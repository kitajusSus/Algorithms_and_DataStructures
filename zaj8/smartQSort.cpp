#include <cstdlib> // Dla rand() i srand()
#include <ctime>   // Dla time()
#include <iostream>
#include <memory> // Potrzebujemy tego pliku do mądrych wskaźników!
#include <vector>

// ... (Cała definicja klasy ArrayIns zostaje BEZ ZMIAN) ...
// class ArrayIns { ... };

// --- Główna część programu z użyciem unique_ptr ---
int main() {
  int maxSize = 16; // Maksymalna liczba zabawek

  // === Tworzenie obiektu ArrayIns na stercie za pomocą unique_ptr ===
  // Używamy std::make_unique - to najlepszy sposób.
  auto arr_ptr = std::make_unique<ArrayIns>(maxSize);
  // 'auto' samo wywnioskuje typ: std::unique_ptr<ArrayIns>
  std::cout << "Utworzono obiekt ArrayIns za pomocą unique_ptr." << std::endl;

  // Wkładamy losowe zabawki (używając ->)
  srand(time(NULL)); // Żeby losowanie było różne za każdym razem
  std::cout << "Wkładanie losowych zabawek..." << std::endl;
  for (int j = 0; j < maxSize; j++) {
    double n = rand() % 100; // Losowa zabawka od 0 do 99
    arr_ptr->insert(n);      // Używamy ->
  }

  std::cout << "\nZabawki przed sortowaniem:" << std::endl;
  // Używamy operatora -> zamiast . bo mamy wskaźnik (nawet jeśli mądry)
  arr_ptr->display();
  std::cout << std::endl;

  // Wywołujemy nasze super sortowanie (używając ->)!
  arr_ptr->quickSort(); // Używamy ->

  std::cout << std::endl;
  std::cout << "Zabawki po sortowaniu:" << std::endl;
  arr_ptr->display(); // Używamy ->

  std::cout << "\nKoniec funkcji main." << std::endl;
  return 0;
  // === MAGIA MĄDREGO WSKAŹNIKA ===
  // Tutaj 'arr_ptr' (unique_ptr) wychodzi z zasięgu.
  // Ponieważ jest mądry, automatycznie wywoła destruktor dla obiektu ArrayIns,
  // co oznacza zwolnienie pamięci zajmowanej przez ten obiekt.
  // Nie musimy pisać 'delete'!
}
