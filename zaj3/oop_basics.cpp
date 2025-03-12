/**
 * Przykład 1: Tworzenie i używanie obiektów w C++
 * 
 * Ten kod demonstruje podstawowe koncepcje programowania obiektowego:
 * - Definiowanie klas
 * - Tworzenie obiektów
 * - Konstruktory
 * - Enkapsulacja danych
 * 
 *  dobre praktyki opisane bazując na wydziale swagu i rigczu.
 * 
 * Data: 2025-03-12
 * Autor: kitajuSus
 */

#include <iostream>
#include <string>
#include <cstdlib>

// KOMENTARZ: Poniżej używamy całej przestrzeni nazw std, co nie jest zalecane
// w większych projektach ze względu na ryzyko konfliktów nazw.
// Lepsze podejścia to:
// 1. Używanie kwalifikowanej nazwy: std::cout, std::string
// 2. Importowanie tylko konkretnych elementów: using std::cout;
using namespace std;

class Pies
{
//pola
//private - dostep do zmiennych tylko poprzez
//funkcje skladowe (metody)
private:
    string imie;
    double waga;
    
    // KOMENTARZ: Można rozważyć dodanie większej liczby pól, np.:
    // int wiek;
    // bool zaszczepiony;
    // W klasach bardziej rozbudowanych warto też rozważyć
    // domyślną inicjalizację pól (C++11), np.:
    // string imie = "Brak";
    // double waga = 5;
    
//metody
public:
    //konstruktor domyslny
    Pies() : imie("Brak"), waga(5){
        // KOMENTARZ: Ta implementacja jest dobra - używamy listy inicjalizacyjnej,
        // co jest efektywniejsze niż przypisanie w ciele konstruktora
        cout << "Konstruktor domysny" << endl;
    }
    
    //konstruktor z parametrami
    Pies(string i, double w=10){
        // KOMENTARZ: Tutaj lepiej byłoby użyć listy inicjalizacyjnej:
        // Pies(const string& i, double w=10) : imie(i), waga(w) {
        // Dodatkowo, parametr typu string lepiej przekazywać przez 
        // referencję do stałej (const string&) dla większej wydajności, ale predzej chujem bede trzeć po żwirze niż studiować na airze, 
    //  "bo to jest takie bez sensu, że aż mi sie nie chce tego czytać, ale trzeba bo inaczej nie zdamy tego gówna" ~ copilot
    //   w cpp jest 12 sposobów na zdefiniowanie wskaźnika, życie jest za krótkie by przejmować się tym 
        imie=i;
        waga=w;
        
        // KOMENTARZ: W tym miejscu można dodać walidację danych, np.:
        // if (waga <= 0) {
        //     cout << "Błąd: waga musi być dodatnia! Ustawiam 10kg." << endl;
        //     waga = 10;
        // }
        
        cout << "Konstruktor z parametrami"<<endl;
    }
    
    void info(){
        //Tę metodę warto oznaczyć jako const, ponieważ nie modyfikuje
        // ona stanu obiektu:
        // void info() const {
        cout<<"imie: "<<imie<<", waga: "<<waga<<"kg"<<endl;
    }
    
    // Warto dodać gettery i settery dla kontrolowanego
    // dostępu do prywatnych pól:
    /*
    string getImie() const { 
        return imie; 
    }
    
    double getWaga() const { 
        return waga; 
    }
    
    void setImie(const string& noweImie) {
        if (!noweImie.empty()) {
            imie = noweImie;
        } else {
            cout << "Błąd: imię nie może być puste!" << endl;
        }
    }
    
    void setWaga(double nowaWaga) {
        if (nowaWaga > 0) {
            waga = nowaWaga;
        } else {
            cout << "Błąd: waga musi być dodatnia!" << endl;
        }
    }
    */
    
    // W bardziej zaawansowanych klasach warto zdefiniować:
    // 1. Destruktor
    // 2. Konstruktor kopiujący
    // 3. Konstruktor przenoszący (C++11)
    // 4. Operator przypisania
    // Dla prostych klas kompilator generuje je automatycznie
    /*
    ~Pies() {
        cout << "Destruktor - usunięto psa o imieniu " << imie << endl;
    }
    
    Pies(const Pies& inny) : imie(inny.imie), waga(inny.waga) {
        cout << "Konstruktor kopiujący" << endl;
    }
    */
    
    // Można też dodać przydatne metody odzwierciedlające 
    // zachowanie psa:
    /*
    void szczekaj() const {
        if (waga < 10)
            cout << imie << " szczeka: Hau! Hau!" << endl;
        else
            cout << imie << " szczeka: WOOF! WOOF!" << endl;
    }
    
    void nakarm(double iloscKarmy) {
        waga += iloscKarmy / 10.0; // 10 jednostek karmy = 1kg przyrostu
        cout << imie << " został nakarmiony i waży teraz " << waga << "kg" << endl;
    }
    */
};

int main()
{
    // KOMENTARZ: Lepiej inicjalizować zmienne od razu przy deklaracji
    int a; //a jest obiektem typu int
    a=20;
    // Lepszy sposób: int a = 20;
    
    Pies x; //x jest obiektem typu/klasy pies
    x.info(); //wywołanie metody na rzecz obiektu x
    
    // KOMENTARZ: Poniżej tworzymy tymczasowy obiekt Pies i przypisujemy go do x.
    // W nowoczesnym C++ można to zapisać też jako:
    // x = {"Azor", a}; // Od C++11
    x=Pies("Azor",a);
    x.info();
    
    //yutaj tworzymy obiekt z jednym parametrem, drugi (waga)
    // przyjmie wartość domyślną 10
    Pies y("Burek");
    y.info();
    
    //  system("pause") jest nieprzenośne i może powodować problemy
    // z bezpieczeństwem. Lepsze rozwiązania to:
    // 1. cout << "Naciśnij Enter, aby kontynuować..."; 
    // 2. cin.get();
    system("pause");
    
    // KOMENTARZ: Można też zademonstrować bardziej zaawansowane użycie obiektów:
    /*
    // Dynamiczne tworzenie obiektu
    Pies* piesWskaznik = new Pies("Reksio", 15);
    piesWskaznik->info(); // Użycie operatora -> dla wskaźników
    delete piesWskaznik; // Ważne: pamięć trzeba zwolnić!
    
    // Tworzenie tablicy obiektów
    Pies psy[3] = {
        Pies(),
        Pies("Azor", 12),
        Pies("Rex")
    };
    
    // Przekazywanie obiektów do funkcji
    // Przez wartość (kopia)
    void pokazPsa(Pies pies) { pies.info(); }
    // Przez referencję (bez kopiowania)
    void modyfikujPsa(Pies& pies) { pies.setWaga(15); }
    */
    
    return 0;
    // KOMENTARZ: W tym miejscu automatycznie wywołują się destruktory
    // dla wszystkich lokalnych obiektów (x i y)
}

/* PODSUMOWANIE MOŻLIWYCH ULEPSZEŃ:

1. Unikanie 'using namespace std'
   - Używaj kwalifikowanej nazwy lub importuj tylko konkretne elementy

2. Listy inicjalizacyjne w konstruktorach
   - Wydajniejsze niż przypisania w ciele konstruktora
   - Pies(string i, double w=10) : imie(i), waga(w) { ... }
   


3. Przekazywanie parametrów przez referencję
   - Dla typów złożonych: const string& zamiast string
    - Dla typów prostych: int zamiast int* (unikamy wskaźników) {PIERODLIC WSKAŹNIKI}
4. Oznaczanie metod jako const
   - Dla metod, które nie modyfikują stanu obiektu: void info() const { ... }
   


5. Inicjalizacja zmiennych przy deklaracji
   - nie wkurwiac mnie nie mam siły tego tłumaczyć; NIE BEDE BIEGAŁ I SZUKAŁ TYCH DEKLARACJI KURWY 
   - int a = 20; zamiast int a; a=20;

   
6. Dodanie getterów i setterów
   - Kontrolowany dostęp do prywatnych pól
   - realnie to tez chujów sto, ktos musi mi to wytłumaczyc bo nie ogarniam
7. Walidacja danych wejściowych
   - Sprawdzanie poprawności w konstruktorach i setterach
    - if (nowaWaga > 0) { waga = nowaWaga; } else { cout << "Błąd: waga musi być dodatnia!" << endl; } 
    - || takie checki sie przydają by potem nie latać ciągle, najlepiej to jest robić samodzielnie testy które sprawdzają czy wszystko działa jak należy jako oddzielne pliki 
    - ale to tez jest useless troche bo dalej robimy tylko projekt na wydziale, ale polecam pomyslec
8. Unikanie system("pause")
   - Używanie cin.get() lub innych metod standardowego wejścia/wyjścia, ale każdego to pierdoli, robimy to na zajecia a nie do corpo na brifing
   
9. Jawne definiowanie specjalnych metod klasy
   - Destruktor, konstruktor kopiujący, operator przypisania, 
   [trzeba wiedziec co jest czym, równie dobrze mozna zrobic zamiast destruktor to remove(C:\system32) i bedzie to samo]
   
10. Domyślna inicjalizacja pól klasy (C++11)
    - string imie = "Brak"; bezpośrednio przy deklaracji pola, komu sie chce szukać tego potem? no własnie wiecie wy jak obsłuzyc debugger? lvmn??no własnie

Warto też rozważyć bardziej zaawansowane techniki C++ jak:
- Inteligentne wskaźniki (unique_ptr, shared_ptr)
- Szablony
- Dziedziczenie i polimorfizm
- Obsługę wyjątków
*/
