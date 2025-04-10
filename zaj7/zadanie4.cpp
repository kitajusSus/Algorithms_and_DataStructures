// merge.cpp
// Ten program pokazuje, jak połączyć dwie listy liczb w jedną,
// tak żeby nowa lista też była poukładana od najmniejszej do największej.

#include <iostream> // Potrzebujemy tego, żeby móc pisać na ekranie (np. wyniki)

using namespace std; // Używamy standardowych narzędzi C++, żeby nie pisać ciągle "std::"

// --- Zapowiedzi Funkcji ---
// Mówimy komputerowi, że gdzieś dalej w kodzie będą takie funkcje:
void merge( int[], int, int[], int, int[] ); // Funkcja do łączenia dwóch list (tablic)
void display(int[], int);                     // Funkcja do pokazywania zawartości listy (tablicy)
// ------------------------

// === Główna część programu - tutaj wszystko się zaczyna ===
int main()
{
    // Tworzymy pierwszą listę liczb (już posortowaną!) - jak stosik kart od najmniejszej.
    int arrayA[] = {23, 47, 81, 95};          // Źródło A (4 karty)
    // Tworzymy drugą listę liczb (też posortowaną!) - drugi stosik kart.
    int arrayB[] = {7, 14, 39, 55, 62, 74};   // Źródło B (6 kart)
    // Tworzymy pustą listę, która pomieści wszystkie liczby z A i B (4+6=10 miejsc).
    int arrayC[10];                           // Cel - tutaj trafią połączone karty

    // Wywołujemy "Magika Łączenia", dając mu obie listy A i B, ich rozmiary (4 i 6)
    // oraz pustą listę C, którą ma wypełnić.
    merge(arrayA, 4, arrayB, 6, arrayC);      // Połącz A i B do C --->

    // Wywołujemy "Pokazywacza", żeby wyświetlił nam na ekranie zawartość
    // połączonej listy C (która powinna mieć 10 liczb).
    display(arrayC, 10);                      // Pokaż wynik!

    return 0; // Mówimy systemowi, że program zakończył się pomyślnie.
}
// === Koniec głównej części programu ===


// --- Definicja Funkcji `merge` (Magik Łączenia) ---
// Bierze dwie posortowane listy (arrayA, arrayB) i ich rozmiary (sizeA, sizeB),
// oraz pustą listę (arrayC), do której wpisze połączony wynik.
void merge( int arrayA[], int sizeA,
            int arrayB[], int sizeB,
            int arrayC[] )
{
    // Tworzymy trzy "palce wskazujące":
    int aDex=0;   // Palec dla listy A, zaczyna na początku (pozycja 0)
    int bDex=0;   // Palec dla listy B, zaczyna na początku (pozycja 0)
    int cDex=0;   // Palec dla listy C (wynikowej), zaczyna na początku (pozycja 0)

    // Pętla główna: Robimy to, dopóki mamy elementy w OBU listach A i B
    while( aDex < sizeA && bDex < sizeB ) // Czy palec A i palec B są jeszcze w swoich listach?
    {
        // Porównujemy liczby, na które wskazują palce A i B
        if( arrayA[aDex] < arrayB[bDex] )  // Czy liczba z A jest mniejsza niż liczba z B?
        {
            // Tak, więc kopiujemy liczbę z A do C
            arrayC[cDex] = arrayA[aDex];
            // Przesuwamy palec C na następne miejsce w liście C
            cDex++;
            // Przesuwamy palec A na następną liczbę w liście A
            aDex++;
            // W skrócie: arrayC[cDex++] = arrayA[aDex++];
        }
        else // W przeciwnym razie (liczba z B jest mniejsza lub równa liczbie z A)
        {
            // Kopiujemy liczbę z B do C
            arrayC[cDex] = arrayB[bDex];
             // Przesuwamy palec C na następne miejsce w liście C
            cDex++;
            // Przesuwamy palec B na następną liczbę w liście B
            bDex++;
            // W skrócie: arrayC[cDex++] = arrayB[bDex++];
        }
    } // Koniec pętli porównującej A i B

    // Sprzątanie: Co jeśli jedna lista się skończyła, a druga jeszcze ma liczby?
    // Musimy je po prostu przepisać do końca listy C.

    // Pętla dla resztek z A: Czy palec A doszedł już do końca listy A?
    while(aDex < sizeA) // Dopóki są jeszcze liczby w A...
    {
        // Kopiuj pozostałe liczby z A do C
        arrayC[cDex] = arrayA[aDex];
        cDex++;
        aDex++;
        // W skrócie: arrayC[cDex++] = arrayA[aDex++];
    }

    // Pętla dla resztek z B: Czy palec B doszedł już do końca listy B?
    while(bDex < sizeB) // Dopóki są jeszcze liczby w B...
    {
        // Kopiuj pozostałe liczby z B do C
        arrayC[cDex] = arrayB[bDex];
        cDex++;
        bDex++;
        // W skrócie: arrayC[cDex++] = arrayB[bDex++];
    }
} // --- Koniec funkcji `merge` ---


// --- Definicja Funkcji `display` (Pokazywacz) ---
// Bierze listę (theArray) i jej rozmiar (size), a następnie ją wyświetla.
void display(int theArray[], int size)
{
    // Pętla: Przejdź przez całą listę od początku (j=0) do końca (j<size)
    for(int j=0; j<size; j++)
    {
        // Wypisz na ekranie liczbę z listy, na którą aktualnie patrzymy (theArray[j])
        cout << theArray[j] << " "; // Dodaj spację po liczbie dla czytelności
    }
    cout << endl; // Na końcu przejdź do nowej linii
} // --- Koniec funkcji `display` ---