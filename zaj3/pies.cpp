/**
 * @file oop_basics.cpp
 * @brief Przykład demonstrujący tworzenie i zarządzanie obiektami w C++
 * @author masny skibider
 * @date 2025-03-12
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * @brief Klasa reprezentująca psa
 * 
 * Klasa demonstruje różne aspekty tworzenia obiektów w C++, w tym:
 * - różne typy konstruktorów
 * - destruktor
 * - enkapsulację danych
 * - metody dostępowe (gettery i settery)
 * - stałe i statyczne składniki klasy
 */
class Pies {
private:
    // Pola prywatne - enkapsulacja danych
    std::string imie;       ///< Imię psa
    double waga;            ///< Waga psa w kilogramach
    int wiek;               ///< Wiek psa w latach
    bool szczepiony;        ///< Czy pies jest zaszczepiony
    
    // Składnik statyczny współdzielony przez wszystkie obiekty klasy
    static int licznik;     ///< Licznik utworzonych obiektów
    
    // Stała klasowa
    static const int MAKSYMALNY_WIEK = 25;  ///< Maksymalny wiek psa w latach
    
public:
    /**
     * @brief Konstruktor domyślny
     * 
     * Inicjalizuje obiekt z wartościami domyślnymi.
     * Demonstruje użycie listy inicjalizacyjnej.
     */
    Pies() : imie("Bezimienny"), waga(5.0), wiek(0), szczepiony(false) {
        std::cout << "Konstruktor domyślny - utworzono psa o imieniu " << imie << std::endl;
        licznik++;
    }
    
    /**
     * @brief Konstruktor z parametrami
     * 
     * @param i Imię psa
     * @param w Waga psa (domyślnie 10kg)
     * @param wk Wiek psa (domyślnie 1 rok)
     * @param szczep Status szczepienia (domyślnie true)
     * 
     * Demonstruje parametry z wartościami domyślnymi.
     */
    Pies(const std::string& i, double w = 10.0, int wk = 1, bool szczep = true) 
        : imie(i), szczepiony(szczep) {
        // Sprawdzenie poprawności danych wejściowych
        if (w > 0 && w < 100) {
            waga = w;
        } else {
            std::cout << "Podana waga jest nieprawidłowa. Ustawiono domyślną wartość 10kg." << std::endl;
            waga = 10.0;
        }
        
        if (wk >= 0 && wk <= MAKSYMALNY_WIEK) {
            wiek = wk;
        } else {
            std::cout << "Podany wiek jest nieprawidłowy. Ustawiono domyślną wartość 1 rok." << std::endl;
            wiek = 1;
        }
        
        std::cout << "Konstruktor z parametrami - utworzono psa o imieniu " << imie << std::endl;
        licznik++;
    }
    
    /**
     * @brief Konstruktor kopiujący
     * 
     * @param innyPies Referencja do kopiowanego obiektu
     * 
     * Demonstruje kopiowanie obiektów.
     */
    Pies(const Pies& innyPies) : imie(innyPies.imie + " (kopia)"),
                                waga(innyPies.waga),
                                wiek(innyPies.wiek),
                                szczepiony(innyPies.szczepiony) {
        std::cout << "Konstruktor kopiujący - utworzono kopię psa o imieniu " << innyPies.imie << std::endl;
        licznik++;
    }
    
    /**
     * @brief Konstruktor przenoszący (C++11)
     * 
     * @param innyPies Referencja do R-wartości przenoszonego obiektu
     * 
     * Demonstruje przenoszenie zamiast kopiowania dla wydajności.
     */
    Pies(Pies&& innyPies) noexcept : imie(std::move(innyPies.imie)),
                                   waga(innyPies.waga),
                                   wiek(innyPies.wiek),
                                   szczepiony(innyPies.szczepiony) {
        innyPies.imie = "Przeniesiony";
        innyPies.waga = 0;
        innyPies.wiek = 0;
        std::cout << "Konstruktor przenoszący - przeniesiono psa" << std::endl;
        licznik++;
    }
    
    /**
     * @brief Destruktor
     * 
     * Wywoływany automatycznie podczas niszczenia obiektu.
     */
    ~Pies() {
        std::cout << "Destruktor - zniszczono psa o imieniu " << imie << std::endl;
        licznik--;
    }
    
    // Gettery - metody dostępowe do pól prywatnych
    
    /**
     * @brief Pobiera imię psa
     * @return Imię psa jako string
     */
    std::string getImie() const { return imie; }
    
    /**
     * @brief Pobiera wagę psa
     * @return Waga psa w kilogramach
     */
    double getWaga() const { return waga; }
    
    /**
     * @brief Pobiera wiek psa
     * @return Wiek psa w latach
     */
    int getWiek() const { return wiek; }
    
    /**
     * @brief Sprawdza status szczepienia
     * @return true jeśli pies jest zaszczepiony, false w przeciwnym razie
     */
    bool czySzczepiony() const { return szczepiony; }
    
    // Settery - metody modyfikujące pola prywatne
    
    /**
     * @brief Ustawia imię psa
     * @param noweImie Nowe imię do ustawienia
     */
    void setImie(const std::string& noweImie) {
        if (!noweImie.empty()) {
            imie = noweImie;
            std::cout << "Zmieniono imię na " << imie << std::endl;
        } else {
            std::cout << "Błąd: imię nie może być puste" << std::endl;
        }
    }
    
    /**
     * @brief Ustawia wagę psa
     * @param nowaWaga Nowa waga w kilogramach
     * @return true jeśli zmiana się powiodła, false w przeciwnym razie
     */
    bool setWaga(double nowaWaga) {
        if (nowaWaga > 0 && nowaWaga < 100) {
            waga = nowaWaga;
            std::cout << "Zmieniono wagę na " << waga << "kg" << std::endl;
            return true;
        } else {
            std::cout << "Błąd: waga musi być między 0 a 100kg" << std::endl;
            return false;
        }
    }
    
    /**
     * @brief Ustawia wiek psa
     * @param nowyWiek Nowy wiek w latach
     * @return true jeśli zmiana się powiodła, false w przeciwnym razie
     */
    bool setWiek(int nowyWiek) {
        if (nowyWiek >= 0 && nowyWiek <= MAKSYMALNY_WIEK) {
            wiek = nowyWiek;
            std::cout << "Zmieniono wiek na " << wiek << " lat" << std::endl;
            return true;
        } else {
            std::cout << "Błąd: wiek musi być między 0 a " << MAKSYMALNY_WIEK << " lat" << std::endl;
            return false;
        }
    }
    
    /**
     * @brief Zmienia status szczepienia
     * @param status Nowy status szczepienia
     */
    void setSzczepienie(bool status) {
        szczepiony = status;
        std::cout << "Status szczepienia: " << (szczepiony ? "zaszczepiony" : "niezaszczepiony") << std::endl;
    }
    
    /**
     * @brief Operator przypisania
     * 
     * @param innyPies Pies, którego dane są kopiowane
     * @return Referencja do bieżącego obiektu
     * 
     * Demonstruje operator przypisania.
     */
    Pies& operator=(const Pies& innyPies) {
        if (this != &innyPies) {
            imie = innyPies.imie;
            waga = innyPies.waga;
            wiek = innyPies.wiek;
            szczepiony = innyPies.szczepiony;
            std::cout << "Operator przypisania - skopiowano dane z psa " << innyPies.imie << std::endl;
        }
        return *this;
    }
    
    /**
     * @brief Wyświetla informacje o psie
     * 
     * Metoda wyświetlająca wszystkie dane o psie.
     */
    void info() const {
        std::cout << "\n--- Informacje o psie ---" << std::endl;
        std::cout << "Imię: " << imie << std::endl;
        std::cout << "Waga: " << waga << "kg" << std::endl;
        std::cout << "Wiek: " << wiek << " lat" << std::endl;
        std::cout << "Status szczepienia: " << (szczepiony ? "zaszczepiony" : "niezaszczepiony") << std::endl;
        std::cout << "-----------------------\n" << std::endl;
    }
    
    /**
     * @brief Symuluje szczekanie psa
     */
    void szczekaj() const {
        std::cout << imie << " szczeka: ";
        if (waga < 7) {
            std::cout << "Hau! Hau!" << std::endl;
        } else if (waga < 20) {
            std::cout << "Woof! Woof!" << std::endl;
        } else {
            std::cout << "WRRR! HAU! HAU!" << std::endl;
        }
    }
    
    /**
     * @brief Symuluje karmienie psa
     * 
     * @param iloscKarmy Ilość karmy w gramach
     */
    void nakarm(int iloscKarmy) {
        if (iloscKarmy > 0 && iloscKarmy < 1000) {
            double przyrost = iloscKarmy / 1000.0;
            waga += przyrost;
            std::cout << imie << " zjadł " << iloscKarmy << "g karmy i przytył " << przyrost << "kg" << std::endl;
            std::cout << "Aktualna waga: " << waga << "kg" << std::endl;
        } else {
            std::cout << "Nieprawidłowa ilość karmy!" << std::endl;
        }
    }
    
    /**
     * @brief Symuluje zabawę z psem
     * 
     * @param czasWMinutach Czas zabawy w minutach
     */
    void bawSie(int czasWMinutach) {
        if (czasWMinutach > 0) {
            double ubytek = czasWMinutach * 0.01;
            if (ubytek < waga) {
                waga -= ubytek;
            } else {
                waga = waga / 2;
            }
            std::cout << imie << " bawił się przez " << czasWMinutach << " minut i schudł " << ubytek << "kg" << std::endl;
            std::cout << "Aktualna waga: " << waga << "kg" << std::endl;
        } else {
            std::cout << "Czas zabawy musi być dodatni!" << std::endl;
        }
    }
    
    /**
     * @brief Pobiera liczbę istniejących obiektów klasy Pies
     * 
     * @return Liczba utworzonych i niezniszczonych obiektów klasy Pies
     */
    static int getLicznikPsow() {
        return licznik;
    }
};

// Inicjalizacja składnika statycznego
int Pies::licznik = 0;

/**
 * @brief Funkcja pokazująca przekazywanie obiektów przez wartość
 * 
 * @param pies Obiekt przekazany przez wartość (tworzy kopię)
 */
void pokazPrzezWartość(Pies pies) {
    std::cout << "Funkcja otrzymała kopię psa o imieniu: " << pies.getImie() << std::endl;
    // Po wyjściu z funkcji kopia zostanie zniszczona
}

/**
 * @brief Funkcja pokazująca przekazywanie obiektów przez referencję
 * 
 * @param pies Referencja do obiektu (bez tworzenia kopii)
 */
void pokazPrzezReferencję(const Pies& pies) {
    std::cout << "Funkcja otrzymała referencję do psa o imieniu: " << pies.getImie() << std::endl;
    // Nie tworzy kopii, nie wywołuje się destruktor przy wyjściu
}

/**
 * @brief Funkcja główna programu
 * 
 * @return Kod powrotu do systemu operacyjnego
 */
int main() {
    std::cout << "=== Rozpoczęcie programu ===" << std::endl;
    std::cout << "Liczba psów na początku: " << Pies::getLicznikPsow() << std::endl;
    
    // Tworzenie obiektu za pomocą konstruktora domyślnego
    std::cout << "\n1. Tworzenie obiektu domyślnego:" << std::endl;
    Pies pies1;
    pies1.info();
    
    // Tworzenie obiektu za pomocą konstruktora z parametrami
    std::cout << "2. Tworzenie obiektu z pełnymi parametrami:" << std::endl;
    Pies pies2("Azor", 15.5, 3, true);
    pies2.info();
    
    // Tworzenie obiektu z domyślnymi wartościami dla niektórych parametrów
    std::cout << "3. Tworzenie obiektu z częściowymi parametrami (reszta domyślne):" << std::endl;
    Pies pies3("Burek");
    pies3.info();
    
    // Tworzenie kopii obiektu
    std::cout << "4. Tworzenie kopii obiektu:" << std::endl;
    Pies pies4 = pies2;  // używa konstruktora kopiującego
    pies4.info();
    
    // Przypisanie jednego obiektu do drugiego
    std::cout << "5. Przypisanie obiektu:" << std::endl;
    pies1 = pies2;       // używa operatora przypisania
    pies1.info();
    
    // Demonstracja metod
    std::cout << "6. Demonstracja metod obiektu:" << std::endl;
    pies3.szczekaj();
    pies3.nakarm(500);
    pies3.bawSie(30);
    pies3.info();
    
    // Dynamiczne tworzenie obiektu za pomocą wskaźnika
    std::cout << "\n7. Dynamiczne tworzenie obiektu (wskaźnik):" << std::endl;
    Pies* piesWsk = new Pies("Rex", 25.0, 5, false);
    piesWsk->info();
    piesWsk->setSzczepienie(true);
    piesWsk->info();
    
    // Usuwanie obiektu stworzonego dynamicznie
    std::cout << "8. Usuwanie obiektu dynamicznego:" << std::endl;
    delete piesWsk;
    
    // Tworzenie obiektu za pomocą inteligentnego wskaźnika (C++11)
    std::cout << "\n9. Tworzenie obiektu za pomocą inteligentnego wskaźnika:" << std::endl;
    std::unique_ptr<Pies> piesSmartPtr = std::make_unique<Pies>("Maks", 12.3, 2);
    piesSmartPtr->info();
    piesSmartPtr->szczekaj();
    
    // Tworzenie tablicy obiektów
    std::cout << "\n10. Tworzenie tablicy obiektów:" << std::endl;
    std::vector<Pies> psyVector;
    psyVector.push_back(Pies("Reksio", 8.5, 4));
    psyVector.push_back(Pies("Pluto", 12.0, 3));
    psyVector.emplace_back("Scooby", 30.0, 7);  // C++11 - konstruuje obiekt bezpośrednio
    
    std::cout << "Psy w wektorze:" << std::endl;
    for (const auto& pies : psyVector) {  // Iteracja po kolekcji za pomocą range-based for (C++11)
        std::cout << "- " << pies.getImie() << ", " << pies.getWaga() << "kg" << std::endl;
    }
    
    // Demonstracja przekazywania obiektów
    std::cout << "\n11. Przekazywanie obiektów do funkcji:" << std::endl;
    pokazPrzezWartość(pies1);      // Tworzy kopię obiektu
    pokazPrzezReferencję(pies1);   // Nie tworzy kopii
    
    std::cout << "\nLiczba psów przed zakończeniem main: " << Pies::getLicznikPsow() << std::endl;
    std::cout << "=== Zakończenie programu ===" << std::endl;
    
    return 0;
    // Na końcu funkcji main destruktory są wywoływane dla wszystkich lokalnych obiektów
}
