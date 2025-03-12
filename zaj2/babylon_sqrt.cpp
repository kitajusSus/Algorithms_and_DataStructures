/**
 * @file babylonian_sqrt.cpp
 * @author kitajusSus (2025-03-05)
 * @brief Implementacja metody Babilończyków do obliczania pierwiastka kwadratowego
 * 
 * Program oblicza pierwiastek kwadratowy z dowolnej liczby dodatniej
 * przy użyciu starożytnej metody Babilończyków (zwanej też metodą Herona
 * lub jako szczególny przypadek metody Newtona-Raphsona).
 */


//
//Metoda opiera się na prostej obserwacji:

//Jeśli x jest przybliżeniem pierwiastka z S, to S/x jest również przybliżeniem
//Średnia arytmetyczna tych dwóch przybliżeń daje lepsze przybliżenie pierwiastka
//Dlatego wzór iteracyjny wygląda następująco:
//x_{n+1} = (x_n + S/x_n) / 2

//Jak działa algorytm:
//    Inicjalizacja: Wybieramy początkowe przybliżenie x₀ (w programie używamy S/2)
//    Iteracja: Obliczamy kolejne przybliżenia według wzoru: x₍ₙ₊₁₎ = (x₍ₙ₎ + S/x₍ₙ₎)/2
//    Warunek stopu: Kontynuujemy, aż |x₍ₙ₊₁₎ - x₍ₙ₎| < epsilon (gdzie epsilon to zadana dokładność)

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


/**
 * @brief Funkcja obliczająca pierwiastek kwadratowy metodą Babilończyków
 * 
 * @param S - liczba, z której obliczamy pierwiastek (musi być dodatnia)
 * @param epsilon - dokładność obliczeń (domyślnie 0.001)
 * @return double - obliczony pierwiastek kwadratowy z S
 */


double babylonianSqrt(double S, double epsilon = 0.001) {
    // Sprawdzenie, czy  dodatnia
    if (S < 0) {
        cerr << "Nie można obliczyć pierwiastka z liczby ujemnej!" <<endl;
        return -1.0;
    }
    // Przypadek brzegowy - pierwiastek z 0 wynosi 0
    if (S == 0.0) {
        return 0.0;
    }
    // Krok 1: Wybranie początkowego przybliżenia
    // Można użyć S/2 lub innej sensownej wartości początkowej
    double x0 = S / 2.0;
    if (x0 == 0.0) x0 = 1.0; // Zabezpieczenie przed dzieleniem przez 0
    // Krok 2: Obliczenie pierwszego przybliżenia
    double x1 = (x0 + S / x0) / 2.0;
    // Krok 3: Iteracyjne przybliżanie wyniku
    while (abs(x1 - x0) > epsilon) {
        x0 = x1;                  // Poprzednie przybliżenie staje się nowym x0
        x1 = (x0 + S / x0) / 2.0; // Wzór na kolejne przybliżenie
    }
    return x1;
}

int main() {
    double liczba;
    cout << "=== METODA BABILOnCZYKoW - OBLICZANIE PIERWIASTKA KWADRATOWEGO ===" << std::endl;
    cout << "Autor: 89219" << endl << endl;

    // Pobranie liczby od użytkownika
    cout << "Podaj liczbe dodatniaa: ";
    cin >> liczba;
    cout << fixed << setprecision(6);
    // ???? czy  dodatnia
    if (liczba < 0) {
        cout << "Blad: Liczba musi być dodatnia!" << endl;
        return 1;
    }
    // Obliczenie
    double wynik = babylonianSqrt(liczba);
    cout << "Pierwiastek z " << liczba << " (metoda Babilonczyków): " << wynik << endl;
    // Porównanie z wbudowaną funkcją sqrt()
    cout << "Pierwiastek z " << liczba << " (funkcja sqrt()): " << sqrt(liczba) << endl;
    cout << "roznica miedzy wynikami: " << abs(wynik - sqrt(liczba)) << endl;
    
    return 0;
}
