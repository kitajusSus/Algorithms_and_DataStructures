#include <iostream>


using namespace std;

/* samoreferecnyjna lista 
class Linked{
  public :
    int data;
    double dData;
    Link* pNext;
};


//to jest to samo ale inaczej,  inventory item to jest wskaźnik do obiektu przechowującego dane
class Link{
  public; 
    inventoryItem* pIteam;
    Link* pNext;
};
*/
class Link{
    public:
      int iData;
      double dData;
      Link* pNext;


      // creates linked list
      Link(int id, double dd): iData(id), dData(dd), pNext(NULL){
      
      }
      /*
      niżej zamieszczona funkcja pozwala na wyswietlanie danych z obiektu typu Link2,
      Konstruktor inicjalizuje dane, nie ma potrzeby inicjalizowania pola  
      pNNext gdyż...
      jest automatycznie ustawiony NULL, (u nas w kodzie jest ustawiony na 
      NULL manualnie dla wiekszej przejrzystosci kodu elo)
      narazie null nie jest odnośnikiem do czegokolwiek, 
      (to taki pusty slot który moze być odnośnikiem do czegoś potem)
      */
      void displayLink(){
        cout<<"{"<< iData<<", "<<dData<<"}";
      }
};

class LinkedList{
  private:
    Link* pFirst;
  public:
    LinkedList(): pFirst(NULL){
    }
    bool isEmpty(){
      return pFirst == NULL;
    }
    // wstawia nowy obiekt link na początek listy, 
    // jest to dosyć łatwe ponieważ  `pFirst` już pokazuje na pierwszy obiekt `Link`
    // Aby wstawić nowy obiekt (link) potrzeba
    // - ustawić zmienną pNext w nowo utworzonym obiekcie `link` tak aby wskazywała na obiekt `link`.
    // który był pierwszy (uprzednio)
    // - zmienić pFirst() tak aby wskazywał na nowo utworzony `link`. 
    void insertFirst(int id, double dd){ 
      // Metoda ta została zrobiona tak by pozwalała na przesłanie do niej argumentow (Przez Wartość)
      // typu `int` i `double`. (Ponieważ takie zmienne ustawiliśmy w `private`  w `Link`)
      // Następnie zmienia się obiekt `link` w powyżej opisany sposób. 
      Link* pNewLink = new Link(id,dd); 
      pNewLink -> pNext = pFirst; //newLink --> poprzedni pierwszy
      pFirst = pNewLink; // pierwszy --> newLink
    }
    //usuwa pierwszy link
    void removeFirst(){
      Link* pTemp = pFirst; //(1)zapisuje pierwszy 
      pFirst = pFirst -> pNext; //(2) odlinkowywuje to: pierwsyz -> stary kolejny
      delete pTemp; //(3) usuwa stary pierwszy. 
    }
    /*
    Aby zapobiec `memory leak` potrzeba usunąć obiekt link z paimęci,
     w tym celu wcześniej tworzymy tymczasową zmienną wskaźnikową do obiektu 
  (1) link,  a następnie po reorganizacji listy (2) usuwamy obiekt z pamięci (3)
    */
   
    void displayList(){
      cout<<"Lista (pierwsza -> ostatnia): ";
      Link* pCurrent = pFirst;
      while(pCurrent != NULL){
        pCurrent -> displayLink();
        pCurrent = pCurrent -> pNext;
      }
      cout<<endl;
    }
};


int main() {
  // Utworzenie nowej pustej listy
  LinkedList lista;
  
  // Sprawdzenie czy lista jest pusta
  cout << "Czy lista jest pusta? " << (lista.isEmpty() ? "Tak" : "Nie") << endl;
  
  // Dodawanie elementów na początek listy
  cout << "\nDodawanie elementów do listy:" << endl;
  lista.insertFirst(22, 2.99);    // Dodajemy {22, 2.99}
  lista.insertFirst(44, 4.99);    // Dodajemy {44, 4.99}
  lista.insertFirst(66, 6.99);    // Dodajemy {66, 6.99}
  lista.insertFirst(88, 8.99);    // Dodajemy {88, 8.99}
  
  // Wyświetlenie listy po dodaniu elementów
  lista.displayList();
  
  // Sprawdzenie czy lista jest pusta po dodaniu elementów
  cout << "\nCzy lista jest pusta? " << (lista.isEmpty() ? "Tak" : "Nie") << endl;
  
  // Usuwanie pierwszego elementu
  cout << "\nUsuwanie pierwszego elementu..." << endl;
  lista.removeFirst();
  lista.displayList();
  
  // Dodanie nowego elementu na początek
  cout << "\nDodanie nowego elementu na początek..." << endl;
  lista.insertFirst(99, 9.99);    // Dodajemy {99, 9.99}
  lista.displayList();
  
  // Demonstracja usuwania wszystkich elementów
  cout << "\nUsuwanie wszystkich elementów z listy:" << endl;
  while (!lista.isEmpty()) {
      lista.removeFirst();
      lista.displayList();
  }
  
  // Sprawdzenie końcowego stanu listy
  cout << "\nCzy lista jest pusta? " << (lista.isEmpty() ? "Tak" : "Nie") << endl;
  
  return 0;
}


