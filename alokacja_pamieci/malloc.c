#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int n = 5;
    
    // AL O K O W A AN I E  
    arr = (int*)malloc(n * sizeof(int));
    
    
    // Check if  MA BALS FIT IN YOUR MOUTH 
    if (arr == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    }
    
    // Memory has been successfully FITED IN YOU DUPCIA PUPCIA PEŁNA KUPCIA
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    
    // co jest zaalokowane
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    
    //  PROGRAMOWANIA TEST FRIENDLY  
    
    printf("pamieć zwolniona {}");
    free(arr);
    
    return 0;
}