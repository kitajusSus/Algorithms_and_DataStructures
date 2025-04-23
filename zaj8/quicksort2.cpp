// quickSort2.cpp
// Pokazuje Quicksort z wyborem "szefa" jako mediany z trzech
// i prostym sortowaniem dla malych kupek.

#include <iostream>
#include <utility> // Dla std::swap, chocia¿ tu mamy w¿asn¿ funkcj¿ swap
#include <vector>

// Klasa do przechowywania naszych zabawek (liczb)
class ArrayIns {
private:
  std::vector<double> theVect; // Tu trzymamy zabawki
  int nElems;                  // Ile ich jest

  // --- FUNKCJE WEWN¿TRZNE (POMOCNICY) ---

  // Nasza g¿ówna funkcja sortuj¿ca - ta, która wywo¿uje sam¿ siebie!
  void recQuickSort(int left, int right) {
    // Liczymy, ile zabawek jest w tej kupce
    int size = right - left + 1;

    // === TRIK 2: SPRAWDZAMY, CZY KUPKA JEST MA¿A ===
    if (size <= 3) {
      // Je¿li 3 lub mniej, u¿ywamy prostego sortowania
      std::cout << "  -> Kupka ma¿a (" << size << "), sortowanie r¿czne dla ["
                << left << "," << right << "]" << std::endl;
      manualSort(left, right);
    } else { // Je¿li kupka jest wi¿ksza...
      std::cout << "  -> Kupka du¿a (" << size << "), normalny Quicksort dla ["
                << left << "," << right << "]" << std::endl;
      // === TRIK 1: WYBIERAMY M¿DREGO SZEFA (PIVOTA) ===
      // Wo¿amy funkcj¿, która znajdzie "¿redni¿" zabawk¿ z trzech
      double median = medianOf3(left, right);
      std::cout << "    Wybrany m¿dry szef (median): " << median << std::endl;

      // Dzielimy kupk¿ u¿ywaj¿c tego m¿drego szefa
      // Funkcja partitionIt jest podobna jak w zwyk¿ym Quicksort,
      // tylko teraz wie, ¿e szef jest na pozycji 'right-1'
      int partition = partitionIt(left, right, median);
      std::cout << "    Podzia¿ zako¿czony, szef wyl¿dowa¿ na: " << partition
                << std::endl;

      // Wywo¿ujemy siebie (rekurencja!) dla dwóch mniejszych kupek
      recQuickSort(left, partition - 1);  // Sortuj lew¿ kupk¿
      recQuickSort(partition + 1, right); // Sortuj praw¿ kupk¿
    }
  } // Koniec recQuickSort

  // === FUNKCJA DO WYBIERANIA M¿DREGO SZEFA ===
  // Patrzy na pierwsz¿, ¿rodkow¿ i ostatni¿ zabawk¿,
  // wybiera t¿ "¿redni¿" i ustawia j¿ na pozycji 'right-1'
  double medianOf3(int left, int right) {
    int center = (left + right) / 2; // Znajd¿ ¿rodek

    // Porównaj i zamie¿, ¿eby by¿y w kolejno¿ci: left <= center <= right
    if (theVect[left] > theVect[center])
      swap(left, center);
    if (theVect[left] > theVect[right])
      swap(left, right);
    if (theVect[center] > theVect[right])
      swap(center, right);

    // Teraz 'center' ma warto¿¿ "¿redni¿" (median¿).
    // Zamieniamy j¿ miejscem z zabawk¿ na 'right-1'.
    // To przygotowuje j¿ do bycia naszym "szefem" (pivotem) dla partitionIt.
    swap(center, right - 1);
    std::cout << "    medianOf3: Po zamianach, pivot (" << theVect[right - 1]
              << ") jest na " << right - 1 << std::endl;
    return theVect[right - 1]; // Zwró¿ warto¿¿ m¿drego szefa
  } // Koniec medianOf3

  // === FUNKCJA DO DZIELENIA KUPKI ===
  // Dzia¿a podobnie jak w zwyk¿ym Quicksort, ale wie,
  // ¿e prawdziwy "szef" (pivot) jest na pozycji 'right-1'.
  // U¿ywa wska¿ników 'leftMark' i 'rightMark' do przestawiania zabawek.
  int partitionIt(int left, int right, double pivot) {
    int leftMark = left; // Zaczyna od lewej (ale zaraz przeskoczy pierwsz¿)
    int rightMark = right - 1; // Zaczyna od prawej (przed pozycj¿ szefa)

    while (true) {
      // Szukaj od lewej zabawki WI¿KSZEJ od szefa
      // ++leftMark -> najpierw zwi¿ksz, potem sprawd¿
      while (theVect[++leftMark] < pivot)
        ; // Pusta p¿tla - szukamy

      // Szukaj od prawej zabawki MNIEJSZEJ od szefa
      // --rightMark -> najpierw zmniejsz, potem sprawd¿
      while (theVect[--rightMark] <
             pivot) // B¿¿D W ORYGINALE? Powinno by¿ '>'? Sprawd¿my kod z
                    // prezentacji. Tak, >.
        // Poprawka: Powinno szuka¿ elementu MNIEJSZEGO lub RÓWNEGO pivotowi od
        // prawej, ale algorytm Lafore'a szuka WI¿KSZEGO od pivot i idzie od
        // prawej. Trzymajmy si¿ Lafore'a:
        while (theVect[--rightMark] > pivot)
          ; // Pusta p¿tla - szukamy (wg Lafore'a, szukamy > pivot id¿c w lewo)

      if (leftMark >= rightMark)   // Je¿li wska¿niki si¿ min¿¿y...
        break;                     // ...to koniec dzielenia tej cz¿¿ci
      else                         // Je¿li si¿ nie min¿¿y...
        swap(leftMark, rightMark); // ...zamie¿ znalezione zabawki miejscami
    } // Koniec p¿tli while

    // Po p¿tli, wska¿nik 'leftMark' jest na pierwszej zabawce z "prawej"
    // (wi¿kszej) grupy. Trzeba teraz postawi¿ naszego szefa (który jest na
    // 'right-1') na w¿a¿ciwym miejscu. W¿a¿ciwe miejsce to w¿a¿nie 'leftMark'.
    swap(leftMark, right - 1);
    return leftMark; // Zwró¿ indeks, gdzie wyl¿dowa¿ szef
  } // Koniec partitionIt

  // === FUNKCJA DO PROSTEGO SORTOWANIA MA¿YCH KUPEK ===
  void manualSort(int left, int right) {
    int size = right - left + 1;
    if (size <= 1)
      return;        // 0 lub 1 zabawka = ju¿ posortowane
    if (size == 2) { // Dwie zabawki
      if (theVect[left] > theVect[right])
        swap(left, right); // Zamie¿, je¿li trzeba
      return;
    } else { // Trzy zabawki (size == 3)
      // Proste porównania i zamiany, by ustawi¿ w kolejno¿ci
      if (theVect[left] > theVect[right - 1]) // lewa ze ¿rodkow¿
        swap(left, right - 1);
      if (theVect[left] > theVect[right]) // lewa z praw¿
        swap(left, right);
      if (theVect[right - 1] > theVect[right]) // ¿rodkowa z praw¿
        swap(right - 1, right);
    }
    std::cout << "      Po manualSort: ";
    displaySubset(left, right);
  } // Koniec manualSort

  // Funkcja do zamiany dwóch zabawek miejscami
  void swap(int dex1, int dex2) {
    double temp = theVect[dex1];
    theVect[dex1] = theVect[dex2];
    theVect[dex2] = temp;
  }

  // Pomocnicza do wy¿wietlania fragmentu
  void displaySubset(int left, int right) {
    std::cout << "[";
    for (int k = left; k <= right; ++k)
      std::cout << theVect[k] << (k == right ? "" : " ");
    std::cout << "]" << std::endl;
  }

public:
  // Konstruktor - tworzy miejsce na zabawki
  ArrayIns(int max) : nElems(0) { theVect.resize(max); }

  // Dodaje now¿ zabawk¿
  void insert(double value) {
    theVect[nElems] = value;
    nElems++;
  }

  // Wy¿wietla wszystkie zabawki
  void display() {
    std::cout << "A = [ ";
    for (int j = 0; j < nElems; j++)
      std::cout << theVect[j] << " ";
    std::cout << "]" << std::endl;
  }

  // G¿ówna funkcja sortuj¿ca, któr¿ wywo¿ujemy z zewn¿trz
  void quickSort() {
    std::cout << "Rozpoczynanie Super Quicksort dla " << nElems << " elementów."
              << std::endl;
    recQuickSort(0, nElems - 1); // Zaczynamy sortowanie od pocz¿tku do ko¿ca
    std::cout << "Super Quicksort zako¿czony." << std::endl;
  }
}; // Koniec klasy ArrayIns

// --- G¿ówna cz¿¿¿ programu ---
int main() {
  int maxSize = 16;      // Maksymalna liczba zabawek
  ArrayIns arr(maxSize); // Tworzymy pude¿ko na zabawki

  // Wk¿adamy losowe zabawki (mo¿esz zmieni¿ na inne liczby)
  srand(time(NULL)); // ¿eby losowanie by¿o ró¿ne za ka¿dym razem
  for (int j = 0; j < maxSize; j++) {
    double n = rand() % 100; // Losowa zabawka od 0 do 99
    arr.insert(n);
  }
  // Mo¿esz te¿ doda¿ zabawki r¿cznie:
  // arr.insert(77); arr.insert(99); arr.insert(44); ...

  std::cout << "Zabawki przed sortowaniem:" << std::endl;
  arr.display();
  std::cout << std::endl;

  // Wywo¿ujemy nasze super sortowanie!
  arr.quickSort();

  std::cout << std::endl;
  std::cout << "Zabawki po sortowaniu:" << std::endl;
  arr.display();

  return 0;
}
