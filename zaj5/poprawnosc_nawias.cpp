// PRIORITY QUEUES  struktura danyc hkolejka priorytetowa
#include <iostream> 
#include <vector> 
using namespace std; 
class PriorityQ{ 
//vector in sorted order, from max at 0 to min at size-1 
    private: 
        int maxSize; 
        vector<double> queVect; 
        int nItems; 
    public: 
        PriorityQ(int s) : maxSize(s), nItems(0){    //constructor
         queVect.resize(maxSize); 
        } 
 
        void insert(double item){
            //insert item 
         
            int j; 
            if(nItems==0)                           //if no items, 
                queVect[nItems++] = item;           //insert at 0 
            else                                    //if items, 
            { 
                for(j=nItems-1; j>=0; j--)          //start at end, 
                { 
                    if( item > queVect[j] )         //if new item larger, 
                        queVect[j+1] = queVect[j];  //shift upward 
                    else                            //if smaller, 
                        break;                      //done shifting 
                }  //end for 
                queVect[j+1] = item;                //insert it 
                nItems++; 
            }  //end else (nItems > 0) 
        }  //end insert() 
 
        double remove()   {
             return queVect[--nItems]; 
        } 
 
        double peekMin() {                           //peek at minimum item 
         return queVect[nItems-1];
        } 
 
        bool isEmpty() {                            //true if queue is empty 
         return (nItems==0); 
        } 
 
        bool isFull(){                               //true if queue is full 
         return (nItems == maxSize); 
        } 
 
};  //end class PriorityQ 
//------------------------------------------------------------- 
int main() { 
    PriorityQ thePQ(5);                 //priority queue, size 5 
 
    thePQ.insert(30);                   //unsorted insertions 
    thePQ.insert(50); 
    thePQ.insert(10); 
    thePQ.insert(40); 
    thePQ.insert(20); 
 
    while( !thePQ.isEmpty() ) {
        //sorted removals 
        double item = thePQ.remove(); 
        cout << item << " ";            //10, 20, 30, 40, 50 
    }  //end while 
    cout << endl; 
    return 0; 
}  //end main()