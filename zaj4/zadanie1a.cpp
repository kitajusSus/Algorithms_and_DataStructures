#include <iostream>
#include <vector>

// Funkcja implementująca sortowanie przez wstawianie
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Przesuń elementy arr[0..i-1], które są większe od key,
        // o jedną pozycję do przodu od ich obecnej pozycji
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Funkcja do wyświetlania tablicy
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Tablica przed sortowaniem: ";
    printArray(arr);
    
    insertionSort(arr);
    
    std::cout << "Tablica po sortowaniu przez wstawianie: ";
    printArray(arr);
    
    return 0;
}