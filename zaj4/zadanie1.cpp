#include <iostream>
// #define int std:: string;
#include <chrono>
#include <string>
#include <vector>
using namespace std;
using namespace std::chrono;
class Person {
private:
  string lastName;
  string firstName;
  int age;

public:
  Person(string last, string first, int a)
      : lastName(last), firstName(first), age(a) {}

  void displayPerson() {
    cout << " //Last Name: " << lastName;
    cout << " //First Name: " << firstName;
    cout << " //Age: " << age << endl;
  }
  string getLast() { return lastName; }
}; // pamietaj o zakonczeniu klasy

class ArrayInOb {
private:
  vector<Person *> v; // vector of pointers to Person vector
  int nElems;

public:
  ArrayInOb(int max) : nElems(0) { v.resize(max); }
  // funckcja do wstawiania osoby do tablicy.
  void insert(string last, string first, int age) {
    v[nElems] = new Person(last, first, age);
    nElems++;
  }
  // funckcja do wyswietlania elementów tablicy
  void display() {
    for (int j = 0; j < nElems; j++) {
      cout << v[j];
      v[j]->displayPerson();
    }
  }
  // funkcja do uruchamiania sortowania przez wstawienie
  // insertion sort
  void insertionSort() {
    int in, out; // zmienne in element w tablicy wewnetrznej
    /*
 out = 1 ponieważ sortujesz do niego, wyciągasz pierwszy element i
    sobie sprawdzasz czy kolejny element jest przed czy po nim
    */
    for (out = 1; out < nElems; out++) {
      Person *temp = v[out];
      in = out;

      while (in > 0 && v[in - 1]->getLast() > temp->getLast()) {
        v[in] = v[in - 1];
        --in;
      }
      v[in] = temp;
    }
  } // zakonczenie insertion sort
};
int main() {
  int maxSize = 6001;
  ArrayInOb arr(maxSize);
  for (int i = 0; i < 1000; i++) {
    arr.insert("Jasny", "Gwint", i + 1);
    arr.insert("Dave", "Bajo", i + 2);
    arr.insert("Fajny", "Gwint", i + 3);
    arr.insert("Szary", "Gwint", i + 4);
    arr.insert("Niebieski", "Gwint", i + 5);
    arr.insert("Ciemny", "Gwint", i + 6);
  }
  cout << "Before sorting: " << endl;
  // arr.display();
  //---------------------------------------
  // Pomiar czasu - start
  auto start = high_resolution_clock::now();
  // Funkcja, której czas mierzymy
  arr.insertionSort();
  // Pomiar czasu - stop
  auto stop = high_resolution_clock::now();
  cout << "After sorting: " << endl;
  //---------------------------------------
  // arr.display();

  // Wyświetlenie wyników pomiarów czasu
  // Obliczenie różnicy czasu
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Cpp: Sorting time dla 1000*6 elementow: " << duration.count()
       << "milisekund, " << duration.count() / 1000 << endl;
  return 0;
}
