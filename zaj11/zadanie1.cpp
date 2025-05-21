#include <algorithm> // Dla std::swap (alternatywa dla własnej funkcji swap)
#include <cstdlib>   // Dla std::rand, std::srand
#include <ctime>     // Dla std::time
#include <iostream>
#include <string> // Dla std::string w displayTree
#include <vector>

// Lepiej unikać "using namespace std;" w zasięgu globalnym w większych
// projektach. Tutaj zostawiam dla zgodności z oryginalnym kodem.
using namespace std;

class Heap {
private:
  vector<int> k; // Wektor przechowujący elementy kopca (k[0] jest nieużywane)
  int nElems;    // Aktualna liczba elementów w kopcu

public:
  // Konstruktor: inicjalizuje kopiec o maksymalnym rozmiarze maxSize
  // Domyślnie maxSize = 100, nElems = 0 (pusty kopiec)
  Heap(int maxSize = 100) : nElems(0) {
    // Wektor k jest indeksowany od 1, więc potrzebujemy maxSize+1 miejsc,
    // jeśli maxSize oznacza maksymalną liczbę elementów.
    // Oryginalny kod robił k.resize(maxSize), co przy indeksowaniu od 1
    // oznaczało, że maksymalny indeks to maxSize-1. Jeśli chcemy maxSize
    // elementów, to k[maxSize] musi być dostępne. Zostawiam jak w oryginale,
    // ale to oznacza, że jeśli maxSize=100, to możemy przechować 99 elementów
    // (indeksy 1 do 99). Bardziej intuicyjne byłoby k.resize(maxSize + 1)
    k.resize(maxSize +
             1); // Zmieniam na maxSize + 1, aby k[maxSize] było dostępne
                 // i można było przechować 'maxSize' elementów.
                 // Jeśli oryginalne maxSize miało oznaczać pojemność tablicy,
                 // to k.resize(maxSize) było OK, ale wtedy maksymalna liczba
                 // elementów do przechowania to maxSize-1.
  }

  // Zwraca aktualny rozmiar kopca
  int heapSize() const { // Dodano const, bo metoda nie modyfikuje obiektu
    return nElems;
  }

  // Zwraca indeks rodzica elementu o indeksie i (dla indeksowania od 1)
  int father(int i) const { // Dodano const
    return i / 2;           // Dzielenie całkowite automatycznie daje floor(i/2)
  }

  // Zwraca indeks lewego dziecka elementu o indeksie i (dla indeksowania od 1)
  int leftChild(int i) const { // Dodano const
    return 2 * i;
  }

  // Zwraca indeks prawego dziecka elementu o indeksie i (dla indeksowania od 1)
  int rightChild(int i) const { // Dodano const
    return 2 * i + 1;
  }

  // Zamienia miejscami elementy w kopcu na pozycjach a i b
  void
  swapElements(int indexA,
               int indexB) { // Zmieniona nazwa, aby nie kolidować z std::swap
    // Można też użyć: std::swap(k[indexA], k[indexB]);
    int temp = k[indexA];
    k[indexA] = k[indexB];
    k[indexB] = temp;
  }

  // Przywraca własność kopca dla poddrzewa zakorzenionego w i (sift-down)
  // Zakłada, że lewe i prawe poddrzewa są już kopcami.
  void restoreHeap(int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int largest =
        i; // Początkowo zakładamy, że bieżący element (i) jest największy

    // Sprawdź, czy lewe dziecko istnieje i jest większe od obecnego 'largest'
    if (left <= nElems && k[left] > k[largest]) {
      largest = left;
    }

    // Sprawdź, czy prawe dziecko istnieje i jest większe od obecnego 'largest'
    if (right <= nElems && k[right] > k[largest]) {
      largest = right;
    }

    // Jeśli największy element nie jest już korzeniem poddrzewa (i)
    if (largest != i) {
      swapElements(i, largest); // Zamień z największym dzieckiem
      restoreHeap(
          largest); // Rekurencyjnie przywróć kopiec dla dotkniętego poddrzewa
    }
  }

  // Buduje kopiec z istniejących elementów w wektorze k
  // Elementy muszą być już w 'k' do nElems.
  void makeHeap() {
    // Zaczynamy od ostatniego rodzica (węzła niebędącego liściem)
    // i idziemy w górę aż do korzenia (indeks 1)
    for (int i = nElems / 2; i >= 1; i--) {
      restoreHeap(i);
    }
  }

  // Usuwa i zwraca największy element z kopca (korzeń)
  int pop() {
    if (nElems == 0) {
      // W bardziej rozbudowanej wersji rzucilibyśmy wyjątek
      cerr << "Blad: Proba usuniecia elementu z pustego kopca!" << endl;
      return -1; // Lub inna wartość błędu
    }
    int largestElement = k[1]; // Największy element jest w korzeniu
    k[1] = k[nElems];          // Przenieś ostatni element na miejsce korzenia
    nElems--;                  // Zmniejsz rozmiar kopca
    if (nElems > 0) {
      restoreHeap(1); // Przywróć własność kopca od korzenia
    }
    return largestElement;
  }

  // Prosta funkcja wstawiania - dodaje element na koniec, ale NIE przywraca
  // własności kopca. Po tej operacji trzeba by wywołać makeHeap lub
  // indywidualnie sift-up. Ta funkcja jest używana w oryginalnym main do
  // "wypełnienia" tablicy przed makeHeap.
  void insert(int x) {
    if (nElems >= k.size() - 1) { // k.size()-1 bo k[0] nieużywane
      cerr << "Blad: Kopiec jest pelny, nie mozna dodac elementu!" << endl;
      // Można zaimplementować dynamiczne rozszerzanie wektora k
      return;
    }
    nElems++;
    k[nElems] = x;
    // Uwaga: ta metoda sama w sobie nie gwarantuje zachowania własności kopca.
    // Własność kopca jest przywracana przez push() lub makeHeap().
  }

  // Wstawia element x do kopca i przywraca własność kopca (sift-up)
  void push(int x) {
    if (nElems >= k.size() - 1) {
      cerr << "Blad: Kopiec jest pelny, nie mozna dodac elementu (push)!"
           << endl;
      return;
    }
    nElems++;
    int i = nElems;
    k[i] = x; // Wstaw nowy element na koniec

    // Przesuwaj element w górę (sift-up), dopóki jest większy od rodzica
    // lub nie dotrze do korzenia
    while (i > 1 && k[i] > k[father(i)]) {
      swapElements(i, father(i));
      i = father(i); // Przejdź do pozycji rodzica
    }
  }

  // Wyświetla elementy kopca w kolejności, w jakiej są w tablicy
  void display() const { // Dodano const
    if (nElems == 0) {
      cout << "Kopiec jest pusty." << endl;
      return;
    }
    for (int i = 1; i <= nElems; i++) {
      cout << k[i] << " ";
    }
    cout << endl;
  }

  // Sortuje elementy tablicy używając algorytmu heapsort
  // Argument t jest ignorowany, jeśli zawsze chcemy budować kopiec na nowo.
  // Oryginalny kod miał t=1 jako domyślny.
  void sort(bool rebuildHeapIfNeeded = true) {
    if (nElems == 0)
      return;

    if (rebuildHeapIfNeeded) {
      makeHeap(); // Upewnij się, że to kopiec
    }

    int originalNumElems = nElems; // Zapamiętaj oryginalny rozmiar kopca

    // Algorytm Heapsort:
    // 1. Zamień korzeń (największy element) z ostatnim elementem kopca.
    // 2. Zmniejsz "widoczny" rozmiar kopca (element na końcu jest już
    // posortowany).
    // 3. Przywróć własność kopca dla zmniejszonego kopca (sift-down od
    // korzenia). Powtarzaj, aż zostanie 1 element w "widocznym" kopcu.
    for (int i = originalNumElems; i >= 2; i--) {
      swapElements(
          1,
          i); // Przenieś największy element (k[1]) na koniec aktualnego zakresu
      nElems--;       // Zmniejsz rozmiar przetwarzanego kopca
      restoreHeap(1); // Przywróć własność kopca dla reszty
    }
    nElems = originalNumElems; // Przywróć oryginalny rozmiar kopca (teraz
                               // tablica jest posortowana)
  }

  // --- Zadanie 1: Funkcja displayTree() ---
public:
  /**
   * @brief Wyświetla strukturę drzewiastą kopca na konsolę.
   *
   * Ta funkcja inicjuje proces wyświetlania, wywołując rekurencyjną funkcję
   * pomocniczą. Drzewo jest rysowane "obrócone" o 90 stopni w lewo, gdzie
   * korzeń jest najbardziej na lewo, a gałęzie rozchodzą się w prawo i w dół.
   * Prawy potomek jest rysowany powyżej swojego rodzica, a lewy potomek
   * poniżej.
   */
  void displayTree() const { // Metoda publiczna, dodano const
    if (nElems == 0) {
      cout << "Kopiec jest pusty. Nie mozna wyswietlic drzewa." << endl;
      return;
    }
    cout << "Struktura drzewiasta kopca (korzen po lewej):" << endl;
    // Wywołanie funkcji rekurencyjnej dla korzenia (indeks 1) na poziomie 0
    displayTreeRecursive(1, 0);
    cout << "---------------------------------------------" << endl;
  }

private:
  // Prywatna, rekurencyjna funkcja pomocnicza do wyświetlania drzewa
  // nodeIndex: indeks bieżącego węzła do wyświetlenia
  // level: poziom zagłębienia w drzewie (używany do wcięcia)
  void displayTreeRecursive(int nodeIndex, int level) const { // Dodano const
    // Warunek bazowy rekurencji: jeśli węzeł nie istnieje w kopcu
    if (nodeIndex < 1 || nodeIndex > nElems) {
      return;
    }

    // 1. Rekurencyjnie wyświetl prawe poddrzewo (zwiększając poziom)
    //    Prawy syn będzie wyświetlony "powyżej" bieżącego węzła w konsoli.
    displayTreeRecursive(rightChild(nodeIndex), level + 1);

    // 2. Wydrukuj bieżący węzeł z odpowiednim wcięciem
    //    Wcięcie jest proporcjonalne do poziomu (level)
    for (int i = 0; i < level; ++i) {
      cout << "    "; // Używamy 4 spacji jako jednostki wcięcia
    }
    cout << k[nodeIndex] << endl; // Wydrukuj wartość węzła

    // 3. Rekurencyjnie wyświetl lewe poddrzewo (zwiększając poziom)
    //    Lewy syn będzie wyświetlony "poniżej" bieżącego węzła w konsoli.
    displayTreeRecursive(leftChild(nodeIndex), level + 1);
  }
  // --- Koniec Zadania 1 ---
};

int main() {
  // Inicjalizacja generatora liczb losowych
  // Używamy std::srand i std::time dla zgodności ze standardem C++
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  int maxSize = 20;         // Maksymalny możliwy rozmiar kopca
  int initialHeapSize = 10; // Początkowa liczba elementów do wstawienia
  Heap h(maxSize);          // Utwórz obiekt kopca

  cout << "Wypelnianie kopca losowymi liczbami (uzywajac insert):" << endl;
  for (int j = 0; j < initialHeapSize; j++) {
    int randomNumber = std::rand() % 100; // Losowa liczba z zakresu 0-99
    h.insert(randomNumber); // Używamy insert - elementy są tylko dodawane,
                            // kopiec nie jest jeszcze kopcem
  }

  cout << "Elementy w tablicy przed makeHeap(): ";
  h.display();
  cout << "Rozmiar kopca: " << h.heapSize() << endl;
  h.displayTree(); // Wyświetl drzewo (może nie być kopcem)

  cout << "\nPo wywolaniu makeHeap():" << endl;
  h.makeHeap(); // Teraz budujemy właściwy kopiec z wstawionych elementów
  cout << "Elementy: ";
  h.display();
  h.displayTree(); // Wyświetl strukturę kopca

  cout << "\nPo push(77):" << endl;
  h.push(77); // Dodajemy 77, metoda push od razu dba o własność kopca
  cout << "Elementy: ";
  h.display();
  h.displayTree();

  cout << "\nPo pop():" << endl;
  if (h.heapSize() > 0) {
    int poppedValue = h.pop(); // Usuwamy największy element
    cout << "Usunieto: " << poppedValue << endl;
  }
  cout << "Elementy: ";
  h.display();
  h.displayTree();

  cout << "\nPo sort():" << endl;
  h.sort(); // Sortujemy tablicę używając heapsort
  cout << "Elementy posortowane: ";
  h.display();
  // Po sortowaniu, struktura w 'k' nie jest już kopcem w tradycyjnym sensie,
  // ale tablicą posortowaną. Wyświetlanie drzewa może nie być sensowne.
  // Jeśli chcemy znowu mieć kopiec, trzeba by go zbudować:
  // h.makeHeap();
  // cout << "Drzewo po sortowaniu (jesli to nadal ma sens):" << endl;
  // h.displayTree();

  cout << "\nNacisnij Enter, aby zakonczyc...";
  cin.get(); // Czeka na Enter - bardziej przenośne niż system("pause")
  return 0;
}
