/*
przykład 5 (C++) Przykład klasy z tablicą zawierająca uporządkowane dane. W przykładzie 
tym do odnajdowania elementu zastosowane zostało przeszukiwanie binarne (tylko w 
przypadku posortowanych danych). 
*/

#include <iostream> 
#include <vector> 
using namespace std; 
////////////////////////////////////// 
class OrdArray { 
    private: 
        vector<double> v;          
        int nElems;                 
    public: 
//-------------------------------------------------------- 
    OrdArray(int max) : nElems(0)       //constructor 
    { v.resize(max); }                  //size the vector 
//-------------------------------------------------------- 
    int getSize()                       //return number of 
    { return nElems; }                  //elements 
//-------------------------------------------------------- 
    int find(double searchKey) 
    { 
        int lowerBound = 0; 
        int upperBound = nElems-1; 
        int curIn; 
 
        while(true) 
        { 
            curIn = (lowerBound + upperBound ) / 2; 
            if(v[curIn]==searchKey) 
                return curIn;               //found it 
            else if(lowerBound > upperBound) 
                return nElems;              //can’t find it 
            else                            //divide range 
            { 
                if(v[curIn] < searchKey) 
                    lowerBound = curIn + 1; //it’s in upper half 
                else 
                    upperBound = curIn - 1; //it’s in lower half 
            }  //end else divide range 
        }  //end while 
    }  //end find() 
//----------------------------------------------------------- 
    void insert(double value)               //put element into array 
    { 
        int j; 
        for(j=0; j<nElems; j++)             //find where it goes 
            if(v[j] > value)                //(linear search) 
                break; 
        for(int k=nElems; k>j; k--)         //move bigger ones up 
            v[k] = v[k-1]; 
        v[j] = value;                       //insert it 
        nElems++;                           //increment size 
    }  //end insert() 
//-----------------------------------------------------------  
    bool remove(double value) 
    { 
        int j = find(value); 
        if(j==nElems)                       //can’t find it 
            return false; 
        else                                //found it 
        { 
            for(int k=j; k<nElems; k++)     //move bigger ones down 
                v[k] = v[k+1]; 
            nElems--;                       //decrement size 
            return true; 
        } 
    }  //end remove() 
//----------------------------------------------------------- 
    void display(){                          //displays array contents  
        for(int j=0; j<nElems; j++)         //for each element, 
            cout << v[j] << " ";            //display it 
        cout << endl; 
    } 
//----------------------------------------------------------- 
};  //end class OrdArray 
//////////////////////////////////////////////////////////////// 
int main() 
{ 
    int maxSize = 100;               //array size 
    OrdArray arr(maxSize);           //create the array 
 
    arr.insert(77);                  //insert 10 items 
    arr.insert(99); 
    arr.insert(44); 
    arr.insert(55); 
    arr.insert(22); 
    arr.insert(88); 
    arr.insert(11); 
    arr.insert(00); 
    arr.insert(66); 
    arr.insert(33); 
 
    int searchKey = 55;              //search for item 
 
    if( arr.find(searchKey) != arr.getSize() ) 
        cout << "Found " << searchKey << endl; 
    else 
        cout << "Can't find " << searchKey << endl; 
 
    arr.display();                   //display items 
 
    cout << "Deleting 0, 55, and 99" << endl; 
    arr.remove(00);                  //delete 3 items 
    arr.remove(55); 
    arr.remove(99); 
 
    arr.display();                   //display items again 
    return 0; 
}   
/* 
Korzyść z stosowania uporządkowanych tablic 
Główną korzyścią jest szybsze wyszukiwanie. Jednakże tracimy na szybkości wstawiania 
nowych danych do tablicy (dane o większych wartościach muszą być przesunięte w górę   
tablicy w celu zrobienia miejsca na nową wartość). 
*/