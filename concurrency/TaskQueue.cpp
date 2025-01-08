#include "TaskQueue.h"

namespace concurrency {

TaskQueue::TaskQueue(int numWorkers)
	: mWorkers()
	, mTasks()
	, mSynchronizationPrimitives(std::make_shared<SSynchronizationPrimitives>()) {
	mWorkers.reserve(numWorkers);
	for (int i = 0; i < numWorkers; ++i) {
		mWorkers.emplace_back([synchronizationPrimitives = mSynchronizationPrimitives, this]() {
			while (!synchronizationPrimitives->mIsBeingDestroyed) {
				auto uniqueLock = std::unique_lock(synchronizationPrimitives->mMutex);
				synchronizationPrimitives->mConditionVariable.wait(uniqueLock, [&]() {
					return synchronizationPrimitives->mIsBeingDestroyed || !mTasks.empty();
				});
				if (synchronizationPrimitives->mIsBeingDestroyed) {
					uniqueLock.unlock();
					return;
				}
				const auto task = std::move(mTasks.front());
				mTasks.pop();
				uniqueLock.unlock();
				task();
			}
		});
	}
}

TaskQueue::~TaskQueue() {
	auto uniqueLock = std::unique_lock(mSynchronizationPrimitives->mMutex);
	mSynchronizationPrimitives->mIsBeingDestroyed = true;
	uniqueLock.unlock();
	mSynchronizationPrimitives->mConditionVariable.notify_all();
	for (auto& worker : mWorkers) {
		// The threads will detach and continue the already started tasks until they get finished.
		// No new tasks will be started, even if the queue was not emtpy. The never started tasks
		// will get lost. Their futures will now have an exception inside, and return true when
		// calling valid(), and they will be ready when calling wait_for(). They will throw
		// std::future_error exceptions with the std::future_errc::broken_promise error code inside
		// when calling get(). Therefore, in general, do not call future.get() on a future coming
		// from a TaskQueue after destroying it.
		worker.detach();
	}
}

void TaskQueue::PushBackImpl(std::function<void()>&& task) {
	auto uniqueLock = std::unique_lock(mSynchronizationPrimitives->mMutex);
	mTasks.push(std::move(task));
	uniqueLock.unlock();
	mSynchronizationPrimitives->mConditionVariable.notify_one();
}

} // namespace concurrency
