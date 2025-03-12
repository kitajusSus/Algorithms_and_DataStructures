/**
 * Przykład 1: Tworzenie nowych obiektów w C++
 * 
 * Ten program demonstruje podstawowe pojęcia związane z tworzeniem obiektów:
 * - Definiowanie klas
 * - Konstruktory (domyślny i z parametrami)
 * - Enkapsulacja danych (pola prywatne)
 * - Tworzenie obiektów na różne sposoby
 * - Metody klasy i ich wywoływanie
 */

#include <iostream>
#include <string>
#include <vector>   // Do przechowywania kolekcji obiektów
#include <memory>   // Do inteligentnych wskaźników

using namespace std;

// =====================================================
// Definicja klasy Pies - to nasz "przepis" na obiekty
// =====================================================
class Pies
{
// CZĘŚĆ PRYWATNA - niedostępna bezpośrednio spoza klasy
private:
    // Pola (zwane też zmiennymi składowymi lub atrybutami)
    // Te dane są "ukryte" - to jest ENKAPSULACJA
    string imie;       // Imię psa
    double waga;       // Waga psa w kilogramach
    int wiek;          // Wiek psa w latach
    bool zaszczepiony; // Czy pies jest zaszczepiony
    
    // Stała statyczna - wspólna dla wszystkich obiektów klasy
    static const int MAX_WIEK = 20;

// CZĘŚĆ PUBLICZNA - interfejs klasy dostępny dla świata zewnętrznego
public:
    // =============================================
    // KONSTRUKTORY - specjalne metody do tworzenia obiektów
    // =============================================
    
    /**
     * Konstruktor domyślny - wywoływany gdy tworzymy obiekt bez parametrów
     * 
     * Lista inicjalizacyjna (po dwukropku) to preferowany sposób inicjalizacji pól,
     * bo jest wydajniejszy niż przypisania w ciele konstruktora.
     */
    Pies() : imie("Brak"), waga(5), wiek(1), zaszczepiony(false) {
        // Ten kod wykonuje się po inicjalizacji pól
        cout << "👋 Hej! Wywołano konstruktor domyślny" << endl;
        // Możemy tu wykonać dowolne operacje potrzebne podczas tworzenia obiektu
    }
    
    /**
     * Konstruktor z parametrami - pozwala na ustawienie pól podczas tworzenia obiektu
     * 
     * Zauważ parametr 'w' z wartością domyślną 10 - jest opcjonalny przy wywołaniu!
     */
    Pies(string i, double w = 10, int lata = 1, bool szczepienie = false) {
        cout << "👋 Hej! Wywołano konstruktor parametryczny" << endl;
        
        // Przypisanie wartości do pól + ewentualna walidacja
        if (i.empty()) {
            imie = "Nieznany";
            cout << "⚠️ Podano puste imię! Ustawiam 'Nieznany'" << endl;
        } else {
            imie = i;
        }
        
        // Sprawdzamy czy waga jest sensowna
        if (w <= 0) {
            waga = 10; // Wartość domyślna, jeśli podano nieprawidłową
            cout << "⚠️ Waga musi być większa od 0! Ustawiam domyślne 10kg" << endl;
        } else {
            waga = w;
        }
        
        // Sprawdzamy czy wiek jest sensowny
        if (lata < 0 || lata > MAX_WIEK) {
            wiek = 1;
            cout << "⚠️ Wiek musi być między 0 a " << MAX_WIEK << "! Ustawiam 1 rok" << endl;
        } else {
            wiek = lata;
        }
        
        zaszczepiony = szczepienie;
    }
    
    /**
     * Konstruktor kopiujący - tworzy nowy obiekt jako kopię istniejącego
     * 
     * Ten konstruktor jest wywoływany automatycznie przy kopiowaniu obiektu,
     * ale możemy go zdefiniować, aby mieć większą kontrolę nad procesem kopiowania.
     */
    Pies(const Pies& innyPies) : imie(innyPies.imie + " (kopia)"),
                                waga(innyPies.waga),
                                wiek(innyPies.wiek),
                                zaszczepiony(innyPies.zaszczepiony) {
        cout << "📋 Wywołano konstruktor kopiujący - skopiowano psa o imieniu " 
             << innyPies.imie << endl;
    }
    
    /**
     * Destruktor - wywoływany automatycznie gdy obiekt jest niszczony
     * 
     * Przydatny do zwalniania zasobów, zamykania plików, itp.
     */
    ~Pies() {
        cout << "👋 Żegnaj! Destruktor dla psa o imieniu " << imie << endl;
    }
    
    // =============================================
    // METODY - funkcje działające na danych klasy
    // =============================================
    
    /**
     * Prosta metoda wyświetlająca informacje o psie
     */
    void info() {
        cout << "--- Informacje o psie ---" << endl;
        cout << "Imię: " << imie << endl;
        cout << "Waga: " << waga << " kg" << endl;
        cout << "Wiek: " << wiek << " lat" << endl;
        cout << "Szczepienia: " << (zaszczepiony ? "tak" : "nie") << endl;
        cout << "------------------------" << endl;
    }
    
    /**
     * Metoda symulująca szczekanie psa - zachowanie zależy od wagi
     */
    void szczekaj() {
        cout << "🐶 " << imie << " szczeka: ";
        
        // Zachowanie zależy od wagi psa - mały piesek szczeka inaczej niż duży
        if (waga < 10) {
            cout << "Hau! Hau!" << endl;
        } else if (waga < 25) {
            cout << "Woof! Woof!" << endl;
        } else {
            cout << "WRRRR! HAU! HAU!" << endl;
        }
    }
    
    /**
     * Metoda zmieniająca imię psa (setter)
     */
    void zmienImie(string noweImie) {
        if (noweImie.empty()) {
            cout << "⚠️ Nowe imię nie może być puste!" << endl;
            return;
        }
        cout << "🔄 Zmieniam imię z " << imie << " na " << noweImie << endl;
        imie = noweImie;
    }
    
    /**
     * Metoda do karmienia psa - zwiększa wagę
     */
    void nakarm(double iloscKarmy) {
        if (iloscKarmy <= 0) {
            cout << "⚠️ Ilość karmy musi być dodatnia!" << endl;
            return;
        }
        
        // Zwiększamy wagę - 10 jednostek karmy = 1kg przyrostu
        double przyrost = iloscKarmy / 10.0;
        waga += przyrost;
        
        cout << "🍖 " << imie << " zjadł " << iloscKarmy 
             << " jednostek karmy i przytył " << przyrost << "kg" << endl;
        cout << "   Aktualna waga: " << waga << "kg" << endl;
    }
    
    /**
     * Metoda do zabawy z psem/Mosiejem - zmniejsza wagę
     */
    void bawSie(int minuty) {
        if (minuty <= 0) {
            cout << "⚠️ Czas zabawy musi być dodatni!, bo tak [sprawdz lini 179 około]" << endl;
            return;
        }
        
        // Zmniejszamy wagę - 30 minut zabawy = 0.5kg spadku wagi
        double spadekWagi = minuty / 60.0;
        
        // Nie pozwalamy, żeby pies schudł poniżej 1kg!
        if (waga - spadekWagi < 1.0) {
            cout << "⚠️ " << imie << " jest zbyt zmęczony na dalszą zabawę!" << endl;
            return;
        }
        
        waga -= spadekWagi;
        cout << "🎾 " << imie << " bawił się przez " << minuty 
             << " minut i schudł " << spadekWagi << "kg" << endl;
        cout << "   Aktualna waga: " << waga << "kg" << endl;
    }
    
    /**
     * Metoda do szczepienia psa
     */
    void zaszczep() {
        if (zaszczepiony) {
            cout << "💉 " << imie << " jest już zaszczepiony!" << endl;
        } else {
            zaszczepiony = true;
            cout << "💉 " << imie << " został zaszczepiony!" << endl;
        }
    }
    
    // Gettery - metody zwracające wartości pól prywatnych
    string getImie() const { return imie; }
    double getWaga() const { return waga; }
    int getWiek() const { return wiek; }
    bool czyZaszczepiony() const { return zaszczepiony; }
};

// =====================================================
// Funkcja pomocnicza do demonstracji przekazywania obiektów
// =====================================================

/**
 * Ta funkcja przyjmuje obiekt Pies przez wartość (tworzy kopię)
 */
void pokazPrzezWartość(Pies pies) {
    cout << "\n🔍 Wewnątrz funkcji pokazPrzezWartość()" << endl;
    cout << "   Otrzymałem kopię psa o imieniu: " << pies.getImie() << endl;
    pies.zmienImie("ZmienionePrzezFunkcję");
    pies.info();
    cout << "   Zaraz wyjdę z funkcji i kopia zostanie zniszczona!" << endl;
} // <- Tu wywołuje się destruktor dla kopii

/**
 * Ta funkcja przyjmuje referencję do obiektu Pies (nie tworzy kopii)
 */
void pokazPrzezReferencję(Pies& pies) {
    cout << "\n🔍 Wewnątrz funkcji pokazPrzezReferencję()" << endl;
    cout << "   Otrzymałem referencję do psa o imieniu: " << pies.getImie() << endl;
    pies.zmienImie("ZmienionePrzezReferencję");
    pies.info();
    cout << "   Zmiany wprowadzone tu wpłyną na oryginalny obiekt!" << endl;
} // <- Tu nie wywołuje się destruktor, bo to tylko referencja

// =====================================================
// FUNKCJA MAIN - początek programu
// =====================================================
int main()
{
    cout << "\n====== PRZYKŁAD TWORZENIA I UŻYWANIA OBIEKTÓW W C++ ======\n" << endl;
    
    // --------- Podstawowe tworzenie obiektów ---------
    
    cout << "\n--- 1. Tworzenie zmiennych podstawowych typów ---" << endl;
    int a;          // Deklaracja zmiennej typu int (bez inicjalizacji)
    a = 20;         // Inicjalizacja zmiennej
    cout << "Zmienna a (typ int): " << a << endl;
    
    cout << "\n--- 2. Tworzenie obiektu przy użyciu konstruktora domyślnego ---" << endl;
    Pies rex;       // Wywołuje konstruktor domyślny
    rex.info();     // Wywołanie metody info() na obiekcie rex
    
    cout << "\n--- 3. Tworzenie nowego obiektu i przypisanie do istniejącego ---" << endl;
    rex = Pies("Azor", a);  // Tworzy nowy obiekt z parametrami i przypisuje do rex
    rex.info();
    
    cout << "\n--- 4. Tworzenie obiektu z niepełnym zestawem parametrów ---" << endl;
    Pies burek("Burek");    // Tylko imię, reszta parametrów przyjmie wartości domyślne
    burek.info();
    
    // --------- Bardziej zaawansowane przykłady ---------
    
    cout << "\n--- 5. Używanie metod obiektu ---" << endl;
    burek.szczekaj();
    burek.nakarm(20);
    burek.bawSie(60);
    burek.zaszczep();
    burek.info();
    
    cout << "\n--- 6. Tworzenie kopii obiektu ---" << endl;
    Pies burek_kopia = burek;  // Używa konstruktora kopiującego
    burek_kopia.info();
    
    cout << "\n--- 7. Tworzenie obiektu z nieprawidłowymi danymi ---" << endl;
    Pies nieprawidlowy("", -5, 30, true);  // Nieprawidłowe imię, waga i wiek
    nieprawidlowy.info();
    
    cout << "\n--- 8. Dynamiczne tworzenie obiektu ---" << endl;
    Pies* piesWskaznik = new Pies("Reksio", 15, 3, true);
    cout << "Obiekt stworzony dynamicznie przez wskaźnik:" << endl;
    piesWskaznik->info();   // Operator -> do dostępu do składowych przez wskaźnik
    // Pamiętaj o zwolnieniu pamięci!
    delete piesWskaznik;    // To wywoła destruktor dla obiektu 'Reksio'
    cout << "Obiekt dynamiczny został usunięty" << endl;
    
    cout << "\n--- 9. Inteligentny wskaźnik (C++11 i nowsze) ---" << endl;
    unique_ptr<Pies> mądryWskaźnik = make_unique<Pies>("Saba", 8, 2, false);
    mądryWskaźnik->info();
    mądryWskaźnik->szczekaj();
    // Nie ma potrzeby używania delete - pamięć zostanie zwolniona automatycznie!
    
    cout << "\n--- 10. Kolekcja obiektów ---" << endl;
    vector<Pies> psyWektora;
    psyWektora.push_back(Pies("Pluto", 7));
    psyWektora.push_back(Pies("Scooby", 40));
    psyWektora.push_back(Pies("Lessie", 15, 5, true));
    
    cout << "Psy w wektorze:" << endl;
    for(int i = 0; i < psyWektora.size(); i++) {
        cout << i+1 << ". ";
        psyWektora[i].info();
    }
    
    cout << "\n--- 11. Przekazywanie obiektów do funkcji ---" << endl;
    cout << "\nPrzed wywołaniem funkcji pokazPrzezWartość():" << endl;
    rex.info();
    pokazPrzezWartość(rex);  // Przekazanie przez wartość - tworzy kopię
    cout << "\nPo wywołaniu funkcji pokazPrzezWartość():" << endl;
    rex.info();  // Obiekt rex nie zmienił się
    
    cout << "\nPrzed wywołaniem funkcji pokazPrzezReferencję():" << endl;
    burek.info();
    pokazPrzezReferencję(burek);  // Przekazanie przez referencję - nie tworzy kopii
    cout << "\nPo wywołaniu funkcji pokazPrzezReferencję():" << endl;
    burek.info();  // Obiekt burek został zmieniony
    
    cout << "\n====== KONIEC PROGRAMU ======\n" << endl;
    // Tu wszystkie lokalne obiekty zostaną zniszczone automatycznie
    // i wywołają się ich destruktory
    
    return 0;
}
