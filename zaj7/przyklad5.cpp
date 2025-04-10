// mergesort.cpp
// Demonstruje rekurencyjne sortowanie przez scalanie (Merge Sort)

#include <iostream>
#include <vector> // Używamy wektorów zamiast zwykłych tablic C-style (są bardziej elastyczne)

using namespace std;

// === Klasa DArray ===
// Tworzymy specjalne "pudełko" (klasę) do przechowywania naszej listy liczb
// i funkcji do operowania na niej (jak sortowanie, dodawanie, pokazywanie).
class DArray
{
private:
    // --- Prywatne rzeczy (ukryte przed światem zewnętrznym) ---
    vector<double> theVect; // Wektor (dynamiczna tablica) do przechowywania liczb (typu double)
    int nElems;             // Licznik, ile liczb FAKTYCZNIE jest w wektorze

    // Prywatna, rekurencyjna funkcja sortująca - serce algorytmu
    void recMergeSort(vector<double>& workSpace, int lowerBound, int upperBound);

    // Prywatna funkcja do scalania dwóch posortowanych połówek
    void merge(vector<double>& workSpace, int lowPtr, int highPtr, int upperBound);

public:
    // --- Publiczne rzeczy (dostępne z zewnątrz) ---

    // Konstruktor: Wywoływany, gdy tworzymy nowy obiekt DArray
    // Ustawia początkową liczbę elementów na 0.
    DArray(int max) : nElems(0) // Inicjalizuje nElems na 0
    {
        theVect.resize(max); // Od razu rezerwuje miejsce w wektorze na 'max' liczb
                             // To pomaga w wydajności, ale wektor i tak może rosnąć.
    }

    // Funkcja do wkładania nowej liczby do naszego "pudełka" (wektora)
    void insert(double value)
    {
        theVect[nElems] = value; // Wstawia wartość na kolejne wolne miejsce
        nElems++;                // Zwiększa licznik elementów
    }

    // Funkcja do pokazywania zawartości naszego "pudełka"
    void display()
    {
        // Pętla przechodząca przez wszystkie WSTAWIONE elementy
        for(int j=0; j<nElems; j++)
            cout << theVect[j] << " "; // Wyświetla element i spację
        cout << endl;                  // Przechodzi do nowej linii na końcu
    }

    // Publiczna funkcja rozpoczynająca sortowanie - to ją wywołamy z main()
    void mergeSort()
    {
        // Tworzymy tymczasowy wektor roboczy (workSpace) o tym samym rozmiarze co nasza lista
        // Jest on POTRZEBNY do procesu scalania, żeby nie nadpisać danych, których jeszcze potrzebujemy.
        vector<double> workSpace(nElems);
        // Wywołujemy naszą *prywatną*, rekurencyjną funkcję sortującą
        // Mówimy jej, żeby posortowała cały zakres od początku (0) do końca (nElems-1)
        recMergeSort(workSpace, 0, nElems-1);
    }

}; // --- Koniec definicji klasy DArray ---


// --- Implementacja prywatnej funkcji rekurencyjnej ---
// Sortuje fragment wektora 'theVect' od 'lowerBound' do 'upperBound'
// używając 'workSpace' jako miejsca tymczasowego.
void DArray::recMergeSort(vector<double>& workSpace, int lowerBound, int upperBound)
{
    // **Warunek Bazowy Rekurencji (Kiedy przestać dzielić?)**
    // Jeśli dolna granica jest taka sama jak górna, to znaczy, że mamy tylko jeden element
    // (lub pusty zakres). Jednoelementowa lista jest już posortowana!
    if(lowerBound == upperBound)
    {
        return; // Nic więcej nie rób, wracaj.
    }
    else
    {
        // **Krok Rekurencyjny (Dziel i Zwyciężaj)**
        // 1. Znajdź środek zakresu, który sortujemy
        int mid = (lowerBound + upperBound) / 2;

        // 2. Wywołaj *tę samą funkcję* (rekurencyjnie), żeby posortowała lewą połówkę
        //    Zakres od 'lowerBound' do 'mid'
        recMergeSort(workSpace, lowerBound, mid);

        // 3. Wywołaj *tę samą funkcję* (rekurencyjnie), żeby posortowała prawą połówkę
        //    Zakres od 'mid + 1' do 'upperBound'
        recMergeSort(workSpace, mid+1, upperBound);

        // 4. Teraz obie połówki (lewa i prawa) są już POSORTOWANE.
        //    Wywołaj funkcję 'merge', żeby je połączyć w jedną, posortowaną całość
        //    w odpowiednim fragmencie wektora 'theVect'.
        merge(workSpace, lowerBound, mid+1, upperBound);
    } // koniec else (krok rekurencyjny)
} // --- Koniec recMergeSort ---


// --- Implementacja prywatnej funkcji scalającej ---
// Łączy dwie posortowane połówki wektora 'theVect':
// - Lewa połówka: od 'lowPtr' do 'mid' (mid = highPtr - 1)
// - Prawa połówka: od 'highPtr' do 'upperBound'
// Wynik scalenia trafia najpierw do 'workSpace', a potem jest kopiowany z powrotem do 'theVect'.
void DArray::merge(vector<double>& workSpace, int lowPtr, int highPtr, int upperBound)
{
    int j = 0; // Indeks dla wektora roboczego (workSpace), zaczyna od 0
    int lowerBound = lowPtr; // Zapamiętujemy początek całego scalango zakresu
    int mid = highPtr - 1;   // Obliczamy indeks końca lewej połówki
    int n = upperBound - lowerBound + 1; // Liczba elementów w całym scalango zakresie

    // Główna pętla scalania: Dopóki są elementy w OBU połówkach
    while(lowPtr <= mid && highPtr <= upperBound)
    {
        // Porównaj elementy z lewej i prawej połówki (w oryginalnym theVect)
        if( theVect[lowPtr] < theVect[highPtr] )
        {
            // Element z lewej jest mniejszy, skopiuj go do workSpace
            workSpace[j++] = theVect[lowPtr++]; // Użyj i przesuń wskaźniki
        }
        else
        {
            // Element z prawej jest mniejszy lub równy, skopiuj go do workSpace
            workSpace[j++] = theVect[highPtr++]; // Użyj i przesuń wskaźniki
        }
    } // Koniec głównej pętli scalania

    // Sprzątanie resztek: Jeśli jedna połówka się skończyła, a druga nie.

    // Skopiuj resztę elementów z lewej połówki (jeśli jakieś zostały)
    while(lowPtr <= mid)
        workSpace[j++] = theVect[lowPtr++];

    // Skopiuj resztę elementów z prawej połówki (jeśli jakieś zostały)
    while(highPtr <= upperBound)
        workSpace[j++] = theVect[highPtr++];

    // **Kluczowy Krok:** Skopiuj posortowany fragment z workSpace Z POWROTEM
    // do oryginalnego wektora theVect, we właściwe miejsce!
    for(j=0; j<n; j++)
    {
        theVect[lowerBound+j] = workSpace[j];
    }
} // --- Koniec merge ---


// === Główna funkcja programu ===
int main()
{
    const int maxSize = 100; // Maksymalny rozmiar naszej tablicy
    DArray arr(maxSize);     // Stwórz obiekt DArray (nasze "pudełko")

    // Wstaw kilka nieposortowanych liczb
    arr.insert(64);
    arr.insert(21);
    arr.insert(33);
    arr.insert(70);
    arr.insert(12);
    arr.insert(85);
    arr.insert(44);
    arr.insert(3);
    arr.insert(99);
    arr.insert(0);
    arr.insert(108);
    arr.insert(36);

    cout << "Przed sortowaniem: ";
    arr.display(); // Pokaż liczby przed sortowaniem

    arr.mergeSort(); // Wywołaj sortowanie przez scalanie!

    cout << "Po sortowaniu:   ";
    arr.display(); // Pokaż liczby po sortowaniu

    return 0; // Zakończ program pomyślnie
} 