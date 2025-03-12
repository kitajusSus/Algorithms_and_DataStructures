

#include <iostream>
#include <vector>  // Ten include daje nam dostęp do klasy vector - taka lepsza tablica
using namespace std;

////////////////////////////////////////////////////////////////
// To jest nasza pierwsza klasa! LowArray to takie opakowanie na vector,
// ale z bardzo prostym interfejsem - stąd "Low" w nazwie
class LowArray
{
private:
    // 'private' oznacza, że te dane są schowane i tylko metody klasy mogą się do nich dostać
    // To jest bardzo ważny koncept w OOP (Programowaniu Obiektowym) - enkapsulacja!
    vector<double> v;  // Używamy vectora zamiast zwykłej tablicy - ma on wiele zalet
                       // vector to dynamiczna tablica, która może zmieniać rozmiar
                       // W przeciwieństwie do zwykłej tablicy int arr[100], która ma stały rozmiar

public:
    // 'public' oznacza, że te metody są dostępne dla kodu poza klasą
    // Tak tworzymy nasz interfejs dla świata zewnętrznego
    
    //--------------------------------------------------------------
    // Konstruktor - specjalna metoda wywoływana przy tworzeniu obiektu
    // Jest jak "ceremonia powitalna" dla nowego obiektu :)
    LowArray(int max)  // Przyjmuje maksymalny rozmiar tablicy
    { 
        v.resize(max);  // resize() ustawia rozmiar vectora
                        // To lepsze niż zwykła tablica, której rozmiaru nie można zmienić!
    }
    
    //--------------------------------------------------------------
    // Ta metoda pozwala ustawić wartość elementu na danej pozycji
    void setElem(int index, double value)
    { 
        v[index] = value;  // Tutaj używamy operatora [] vectora - działa jak w zwykłej tablicy
                           // Uwaga: Nie ma tu sprawdzania zakresu - można wyjść poza granice!
    }
    
    //--------------------------------------------------------------
    // Ta metoda pozwala odczytać wartość elementu z danej pozycji
    double getElem(int index)
    { 
        return v[index];  // Zwraca element vectora na pozycji index
                          // Znów bez sprawdzania zakresu - można się wywalić!
    }
    
    // Zauważ, że te metody są bardzo proste - stąd nazwa "LowArray"
    // To dosłownie tylko "settery" i "gettery" bez żadnej dodatkowej logiki
    
}; //end class LowArray
////////////////////////////////////////////////////////////////

int main()
{
    // Tworzymy obiekt klasy LowArray o rozmiarze 100
    // To wywołuje nasz konstruktor LowArray(int max)
    LowArray arr(100);  // Teraz arr to nasz obiekt, przez który będziemy operować na tablicy
    
    int nElems = 0;     // Licznik elementów - UWAGA: musimy ręcznie go śledzić!
                        // To jest słabość tego podejścia - klasa nie śledzi, ile elementów faktycznie jest w tablicy
    int j;              // Zmienna do iteracji w pętlach
    
    //--------------------------------------------------------------
    // Wstawiamy 10 elementów używając metody setElem()
    // Zauważ, że musimy ręcznie podać indeks każdego elementu
    arr.setElem(0, 77);  // W bardziej zaawansowanej klasie moglibyśmy mieć metodę insert(),
    arr.setElem(1, 99);  // która automatycznie dodawałaby element na końcu
    arr.setElem(2, 44);
    arr.setElem(3, 55);
    arr.setElem(4, 22);
    arr.setElem(5, 88);
    arr.setElem(6, 11);
    arr.setElem(7, 00);  // To samo co 0.0 (pamiętaj, że przechowujemy double)
    arr.setElem(8, 66);
    arr.setElem(9, 33);
    nElems = 10;         // Ręcznie ustawiamy licznik na 10 - nasza klasa tego nie śledzi!
    
    //--------------------------------------------------------------
    // Wyświetlamy zawartość tablicy za pomocą getElem()
    cout << "Tablica na początku: ";
    for(j=0; j<nElems; j++)
        cout << arr.getElem(j) << " ";  // Używamy getElem() do odczytu wartości
    cout << endl;
    
    //--------------------------------------------------------------
    // Szukamy elementu o wartości 26
    int searchKey = 26;
    cout << "Szukam elementu " << searchKey << "..." << endl;
    
    // Zauważ, że musimy ręcznie implementować wyszukiwanie!
    // Nasza klasa LowArray nie oferuje metody search() - ma tylko getElem() i setElem()
    for(j=0; j<nElems; j++)
        if(arr.getElem(j) == searchKey)  // Sprawdzamy każdy element
            break;                        // Przerywamy pętlę, jeśli znaleźliśmy
    
    // Sprawdzamy, czy znaleźliśmy element
    if(j == nElems)  // Jeśli j == nElems, to znaczy, że przeszliśmy całą tablicę bez znalezienia
        cout << "Nie znalazłem elementu " << searchKey << endl;
    else
        cout << "Znalazłem element " << searchKey << endl;
    
    //--------------------------------------------------------------
    // Usuwamy element o wartości 55
    // Znów musimy zaimplementować tę funkcjonalność sami, ponieważ LowArray tego nie oferuje
    double deleteKey = 55;
    cout << "Usuwam element " << deleteKey << endl;
    
    // Najpierw szukamy elementu - identycznie jak wcześniej
    for(j=0; j<nElems; j++)
        if(arr.getElem(j) == deleteKey)
            break;
    
    // Przesuwamy wszystkie elementy o wyższym indeksie o jedno miejsce w dół
    for(int k=j; k<nElems-1; k++)  // Zauważ nElems-1 - nie wychodzimy poza tablicę
        arr.setElem(k, arr.getElem(k+1));  // Kopiujemy element z k+1 na pozycję k
    
    nElems--;  // Zmniejszamy licznik elementów
    
    //--------------------------------------------------------------
    // Wyświetlamy zawartość tablicy po usunięciu
    cout << "Tablica po usunięciu " << deleteKey << ": ";
    for(j=0; j<nElems; j++)
        cout << arr.getElem(j) << " ";
    cout << endl;
    
    return 0;
} //end main()

/* 
DODATKOWE WYJAŚNIENIA:

1. Zalety vectora nad zwykłą tablicą:
   - Można zmieniać jego rozmiar (resize)
   - Ma wbudowane metody jak push_back(), size()
   - Automatycznie zarządza pamięcią (nie trzeba delete[])
   - Obsługa błędów (np. metoda at() sprawdza zakres)

2. Co to jest "low-level interface"?
   - Nasza klasa oferuje tylko podstawowe operacje: pobierz i ustaw element
   - Nie ma wyższych funkcji jak wstawianie, usuwanie czy wyszukiwanie
   - Te funkcjonalności musimy implementować w kodzie klienta (w main())
   - To jak dać komuś śrubokręt i śruby, zamiast gotowego mebla :)

3. Enkapsulacja - ukrywanie implementacji:
   - Vector jest prywatny (private) - nie można się do niego dostać bezpośrednio z main()
   - Dostęp jest tylko przez metody publiczne getElem() i setElem()
   - Dzięki temu możemy zmienić implementację (np. na zwykłą tablicę) bez zmiany interfejsu

4. Ograniczenia tego rozwiązania:
   - Brak sprawdzania zakresu indeksów (można wyjść poza tablicę)
   - Musimy ręcznie śledzić liczbę elementów (nElems)
   - Sami implementujemy wszystkie algorytmy (wyszukiwanie, usuwanie)
   - To sporo kodu do napisania i potencjalne źródło błędów!

5. Co można by poprawić?
   - Dodać sprawdzanie zakresu indeksów w getElem() i setElem()
   - Dodać metody wyższego poziomu jak insert(), search(), remove()
   - Wewnętrznie przechowywać liczbę elementów, zamiast robić to w main()

To jest pierwszy krok w kierunku obiektowego podejścia do struktur danych. W kolejnym przykładzie
zapewne zobaczymy klasę z bardziej rozbudowanym interfejsem, która przejmie więcej odpowiedzialności!
*/
