#include <iostream>
//#define int std:: string;
#include <vector>
#include <string>

using namespace std; 

class Person{
    private:
        string lastName;
        string firstName;
        int age;

    public:
        Person(string last, string first, int a):
            lastName(last), firstName(first), age(a){}

    void displayPerson(){
        cout<<" //Last Name: "<<lastName;
        cout<<" //First Name: "<< firstName;
        cout<<" //Age: "<< age<< endl;
    }
    string getLast() {
        return lastName;
    }
}; //pamietaj o zakonczeniu klasy

class ArrayInOb{
    private:
        vector<Person*> v; //vector of pointers to Person vector
        int nElems;

    public:
        ArrayInOb(int max) : nElems(0) {
            v.resize(max);
        }
    //funckcja do wstawiania osoby do tablicy. 
    void insert(string last, string first, int age){
        v[nElems] = new Person(last, first, age);
        nElems++;
    }
    //funckcja do wyswietlania elementów tablicy
    void display(){
        for(int j=0; j<nElems; j++){
            cout<< v[j]; v[j] -> displayPerson();
        }
    }
    // funkcja do uruchamiania sortowania przez wstawienie
    //insertion sort
    void insertionSort(){
           int in, out; //zmienne in element w tablicy wewnetrznej 
           /*
            out = 1 ponieważ sortujesz do niego, wyciągasz pierwszy element i 
           sobie sprawdzasz czy kolejny element jest przed czy po nim
           */
           for(out=1; out<nElems; out++){
                Person* temp = v[out];
                in = out;

                while(in>0 && v[in-1]-> getLast() > temp->getLast() ){
                    v[in] = v[in-1];
                    --in;
            }
            v[in] = temp;
           }
    }//zakonczenie insertion sort

};



int main(){
    int maxSize = 100; 
    ArrayInOb arr(maxSize);

    arr.insert("Jasny", "Gwint", 14);
    arr.insert("Dave", "Bajo", 15);
    arr.insert("Fajny", "Gwint", 2);
    arr.insert("Szary", "Gwint", 24);
    arr.insert("Niebieski", "Gwint", 134);
    arr.insert("Ciemny", "Gwint", 44);

    cout<<"Before sorting: "<<endl;
    arr.display();

    arr.insertionSort();

    cout<<"After sorting: "<<endl;
    arr.display();
    return 0;
}


















































































