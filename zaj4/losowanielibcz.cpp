#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// Zwraca wektor (dynamiczną tablicę) zawierającą losowe 0 i 1
vector<int> robienie_tablicy(int n) {
    vector<int> arr(n);
    
    // Inicjalizacja generatora liczb losowych
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);
    
    // Wypełnianie tablicy losowymi 0 i 1
    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
    }
    
    return arr;
}

// Alternatywna wersja używająca prostszego generatora losowego
vector<int> robienie_tablicy_prosta(int n) {
    vector<int> arr(n);
    
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr));
    
    // Wypełnianie tablicy losowymi 0 i 1
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 2; // generuje 0 lub 1
    }
    
    return arr;
}

int main() {
    int n = 10;
    
    // Użycie funkcji
    vector<int> tablica = robienie_tablicy(n);
    
    // Wyświetlenie wyników
    cout << "Wygenerowana tablica: ";
    for (int i = 0; i < n; i++) {
        cout << tablica[i] << " ";
    }
    cout << endl;
    
    return 0;
}