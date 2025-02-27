#include <iostream>
using namespace std;

const int n = 10;
int tab[n] = {12, 3, 2, -7, 44, 5, 1, 0, -3,99};

// Funkcja rekurencyjna zwraca true, gdy znajdzie element x w przedziale indeksów [left, right]
bool szukajRekurencyjnie(const int tab[], int left, int right, int x) {
    if (left > right) {
        return false;
    }
    if (tab[left] == x) {
        return true;
    }
    return szukajRekurencyjnie(tab, left + 1, right, x);
}

int main() {
    int szukane1 = 7;
    int szukane2 = 5;

    if (szukajRekurencyjnie(tab, 0, n , szukane1))
        cout << "Znalazłem element " << szukane1 << endl;
    else
        cout << "Element " << szukane1 << " nie został znaleziony" << endl;

    if (szukajRekurencyjnie(tab, 0, n - 1, szukane2))
        cout << "Znalazłem element " << szukane2 << endl;
    else
        cout << "Element " << szukane2 << " nie został znaleziony" << endl;

    return 0;
}
