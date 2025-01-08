#pragma once

#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace concurrency {

/**
 * A multithreaded task queue.
 * The tasks are picked in order of arrival, and they do not have priorities.
 * The synchronization with the user happens through std::future<R>s.
 *
 * @warning Futures returned by the TaskQueue might throw after destroying the TaskQueue.
 *          Don't discard the futures returned and wait for them before the TaskQueue is destroyed.
 *          Do not call future.get() on a future coming from a TaskQueue after it is destroyed.
 *
 * On the TaskQueue destructor, the threads will detach and continue the already started tasks
 * until they get finished. No new tasks will be started, even if the queue was not emtpy. The never
 * started tasks will get lost. At that point, their futures will have an exception inside, and
 * return true when calling valid(), and they will be ready when calling wait_for(). They will throw
 * std::future_error exceptions with the std::future_errc::broken_promise error code inside when
 * calling get(). Therefore, don't discard the futures returned from PushBack and wait for them
 * before the TaskQueue is destroyed. Moreover, in general, do not call future.get() on a future
 * coming from a TaskQueue after it is destroyed.
 */
class TaskQueue {
public:
	explicit TaskQueue(int numWorkers);
	~TaskQueue();

	TaskQueue(const TaskQueue&) = delete;
	TaskQueue& operator=(const TaskQueue&) = delete;
	TaskQueue(TaskQueue&&) = delete;
	TaskQueue& operator=(TaskQueue&&) = delete;

	/**
	 * @brief Inserts a new task to be executed. Tasks are executed in order.
	 *
	 * @tparam R Return type of the task.
	 * @param task Task to be executed.
	 *
	 * @return A future with the return type.
	 */
	template<typename R>
	[[nodiscard]] std::future<R> PushBack(std::function<R()> task) {
		auto promise = std::make_shared<std::promise<R>>();
		auto future = promise->get_future();
		PushBackImpl([p = std::move(promise), t = std::move(task)]() mutable {
			if constexpr (std::is_same<R, void>::value) {
				t();
				p->set_value();
			} else {
				p->set_value(t());
			}
		});
		return future;
	}

private:
	void PushBackImpl(std::function<void()>&& task);

	struct SSynchronizationPrimitives {
		bool mIsBeingDestroyed = false;
		std::mutex mMutex;
		std::condition_variable mConditionVariable;
	};

	std::vector<std::thread> mWorkers;
	std::queue<std::function<void()>> mTasks;
	std::shared_ptr<SSynchronizationPrimitives> mSynchronizationPrimitives;
};

}
