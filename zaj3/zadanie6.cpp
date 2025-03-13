/*
Przykład 6 (C++) Przechowywanie obiektów. Implementacja klasy Person. Przykład klasy 
mogącej posłużyć do przechowywania danych personelu.  
*/
 
 
#include <iostream> 
#include <string> 
#include <vector> 
using namespace std; 
//////////////////////////////////////////////////////////////// 
class Person 
{ 
    private: 
        string lastName; 
        string firstName; 
        int age; 
    public: 
//-------------------------------------------------------------- 
    Person(string last, string first, int a) :   //constructor 
    lastName(last), firstName(first), age(a) 
    {  } 
//-------------------------------------------------------------- 
    void displayPerson() 
    { 
        cout << "   Last name: " << lastName; 
        cout << ", First name: " << firstName; 
        cout << ", Age: " << age << endl; 
    } 
//-------------------------------------------------------------- 
    string getLast()                    //get last name 
    { return lastName; } 
};  //end class Person 
//////////////////////////////////////////////////////////////// 
class ClassDataArray 
{ 
    private: 
        vector<Person*> v;               //vector of pointers 
        int nElems;                      //number of data items 
    public: 
//-------------------------------------------------------------- 
    ClassDataArray(int max) : nElems(0) //constructor 
    { v.resize(max); }                  //create the array 
//-------------------------------------------------------------- 
    ~ClassDataArray()                   //destructor 
    { 
        for(int j=0; j<nElems; j++)     //delete each element 
            delete v[j]; 
    } 
//-------------------------------------------------------------- 
    Person* find(string searchName) 
    {                                   //find specified value 
        int j; 
        for(j=0; j<nElems; j++)         //for each element, 
            if( v[j]->getLast() == searchName )  //found item? 
                break;                  //exit loop before end 
        if(j == nElems)                 //gone to end? 
            return NULL;                //yes, can’t find it 
        else 
            return v[j];                //no, found it 
    };  //end find() 
//-------------------------------------------------------------- 
    //put person into array 
    void insert(string last, string first, int age) 
    { 
        v[nElems] = new Person(last, first, age); 
        nElems++;                       //increment size 
    } 
//----------------------------------------------------------- 
    bool remove(string searchName){     //delete person from array 
        int j; 
        for(j=0; j<nElems; j++)         //look for it 
            if( v[j]->getLast() == searchName ) 
                break; 
        if(j==nElems)                   //can’t find it 
            return false; 
        else                            //found it 
        { 
            delete v[j];                //delete Person object 
            for(int k=j; k<nElems; k++) //shift down 
                v[k] = v[k+1]; 
            nElems--;                   //decrement size 
            return true; 
        } 
    }  //end remove() 
//----------------------------------------------------------- 
    void displayA()                     //displays array contents 
    { 
        for(int j=0; j<nElems; j++)     //for each element, 
            v[j]->displayPerson();      //display it 
    } 
//----------------------------------------------------------- 
};  //end class ClassDataArray 
//////////////////////////////////////////////////////////////// 
int main() 
{ 
    int maxSize = 100;                  //array size 
    ClassDataArray arr(maxSize);        //array 
 
    arr.insert("Evans", "Patty", 24);   //insert 10 items 
    arr.insert("Smith", "Lorraine", 37); 
    arr.insert("Yee", "Tom", 43); 
    arr.insert("Adams", "Henry", 63); 
    arr.insert("Hashimoto", "Sato", 21); 
    arr.insert("Stimson", "Henry", 29); 
    arr.insert("Velasquez", "Jose", 72); 
    arr.insert("Lamarque", "Henry", 54); 
    arr.insert("Vang", "Minh", 22); 
    arr.insert("Creswell", "Lucinda", 18); 
 
    arr.displayA();                     //display items 
 
    string searchKey = "Stimson";       //search for item 
    cout << "Searching for Stimson" << endl; 
    Person* found; 
    found=arr.find(searchKey); 
 
    if(found != NULL) 
    { 
        cout << "   Found "; 
        found->displayPerson(); 
    } 
    else 
        cout << "   Can't find " << searchKey << endl; 
    cout << "Deleting Smith, Yee, and Creswell" << endl; 
    arr.remove("Smith");                //delete.  
    arr.remove("Yee"); 
    arr.remove("Creswell"); 
 
    arr.displayA();                     //display items again 
    return 0; 
}  //end main() 