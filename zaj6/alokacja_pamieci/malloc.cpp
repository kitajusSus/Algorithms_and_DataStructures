#include <iostream>
#include <cstdlib>

int main() {
    int *arr;
    int n = 5;
    
    // Allocate memory for an array of 5 integers
    arr = (int*)malloc(n * sizeof(int));
    
    // Check if memory allocation was successful
    if (arr == NULL) {
        std::cerr << "Memory not allocated." << std::endl;
        return 1;
    }
    
    // Memory has been successfully allocated
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    
    // Print the allocated memory values
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    
    // Free the allocated memory
    free(arr);
    
    return 0;
}