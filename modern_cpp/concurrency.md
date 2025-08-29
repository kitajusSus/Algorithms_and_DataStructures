# C++ Concurrency Examples

This directory contains simple examples showcasing modern C++ concurrency features.

## Thread Pool

The `thread_pool.cpp` file implements a minimal thread pool that allows you to queue work items and distribute them across a fixed number of worker threads. Tasks are enqueued using `enqueue` which returns a `std::future` representing the eventual result.

## `std::async` and `std::future`

The `async_example.cpp` demonstrates launching an asynchronous task using `std::async`. The returned `std::future` is polled until the result becomes available.

Compile the examples using a C++17 compiler:

```bash
g++ -std=c++17 -pthread async_example.cpp -o async_example
./async_example
```

The thread pool file can be built into your project and used to parallelize workloads.
