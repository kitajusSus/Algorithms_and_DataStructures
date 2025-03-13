//demonstrates array class with low-level interface 
#include <iostream> 
#include <vector> 
using namespace std; 
//////////////////////////////////////////////////////////////// 
class LowArray 
{ 
    private: 
        vector<double> v;                   //vector holds doubles 
 
    public: 
//-------------------------------------------------------------- 
    LowArray(int max)                       //constructor 
    { v.resize(max); }                      //size the vector 
//-------------------------------------------------------------- 
    void setElem(int index, double value)   //put element into 
    { v[index] = value; }                   //array, at index 
//-------------------------------------------------------------- 
    double getElem(int index)               //get element from 
    { return v[index]; }                    //array, at index 
    //-------------------------------------------------------------- 

 
};  //end class LowArray 
//////////////////////////////////////////////////////////////// 
int main() 
{ 
    LowArray arr(100);                      //create a LowArray 
    int nElems = 0;                         //number of items 
    int j;                                  //loop variable 
//-------------------------------------------------------------- 
    arr.setElem(0, 77);                     //insert 10 items 
    arr.setElem(1, 99); 
    arr.setElem(2, 44); 
    arr.setElem(3, 55); 
    arr.setElem(4, 22); 
    arr.setElem(5, 88); 
    arr.setElem(6, 11); 
    arr.setElem(7, 00); 
    arr.setElem(8, 66); 
    arr.setElem(9, 33); 
    nElems = 10;                            //now 10 items in array 
//-------------------------------------------------------------- 
    for(j=0; j<nElems; j++)                 //display items 
        cout << arr.getElem(j) << " "; 
    cout << endl; 
//-------------------------------------------------------------- 
    int searchKey = 26;                     //search for item 
    for(j=0; j<nElems; j++)                 //for each element, 
        if(arr.getElem(j) == searchKey)         //found item? 
            break; 
    if(j == nElems)                         //no 
        cout << "Can't find " << searchKey << endl; 
    else                                    //yes 
        cout << "Found " << searchKey << endl; 
//------------------------------------------------------------- 
    double deleteKey = 55;                  //delete value 55 
    cout << "Deleting element " << deleteKey << endl; 
    for(j=0; j<nElems; j++)                 //look for it 
        if(arr.getElem(j) == deleteKey) 
            break; 
    for(int k=j; k<nElems; k++)             //higher ones down 
        arr.setElem(k, arr.getElem(k+1) ); 
    nElems--;                               //decrement size 
//------------------------------------------------------------- 
    for(j=0; j<nElems; j++)                 //display items 
        cout << arr.getElem(j) << " "; 
    cout << endl; 
    return 0; 
}  //end main() 

/*Zamiast tablic użyliśmy klasy vector. Pod wieloma względami operacje na obiektach typu 
vector są podobne do operacji na tablicach. Użycie kasy vector pozwala nam na określenie 
rozmiaru wektora (ma to miejsce w konstruktorze klasy lowArray przy wykorzystaniu 
metody resize()). Pozwala to na przechowywanie dowolnej liczby danych w przeciwieństwie 
do tablic gdzie ograniczeni byliśmy do tej samej wielkości tablicy. 
 
W dalszej części często strukturę przechowującą dane (vector) nazywać będziemy po prostu 
tablicą.  
 
W klasie lowArray tablica jest ukryta przed światem zewnętrznym. Tylko funkcje składowe
 klasy lowArray mogą uzyskać dostęp do tablicy (private). Tymi funkcjami są: setElem(), 
getElem() oraz konstruktor.  
*/