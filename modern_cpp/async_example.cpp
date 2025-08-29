#include <iostream>
#include <future>
#include <chrono>
#include <thread>

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return result;
}

int main() {
    // start asynchronous task
    std::future<long long> fut = std::async(std::launch::async, factorial, 10);

    std::cout << "Calculating factorial asynchronously...\n";
    // do other work while the task runs
    while (fut.wait_for(std::chrono::milliseconds(50)) != std::future_status::ready) {
        std::cout << "." << std::flush;
    }
    std::cout << "\nResult: " << fut.get() << "\n";
    return 0;
}
