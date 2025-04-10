#include <iostream>
#include <chrono>  // dla pomiaru czasu

using namespace std;

int triangle(int n) {
    if (n == 1)
        return 1;
    else
        return(n + triangle(n - 1));
}

int main() {
    int theNumber;
    int triangle(int);
    cout << "enter a number: ";
    cin >> theNumber;

    // Start pomiaru czasu
    auto start = chrono::high_resolution_clock::now();

    int theAnswer = triangle(theNumber);

    // Koniec pomiaru czasu
    auto end = chrono::high_resolution_clock::now();
    
    // Obliczenie czasu w milisekundach
    chrono::duration<double, milli> duration = end - start;

    cout << "Triangle= " << theAnswer << endl;
    cout << "Time taken: " << fixed << duration.count() << " ms" << endl;

    return 0;
}