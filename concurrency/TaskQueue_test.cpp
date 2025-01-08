#include "TaskQueue.h"

#include <gtest/gtest.h>

#include <random>

namespace {

struct STaskHandler {
	std::future<void> mFuture;

	std::mutex mStartMutex;
	std::condition_variable mStartConditionVariable;
	bool mIsStarted = false;

	std::mutex mEndMutex;
	std::condition_variable mEndConditionVariable;
	bool mIsEnded = false;

	void WaitStart() {
		auto startLock = std::unique_lock(mStartMutex);
		mStartConditionVariable.wait(startLock, [this]() { return mIsStarted; });
	}

	bool IsStarted(std::chrono::milliseconds duration) {
		auto sLock = std::unique_lock(mStartMutex);
		return mStartConditionVariable.wait_for(sLock, duration, [this]() { return mIsStarted; });
	}

	void TriggerStart() {
		auto startLock = std::unique_lock(mStartMutex);
		mIsStarted = true;
		startLock.unlock();
		mStartConditionVariable.notify_all();
	}

	void WaitEnd() {
		auto endLock = std::unique_lock(mEndMutex);
		mEndConditionVariable.wait(endLock, [this]() { return mIsEnded; });
	}

	void TriggerEnd() {
		auto endLock = std::unique_lock(mEndMutex);
		mIsEnded = true;
		endLock.unlock();
		mEndConditionVariable.notify_all();
	}
};

} // namespace

TEST(TeskQueue, Task_ReturnsInt) {
	auto taskQueue = concurrency::TaskQueue(1);
	auto task = []() -> int { return 1234; };
	auto future = taskQueue.PushBack<int>(task);
	auto result = future.get();
	EXPECT_EQ(result, 1234);
}

TEST(TeskQueue, Task_ReturnsVoid) {
	auto taskQueue = concurrency::TaskQueue(1);
	auto task = []() -> void {};
	auto future = taskQueue.PushBack<void>(task);
	future.get();
}

TEST(TeskQueue, TasksConsumed_InOrder) {
	const int numWorkers = 100;
	const int numTasks = numWorkers * 100;

	auto randomDevice = std::random_device();
	auto randomNumberEngine = std::minstd_rand(randomDevice());

	auto taskQueue = concurrency::TaskQueue(numWorkers);

	// PushBack all the tasks with their TaskHandlers. The first _numWorkers_ will start being
	// executed.
	auto tasksHandlers = std::vector<STaskHandler>(numTasks);
	for (int i = 0; i < numTasks; ++i) {
		auto& taskHandler = tasksHandlers[i];
		taskHandler.mFuture = taskQueue.PushBack<void>([&taskHandler]() {
			taskHandler.TriggerStart();
			taskHandler.WaitEnd();
		});
	}

	// First, check that the first _numWorker_ tasks have started (by waiting for the start flag),
	// and store these started TaskHandlers in a vector.
	auto startedTasksHandlers = std::vector<STaskHandler*>(numWorkers, nullptr);
	for (int i = 0; i < numWorkers; ++i) {
		STaskHandler*& startedTaskHandlerPtr = startedTasksHandlers[i];
		auto& taskHandler = tasksHandlers[i];
		taskHandler.WaitStart();
		startedTaskHandlerPtr = std::addressof(taskHandler);
	}

	// For the rest of tasks: Trigger the end of one of the started task (chosen randomly), and wait
	// until it is ended. Then, check that the next queued task (following the PushBack order) is
	// started (by waiting for the start flag). Update the started TaskHandlers by overwriting the
	// ended with the newly started.
	for (int i = numWorkers; i < numTasks; ++i) {
		auto distribution = std::uniform_int_distribution<int>(0, numWorkers - 1);
		const int randomIndex = distribution(randomNumberEngine);
		STaskHandler*& startedTaskHandlerPtr = startedTasksHandlers[randomIndex];
		startedTaskHandlerPtr->TriggerEnd();
		startedTaskHandlerPtr->mFuture.wait();

		auto& taskHandler = tasksHandlers[i];
		taskHandler.WaitStart();
		startedTaskHandlerPtr = std::addressof(taskHandler);
	}

	// Finally, trigger the end of all the remaining started tasks, and wait until they are ended.
	for (int i = 0; i < numWorkers; ++i) {
		STaskHandler*& startedTaskHandlerPtr = startedTasksHandlers[i];
		startedTaskHandlerPtr->TriggerEnd();
		startedTaskHandlerPtr->mFuture.wait();
	}
}

TEST(TeskQueue, OnDestruction_WorkersDetach) {
	const int numWorkers = 100;
	const int numTasks = 3 * numWorkers;

	auto tasksHandlers = std::vector<STaskHandler>(numTasks);

	{
		auto taskQueue = concurrency::TaskQueue(numWorkers);

		// PushBack all the tasks with their TaskHandlers. The first _numWorkers_ will start being
		// executed.
		for (int i = 0; i < numTasks; ++i) {
			auto& taskHandler = tasksHandlers[i];
			taskHandler.mFuture = taskQueue.PushBack<void>([&taskHandler]() {
				taskHandler.TriggerStart();
				taskHandler.WaitEnd();
			});
		}

		// First, check that the first _numWorker_ tasks have started (by waiting for the start
		// flag), and store these started TaskHandlers in a vector.
		for (int i = 0; i < numWorkers; ++i) {
			auto& taskHandler = tasksHandlers[i];
			taskHandler.WaitStart();
		}

		// Destroy the TaskQueue. The threads will detach and continue the already started tasks
		// until they get finished. No new tasks will be started, even if the queue was not emtpy.
		// The never started tasks will get lost. Their futures will now have an exception inside,
		// and return true when calling valid(), and they will be ready when calling wait_for().
		// They will throw std::future_error exceptions with the std::future_errc::broken_promise
		// error code inside when calling get(). Therefore, in general, do not call future.get() on
		// a future coming from a TaskQueue after destroying it.
	}

	// Check that the first _numWorkers_ tasks are still alive by triggering the end and wait until
	// they are ended.
	for (int i = 0; i < numWorkers; ++i) {
		auto& taskHandler = tasksHandlers[i];
		taskHandler.TriggerEnd();
		taskHandler.mFuture.wait();
	}

	// Check that none of the rest of queued tasks have started.
	for (int i = numWorkers; i < numTasks; ++i) {
		auto& taskHandler = tasksHandlers[i];
		const bool isTaskStarted = taskHandler.IsStarted(std::chrono::milliseconds(0));
		EXPECT_FALSE(isTaskStarted);

		auto& future = taskHandler.mFuture;
		// Their futures will still return true when calling valid().
		const bool isFutureValid = future.valid();
		EXPECT_TRUE(isFutureValid);
		// They will be ready when calling wait_for() (because they have a exception inside).
		const auto future_status = future.wait_for(std::chrono::milliseconds(0));
		EXPECT_EQ(future_status, std::future_status::ready);
		// They will throw std::future_error exceptions with the std::future_errc::broken_promise
		// error code when calling get().
		// EXPECT_THROW(future.get(), std::future_error); // Cannot 'try' with exceptions disabled.
	}
}
