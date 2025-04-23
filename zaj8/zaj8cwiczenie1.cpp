// zajecia 8 QUICKSORT
//
// quicksort - sortowanie szybkie

#include <iostream> // Do wyswietlania danych (cout)
#include <utility> // Mozna uzyc std::swap, ale zdefiniujemy w¿asn¿ dla jasno¿ci
#include <vector>  // Do uzywania dynamicznej tablicy (wektora)

// --- Funkcja pomocnicza do wyswietlania wektora ---
void printArray(const std::vector<int> &arr) {
  for (int element : arr) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

// --- Funkcja pomocnicza do zamiany dwóch elementów miejscami ---
// U¿ywamy indeksów i referencji do wektora, aby modyfikowa¿ oryginalny wektor.
void swap(std::vector<int> &arr, int i, int j) {
  // Komentarz: Prosta zamiana warto¿ci przy u¿yciu zmiennej tymczasowej.
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}
void quickSort(std::vector<int> &arr, int low, int high);
// --- ETAP 2: Partycjonowanie (Partitioning) ---
// Funkcja ta przyjmuje podtablic¿ (okre¿lon¿ przez low i high),
// wybiera pivot, przestawia elementy i zwraca ostateczny indeks pivota.
int partition(std::vector<int> &arr, int low, int high);

int main() {
  // Przykladowy wektor do posortowania
  std::vector<int> data = {7, 2, 1, 6, 8, 5, 3, 4};
  // std::vector<int> data = {5, 1, 4, 2, 8}; // Krótszy przyk¿ad z notatek

  std::cout << "Tablica przed sortowaniem: ";
  printArray(data);
  std::cout << "\nRozpoczynanie Quicksort...\n" << std::endl;

  // Pierwsze wywo¿anie quickSort dla ca¿ej tablicy
  // 'low' to 0, 'high' to ostatni indeks (rozmiar - 1)
  quickSort(data, 0, data.size() - 1);

  std::cout << "\nSortowanie zakonczone." << std::endl;
  std::cout << "Tablica po sortowaniu: ";
  printArray(data);

  return 0;
}

// --- ETAP 1 & 3: Rekurencyjna funkcja Quicksort (Dziel i Zwyci¿¿aj) ---
void quickSort(std::vector<int> &arr, int low, int high) {
  std::cout << "Wywolanie quickSort dla zakresu [" << low << ", " << high << "]"
            << std::endl;

  // Komentarz: WARUNEK BAZOWY REKURENCJI.
  // Jesli 'low' jest mniejsze od 'high', to znaczy, że w podtablicy
  // jest więcej niż jeden element i trzeba ja sortowac.
  // Je¿li 'low >= high', podtablica ma 0 lub 1 element, jest ju¿ posortowana.
  if (low < high) {

    // Komentarz: ETAP 1 - DZIEL (Divide).
    // Wywo¿ujemy funkcj¿ partycjonuj¿c¿. Ona przestawia elementy
    // i zwraca indeks, na którym pivot znalaz¿ si¿ po podziale.
    int pivotIndex = partition(arr, low, high);
    std::cout << "  Pivot znalazl sie na indeksie: " << pivotIndex << std::endl;

    // Komentarz: ETAP 3 - ZWYCIEZAJ (Conquer).
    // Rekurencyjnie wywo¿ujemy quickSort dla dwóch podtablic:
    // 1. Lewa podtablica: elementy od 'low' do 'pivotIndex - 1' (mniejsze od
    // pivota).
    // 2. Prawa podtablica: elementy od 'pivotIndex + 1' do 'high' (wi¿ksze od
    // pivota). Pivot (na pivotIndex) jest ju¿ na swoim miejscu i nie bierze
    // udzia¿u w dalszym sortowaniu.

    // Wywo¿anie dla lewej cz¿¿ci
    quickSort(arr, low, pivotIndex - 1);

    // Wywo¿anie dla prawej cz¿¿ci
    quickSort(arr, pivotIndex + 1, high);

  } else {
    std::cout << "  Zakres [" << low << ", " << high
              << "] ma <= 1 element - warunek bazowy, brak sortowania."
              << std::endl;
  }
}

int partition(std::vector<int> &arr, int low, int high) {
  //  Wybieramy PIVOT. Tutaj wybieramy ostatni element podtablicy jako
  //   pivot. To jedna z popularnych strategii.
  int pivotValue = arr[high];
  std::cout << "  Partycjonowanie od " << low << " do " << high
            << ". Pivot = " << pivotValue << std::endl;

  //'i' to indeks wskazuj¿cy na ostatni element, który byc MNIEJSZY
  // lub RÓWNY pivotowi. Zaczyna tuZ przed poczAtkiem rozwa¿anej podtablicy.
  int i = low - 1;

  // Komentarz: Przechodzimy przez podtablic¿ od 'low' do 'high-1' (wszystko
  // oprócz pivota). 'j' jest indeksem bie¿¿co sprawdzanego elementu.
  for (int j = low; j < high; ++j) {
    // Komentarz: Sprawdzamy, czy bie¿¿cy element (arr[j]) jest mniejszy lub
    // równy pivotowi.
    if (arr[j] <= pivotValue) {
      // Komentarz: Je¿li tak, to znaczy, ¿e ten element powinien znale¿¿ si¿ w
      // "lewej" cz¿¿ci (mniejszych od pivota). Zwi¿kszamy 'i' (przesuwamy
      // granic¿ lewej cz¿¿ci) i zamieniamy element arr[i] z arr[j].
      i++;
      swap(arr, i, j);
      std::cout << "    Zamiana " << arr[i] << " (" << i << ") z " << arr[j]
                << " (" << j << "): ";
      printArray(arr);
    }
    // Komentarz: Je¿li arr[j] jest wi¿kszy od pivota, nic nie robimy - 'j'
    // idzie dalej, a element arr[j] zostaje na razie w "prawej" cz¿¿ci.
  }

  // Po przej¿ciu p¿tli, wszystkie elementy od 'low' do 'i' s¿ <=
  // pivot. Elementy od 'i+1' do 'high-1' s¿ > pivot. Teraz musimy umie¿ci¿
  // pivot (który jest nadal na pozycji 'high') na jego w¿a¿ciwym miejscu.
  // W¿a¿ciwe miejsce to tu¿ po ostatnim elemencie mniejszym lub równym
  // pivotowi, czyli na pozycji 'i+1'. Zamieniamy arr[i+1] z pivotem
  // (arr[high]).
  swap(arr, i + 1, high);
  std::cout << "    Umieszczenie pivota (" << arr[i + 1] << ") na pozycji "
            << i + 1 << ": ";
  printArray(arr);

  // zwracam ci indeks, na którym OSTATECZNIE znalazl sie pivot.
  // Ten indeks podzieli tablice na dwie cz¿¿ci do dalszego sortowania.
  return i + 1;
}
