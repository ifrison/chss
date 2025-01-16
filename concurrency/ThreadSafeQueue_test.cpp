#include "ThreadSafeQueue.h"

#include <test_utils/TestUtils.h>

#include <random>
#include <future>

namespace {

} // namespace

TEST_CASE("ThreadSafeQueue", "TODO") {
	auto threadSafeQueue = concurrency::ThreadSafeQueue<int>();
	REQUIRE(threadSafeQueue.GetSize() == 0);
	threadSafeQueue.Push(123);
	REQUIRE(threadSafeQueue.GetSize() == 1);
	threadSafeQueue.Push(456);
	REQUIRE(threadSafeQueue.GetSize() == 2);
	threadSafeQueue.Push(789);
	REQUIRE(threadSafeQueue.GetSize() == 3);
}

TEST_CASE("ThreadSafeQueue", "TODO2") {
	auto threadSafeQueue = concurrency::ThreadSafeQueue<std::string>();
	auto future1 = std::async([&threadSafeQueue]() {
		int result = threadSafeQueue.Pop();
		REQUIRE(result == 123);
	});
	auto future2 = std::async([&threadSafeQueue]() {
		threadSafeQueue.Push(123);
	});
	future1.get();
	future2.get();
	REQUIRE(threadSafeQueue.IsEmpty());
}

// TODO: Add meaningful unit tests!
