// Krzysztof Bezubik kolokwium aisd 
// zadanie 1
// nr indeksu: 89219 
// Napisać program sprawdzająchy czy algorytm, sortowania przez wstawianie jest algorytmem stabilnym. 

#include <iostream>
// #define int std:: string;
#include <chrono>
#include <string>
#include <vector>
using namespace std;


class Person {
private:
  string lastName;
  string firstName;
  int age;
  int id;

public:
  Person(string last, string first, int a, int id): lastName(last), firstName(first), age(a), id(id) {

  }
  // int id: do zapamietywania  kiedy został dodany element
  void displayPerson() {
    cout << " //Last Name: " << lastName;
    cout << " //First Name: " << firstName;
    cout << " //Age: " << age;
    cout << "//numer "<< id<<endl;
  }
  string getLast() { return lastName; }
}; 

class ArrayInOb {
private:
  vector<Person *> v; // vector of pointers to Person vector
  int nElems;

public:
  ArrayInOb(int max) : nElems(0) { v.resize(max); }
  // funckcja do wstawiania osoby do tablicy.
  void insert(string last, string first, int age, int id) {
    v[nElems] = new Person(last, first, age, id);
    nElems++;
  }
  // funckcja do wyswietlania elementów tablicy
  void display() {
    for (int j = 0; j < nElems; j++) {
      //cout << v[j];
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
  int maxSize = 100;
  ArrayInOb arr(maxSize);
  
  //for (int i = 0; i < 13; i++) {
    int id = 0;
    arr.insert("Evans", "Patty",24, ++id);
    arr.insert("Smith", "Doc",59, ++id );
    arr.insert("Smith", "Lorraine",37,  ++id);
    arr.insert("Smith", "Paul",37,++id);
    arr.insert("Yee", "Tom",43, ++id);
    arr.insert("Hashimoto", "Sato",21,++id);
    arr.insert("Stimson", "Henry",29, ++id);
    arr.insert("Velasquez", "Jose", 72,++id);
    arr.insert("Vang", "Minh", 22,++id);
    arr.insert("Creswell","Patty", 18,++id);
  
  cout << "Przed sortowaniem: " << endl;
  arr.display();
  //---------------------------------------
  arr.insertionSort();
  //---------------------------------------
  cout << "After sorting: " << endl;
  /*
  Zakładając ze to jest algorytm stabilny to po arr display,
  elementy ktore maja te same imiona, powinny byc po sobie w takiej samej kolejnosci jak gdy były dodawane,
  mozna jeden smith dodac na poczatek inny w srodku a inny na koncu, a po posortowaniu bedą obok siebie w kolejnosci dodania.
  */
  arr.display();
  /*
    //Last Name: Smith //First Name: Doc //Age: 59//numer 2
    //Last Name: Smith //First Name: Lorraine //Age: 37//numer 3
    //Last Name: Smith //First Name: Paul //Age: 37//numer 4
  Jak widać algorytm sortowania przez wstawianie jest stabilny, 
  */

}
