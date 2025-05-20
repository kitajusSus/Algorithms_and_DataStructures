#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n = 5;
    
    // Allocate memory for an array of 5 integers
    arr = (int*)malloc(n * sizeof(int));
    
    // Check if memory allocation was successful
    if (arr == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    }
    
    // Memory has been successfully allocated
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    
    // Print the allocated memory values
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    
    // Free the allocated memory
    free(arr);
    
    return 0;
}