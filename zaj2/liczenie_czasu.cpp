#include <iostream>
#include <ctime>

int main() {
    // Start measuring time
    std::clock_t start = std::clock();

    // Code to measure
    // ...

    // End measuring time
    std::clock_t end = std::clock();

    // Calculate the duration
    double duration = double(end - start) / CLOCKS_PER_SEC;

    // Output the duration
    std::cout << "Time taken: " << duration << " seconds" << std::endl;

    return 0;
}