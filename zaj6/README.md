# Linked Lists w C++ - Przewodnik

## Spis treści
1. [Podstawowa implementacja](#1-podstawowa-implementacja)
2. [Rozszerzona implementacja z dodatkowymi operacjami](#2-rozszerzona-implementacja)
3. [Zaawansowana implementacja z sortowaniem](#3-zaawansowana-implementacja)


- [Pierwszy program przykladowy](linked_list.cpp)
- [ćwiczenie 2](zadanie2_listy.cpp)
## Wprowadzenie
Lista połączona (linked list) to struktura danych, w której każdy element (węzeł) zawiera dane oraz wskaźnik do następnego elementu. W przeciwieństwie do tablic, elementy listy połączonej nie muszą zajmować ciągłego obszaru w pamięci.


## 1. Podstawowa implementacja
Pierwsza implementacja pokazuje najprostszą wersję listy połączonej z podstawowymi operacjami.

```cpp
#include <iostream>

// Definicja struktury węzła
struct Node {
    int data;           // Przechowywana wartość
    Node* next;         // Wskaźnik na następny element
    
    // Konstruktor
    Node(int value) : data(value), next(nullptr) {}
};

// Klasa listy połączonej
class LinkedList {
private:
    Node* head;     // Wskaźnik na początek listy

public:
    // Konstruktor
    LinkedList() : head(nullptr) {}
    
    // Dodawanie elementu na początek listy
    void dodajNaPoczatek(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    // Wyświetlanie listy
    void wyswietl() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    
    // Destruktor - zwalnianie pamięci
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList lista;
    
    // Dodawanie elementów
    lista.dodajNaPoczatek(3);
    lista.dodajNaPoczatek(2);
    lista.dodajNaPoczatek(1);
    
    // Wyświetlanie listy
    std::cout << "Lista: ";
    lista.wyswietl();
    
    return 0;
}
```

Ten podstawowy przykład pokazuje:
- Definicję struktury węzła
- Podstawową implementację listy połączonej
- Dodawanie elementów na początek listy
- Wyświetlanie elementów
- Prawidłowe zwalnianie pamięci

## 2. Rozszerzona implementacja
Druga implementacja rozszerza możliwości listy o dodatkowe operacje.

```cpp
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}
    
    // Dodawanie na koniec listy
    void dodajNaKoniec(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    // Usuwanie elementu o zadanej wartości
    bool usun(int value) {
        if (head == nullptr) return false;
        
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        
        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Wyszukiwanie elementu
    bool znajdz(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Pobieranie rozmiaru listy
    int rozmiar() const {
        return size;
    }
    
    void wyswietl() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList lista;
    
    // Dodawanie elementów
    lista.dodajNaKoniec(1);
    lista.dodajNaKoniec(2);
    lista.dodajNaKoniec(3);
    lista.dodajNaKoniec(4);
    
    std::cout << "Lista początkowa: ";
    lista.wyswietl();
    
    // Usuwanie elementu
    lista.usun(2);
    std::cout << "Po usunięciu 2: ";
    lista.wyswietl();
    
    // Wyszukiwanie
    std::cout << "Czy 3 jest w liście? " << (lista.znajdz(3) ? "Tak" : "Nie") << std::endl;
    std::cout << "Czy 2 jest w liście? " << (lista.znajdz(2) ? "Tak" : "Nie") << std::endl;
    
    std::cout << "Rozmiar listy: " << lista.rozmiar() << std::endl;
    
    return 0;
}
```

Ta implementacja dodaje:
- Dodawanie elementów na koniec listy
- Usuwanie elementów o zadanej wartości
- Wyszukiwanie elementów
- Śledzenie rozmiaru listy

## 3. Zaawansowana implementacja
Trzecia implementacja wprowadza sortowanie i bardziej zaawansowane operacje.

```cpp
#include <iostream>
#include <stdexcept>

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;
    
    // Pomocnicza funkcja do łączenia posortowanych list
    Node* merge(Node* left, Node* right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        
        Node* result = nullptr;
        
        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }
        
        return result;
    }
    
    // Pomocnicza funkcja do podziału listy
    Node* getMiddle(Node* head) {
        if (head == nullptr) return nullptr;
        
        Node* slow = head;
        Node* fast = head->next;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // Rekurencyjna funkcja sortowania przez scalanie
    Node* mergeSort(Node* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        Node* middle = getMiddle(head);
        Node* nextToMiddle = middle->next;
        
        middle->next = nullptr;
        
        Node* left = mergeSort(head);
        Node* right = mergeSort(nextToMiddle);
        
        return merge(left, right);
    }

public:
    LinkedList() : head(nullptr), size(0) {}
    
    // Wstawianie z zachowaniem porządku
    void wstawPosortowane(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr || head->data >= value) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }
    
    // Sortowanie listy
    void sortuj() {
        head = mergeSort(head);
    }
    
    // Odwracanie listy
    void odwroc() {
        Node *prev = nullptr, *current = head, *next = nullptr;
        
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
    }
    
    // Usuwanie duplikatów (zakładając, że lista jest posortowana)
    void usunDuplikaty() {
        if (head == nullptr) return;
        
        Node* current = head;
        while (current->next != nullptr) {
            if (current->data == current->next->data) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
            } else {
                current = current->next;
            }
        }
    }
    
    void wyswietl() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList lista;
    
    // Dodawanie elementów w losowej kolejności
    lista.wstawPosortowane(5);
    lista.wstawPosortowane(3);
    lista.wstawPosortowane(8);
    lista.wstawPosortowane(3);
    lista.wstawPosortowane(1);
    
    std::cout << "Lista początkowa: ";
    lista.wyswietl();
    
    // Sortowanie listy
    lista.sortuj();
    std::cout << "Po sortowaniu: ";
    lista.wyswietl();
    
    // Usuwanie duplikatów
    lista.usunDuplikaty();
    std::cout << "Po usunięciu duplikatów: ";
    lista.wyswietl();
    
    // Odwracanie listy
    lista.odwroc();
    std::cout << "Po odwróceniu: ";
    lista.wyswietl();
    
    return 0;
}
```

Ta zaawansowana implementacja zawiera:
- Sortowanie przez scalanie (merge sort)
- Wstawianie z zachowaniem porządku
- Usuwanie duplikatów
- Odwracanie listy

## Podsumowanie
Powyższe przykłady pokazują ewolucję implementacji listy połączonej od najprostszej do bardziej złożonej wersji. Każdy kolejny przykład dodaje nowe funkcjonalności i pokazuje różne techniki operowania na strukturze danych.

Pamiętaj o najważniejszych aspektach przy pracy z listami połączonymi:
1. Prawidłowe zarządzanie pamięcią
2. Obsługa przypadków brzegowych (pusta lista, jeden element)
3. Zachowanie wskaźników przy modyfikacji listy
4. Efektywne implementowanie algorytmów

Listy połączone są fundamentalną strukturą danych, która znajduje zastosowanie w wielu praktycznych scenariuszach programistycznych.


# Abstrakcyjne typy danych w C++ - poradnaik. 


Dodatkowo przygotowałem poradnik i prezentacje czym jest alokacja pamieci w cpp (malloc) w cpp i w zig. [malloc poradnik](alokacja_pamieci\notatki.md)

