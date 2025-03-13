#include <iostream>
#include <vector>
using namespace std;


//klasa 
class HighArray {
    private:
        vector<double> v;
        int nElems;
    //-------------------          
    public:
    HighArray(): nElems(0){
        
    }
    HighArray(int max): nElems(0){
        v.resize(max) 
    }
    //------------SZUKANIE ELEMENTÓW W TABLICY------
    bool find(double searchKey){
        int j;
        for(j=0; j<nElems;j++)
            if(v[j]==searchKey)
                break;
        if(j==nElems)
            return false;
        else
            return true;    
    }
    //------------------
    void insert(double value){
        v[nElems] = value;
        nElems++
    }
    bool remove(double value){
        int j;
        for(j=0; j<nElems;j++)
            if(value ==v[j])
                break;

        if(j==nElems) 
            return false;
        else{
            for(int k=j; k<nElems;k++)
                v[k]=v[k+1];
            nElems--;
            return true;
        }
    }
    //-------------------------------------------------------------- 
    void display(){                      //displays array contents  
    for(int j=0; j<nElems; j++)         //for each element, 
        cout << v[j] << " ";            //display it 
    cout << endl; 
    }

};
// -----------------------------------------------
int main() { 
    int maxSize = 100;                  //array size 
    HighArray arr(maxSize);             //vector 
    arr.insert(77);                     //insert 10 items 
    arr.insert(99); 
    arr.insert(44); 
    arr.insert(55); 
    arr.insert(22); 
    arr.insert(88); 
    arr.insert(11); 
    arr.insert(0); 
    arr.insert(66); 
    arr.insert(33); 
 
    arr.display();                      //display items 
 
    int searchKey = 35;                 //search for item 
    if( arr.find(searchKey) ) 
        cout << "Found " << searchKey << endl; 
    else 
        cout << "Can't find " << searchKey << endl; 
 
    cout << "Deleting 0, 55, and 99" << endl; 
    arr.remove(0);                      //delete 3 items 
    arr.remove(55); 
    arr.remove(99); 
 
    arr.display();                      //display items again 
    return 0; 
}  //end main() 


/*
W programie zadanie3.cpp kod odpowiedzialny za wyszukanie elementu zajął osiem 
linijek. W programie zadanie4.cpp zajął już tylko jedną. Dodatkową korzyścią jest to, że 
użytkownik klasy (tzn. main()) nie musi pilnować indeksowania tablicy. Co więcej 
użytkownik klasy nie musi nic wiedzieć o strukturze przechowującej dane użytej w  
highArray. Struktura ta jest ukryta za interfejsem. W następnym przykładzie, zobaczymy 
ten sam interfejs z inną strukturą danych. 
 
Abstrakcja 
Proces oddzielania jak od co (jak operacje są wykonywane w klasie w przeciwieństwie co jest 
widziane przez użytkownika klasy) nazywa się abstrakcją.  
*/