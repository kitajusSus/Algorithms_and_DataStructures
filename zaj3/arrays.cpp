#include <iostream>
using namespace std;

int main(){
    // Deklarujemy tablicę 100 elementów - spoko, zawsze lepiej mieć zapas miejsca
    // w razie jakbyśmy chcieli więcej rzeczy wsadzić
    int arr[100];
    const int UNDEFINED = -999999;  // specjalna wartość oznaczająca niezdefiniowany element 
    // Inicjalizacja wszystkich elementów jako niezdefiniowane
    for(int i = 0; i < 100; i++) {
        arr[i] = UNDEFINED;
    } 
    // Definiowanie wartości
    arr[1] = 99;
    arr[99] = 1;
          // nasza tablica do przechowywania liczb
    int nElems = 0;         // licznik elementów - mega ważne by śledzić ile mamy elementów!
    int j;                  // zmienna do pętli - będziemy jej używać kilka razy
    int searchKey;          // wartość której będziemy szukać
    int* pointer = arr;

    cout << pointer<<endl; // pusty adres narazie nie ma elementu
    // wskaźnik pokazuje pierwszy element tablicy
    //--------------------------------------------------------------
    // Wrzucamy początkowe wartości do tablicy - normalnie można by to zrobić pętlą,
    // ale tu dla jasności robimy po jednym. To jak wkładanie rzeczy na półkę.
    arr[0] = 77;            // indeksy zaczynają się od 0, nie od 1! Pamiętaj o tym mój ty pumperniklu!
    arr[1] = 99;
    arr[2] = 44;
    arr[3] = 55;
    arr[4] = 22;
    arr[5] = 88;
    arr[6] = 11;
    arr[7] = 00;            // to samo co 0
    arr[8] = 66;
    arr[9] = 33;
    nElems = 10; 
    cout << *(pointer+1)<<endl; // w tej kolumnie pamieci juz jest coś       
        // ustawiamy licznik na 10, bo tyle elementów dodaliśmy
        
    //cout<<"Wyswietlanie wskaznikowe dla elementow tablicy";
    //int size = sizeof(arr)/sizeof(arr[1]);
    //for(int i=0; i<size; i++)
    //    cout<< *(pointer + i)<<endl;

    // Wyświetlanie tylko zdefiniowanych elementów
    cout << "Zdefiniowane elementy:" << endl;
    for(int i = 0; i < size; i++) {
        if(arr[i] != UNDEFINED) {
            cout << "arr[" << i << "] = " << arr[i] << endl;
        }
    }
    
    // zobaczcie ze ten kod jest chujowy, bo rozmiar tablicy jest gigantyczny (ma 100 elementów)


    //--------------------------------------------------------------
    // Wyświetlamy zawartość tablicy
    // Po prostu lecimy od 0 do nElems (czyli 10) i drukujemy każdy element
    cout << "Nasza tablica na początku: ";
    for( j=0; j<nElems; j++)     // klasyczna pętla for: start, warunek, krok
        cout << arr[j] << " ";  // wyświetlamy każdy element i spację
    cout << endl;               // na końcu nowa linia dla lepszej czytelności
    
    //--------------------------------------------------------------
    // Szukamy elementu o wartości 66
    // To jest proste wyszukiwanie liniowe - idziemy element po elemencie
    searchKey = 66;             // to jest ta wartość, której szukamy
    cout << "Szukamy elementu " << searchKey << "..." << endl;
    
    for(j=0; j<nElems; j++)     // znowu pętla po całej tablicy
        if(arr[j] == searchKey) // sprawdzamy czy aktualny element to ten, którego szukamy
            break;              // jeśli znaleźliśmy, to wyskakujemy z pętli - break!
    
    // Teraz sprytna część - sprawdzamy czy znaleźliśmy element czy nie
    // Jeśli j doszło do końca tablicy (j == nElems), to znaczy że nie znaleźliśmy
    if(j == nElems)
        cout << "Nie znaleziono elementu " << searchKey << endl;
    else
        cout << "Znalazłem " << searchKey << " na pozycji " << j << endl;
    
    //--------------------------------------------------------------
    // Teraz usuwamy element o wartości 55
    // Najpierw musimy go znaleźć (tak samo jak wyżej), a potem przesunąć wszystko w dół
    searchKey = 55;
    cout << "Usuwam element " << searchKey << "..." << endl;
    
    // Szukamy elementu - dokładnie jak wcześniej
    for(j=0; j<nElems; j++)
        if(arr[j] == searchKey)
            break;
    
    // Teraz przesuwamy wszystkie elementy o indeksie większym od j o jeden w dół
    // To jak przesuwanie książek na półce, gdy wyciągasz jedną ze środka
    for(int k=j; k<nElems-1; k++)   // zauważ nElems-1, bo inaczej wyjdziemy poza tablicę!
        arr[k] = arr[k+1];          // kopiujemy element z prawej na pozycję bieżącą
    
    nElems--;                       // zmniejszamy liczbę elementów o 1
    
    //--------------------------------------------------------------
    // Wyświetlamy tablicę po usunięciu - dokładnie tak samo jak wcześniej
    cout << "Tablica po usunięciu " << searchKey << ": ";
    for(j=0; j<nElems; j++)
        cout << arr[j] << " ";
    cout << endl;
    
    //--------------------------------------------------------------
    // BONUS: Co jeszcze można zrobić z tablicami:
    
    // 1. Wstawianie w określone miejsce (nie tylko na końcu)
    cout << "\n--- BONUS: Wstawianie w środek tablicy ---" << endl;
    int insertPos = 3;                  // pozycja, na którą chcemy wstawić
    int insertVal = 42;                 // wartość do wstawienia
    
    // Najpierw przesuwamy wszystko od końca o jeden w prawo aby zrobić miejsce
    for(j=nElems; j>insertPos; j--)
        arr[j] = arr[j-1];
    
    arr[insertPos] = insertVal;         // wstawiamy nową wartość
    nElems++;                           // zwiększamy licznik
    
    cout << "Tablica po wstawieniu " << insertVal << " na pozycję " << insertPos << ": ";
    for(j=0; j<nElems; j++)
        cout << arr[j] << " ";
    cout << endl;
    
    // 2. Znajdowanie największego elementu
    cout << "\n--- BONUS: Znajdowanie max ---" << endl;
    int max = arr[0];                   // zakładamy, że pierwszy element jest największy
    
    for(j=1; j<nElems; j++)            // sprawdzamy resztę elementów
        if(arr[j] > max)               // jeśli znajdziemy większy
            max = arr[j];              // aktualizujemy max
    
    cout << "Największy element: " << max << endl;
    
    // 3. Sortowanie bąbelkowe (proste, ale nie najwydajniejsze)
    cout << "\n--- BONUS: Sortowanie bąbelkowe ---" << endl;
    for(int i=0; i<nElems-1; i++) {
        for(int k=0; k<nElems-1-i; k++) {
            if(arr[k] > arr[k+1]) {     // jeśli elementy są w złej kolejności
                // zamieniamy je miejscami - klasyczna podmiana z trzecią zmienną
                int temp = arr[k];
                arr[k] = arr[k+1];
                arr[k+1] = temp;
            }
        }
    }
    
    cout << "Tablica po sortowaniu: ";
    for(j=0; j<nElems; j++)
        cout << arr[j] << " ";
    cout << endl;
    
    return 0;
} // koniec main()

/* 
Hej, kilka dodatkowych uwag:

1. Pamiętaj, że w tym kodzie używamy tablicy statycznej (o stałym rozmiarze).
   W praktyce często lepiej użyć wektora (std::vector), który sam się powiększa.

2. Funkcje, które tutaj zrobiliśmy (wyszukiwanie, usuwanie) mają złożoność O(n),
   czyli czas ich wykonania rośnie liniowo z rozmiarem tablicy.

3. Gdybyśmy często wyszukiwali elementy, lepiej byłoby najpierw posortować tablicę,
   a potem używać wyszukiwania binarnego - wtedy złożoność to O(log n).

4. Ten kod jest proceduralny, w prawdziwych projektach używa się podejścia obiektowego -
   czyli zamknęlibyśmy tablicę i wszystkie operacje w klasie, żeby był porządek.
*/
