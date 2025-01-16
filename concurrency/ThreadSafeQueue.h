#pragma once

#include <condition_variable>
#include <queue>
#include <mutex>
#include <optional>

namespace concurrency {

template<typename T>
class ThreadSafeQueue {
public:
	template<typename... Args>
	explicit ThreadSafeQueue(Args&&... args) : mQueue(std::forward<Args>(args)...) {}

	[[nodiscard]] bool IsEmpty() const {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		return mQueue.empty();
	}

	[[nodiscard]] std::size_t GetSize() const {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		return mQueue.size();
	}

	void Push(const T& value) {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		return mQueue.push(value);
		uniqueLock.unlock();
		mSynchronizationPrimitives.mConditionVariable.notify_one();
	}

	void Push(T&& value) {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		return mQueue.push(std::move(value));
		uniqueLock.unlock();
		mSynchronizationPrimitives.mConditionVariable.notify_one();
	}

	template<class... Args>
	void Emplace(Args&&... args) {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		mQueue.emplace(std::forward<Args>(args)...);
		uniqueLock.unlock();
		mSynchronizationPrimitives.mConditionVariable.notify_one();
	}

	[[nodiscard]] T Pop() {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		while (mQueue.empty()) {
			mSynchronizationPrimitives.mConditionVariable.wait(uniqueLock);
		}
		auto result = std::move(mQueue.front());
		mQueue.pop();
		return result;
	}

	[[nodiscard]] std::optional<T> TryPop() {
		auto uniqueLock = std::unique_lock(mSynchronizationPrimitives.mMutex);
		while (mQueue.empty()) {
			return std::nullopt;
		}
		auto result = std::move(mQueue.front());
		mQueue.pop();
		return result;
	}

private:
	struct SSynchronizationPrimitives {
		std::mutex mMutex;
		std::condition_variable mConditionVariable;
	};

	std::queue<T> mQueue;
	mutable SSynchronizationPrimitives mSynchronizationPrimitives;
};

}
