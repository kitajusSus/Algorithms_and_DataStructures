// zadanie2 lista jednostronnie wiązana , 
// zadanie2_lists.cpp

#include <iostream>

using namespace std;

class Link{
    public:
        int  iData;
        double dData;
        Link* pNext;

        Link(int id, double dd): iData(id), dData(dd), pNext(NULL){
        }
        
        void displayLink(){
            cout<< "{"<< iData<< ", "<<dData<< "}";
        }
};

class LinkList{
    private:
        Link* pFirst; //prt to first link on list
    public:
        LinkList() : pFirst(NULL){

        }
        ~LinkList(){
            Link* pCurrent = pFirst;
            while(pCurrent != NULL){
                Link* pOldCur = pCurrent;
                pCurrent = pCurrent -> pNext;
                delete pOldCur;
            }
        }
        void insertFirst(int id, double dd){ 
            // Metoda ta została zrobiona tak by pozwalała na przesłanie do niej argumentow (Przez Wartość)
            // typu `int` i `double`. (Ponieważ takie zmienne ustawiliśmy w `private`  w `Link`)
            // Następnie zmienia się obiekt `link` w powyżej opisany sposób. 
            Link* pNewLink = new Link(id,dd); 
            pNewLink -> pNext = pFirst; //newLink --> poprzedni pierwszy
            pFirst = pNewLink; // pierwszy --> newLink
          }
          //usuwa pierwszy link
        bool remove(int key){
            Link* pCurrent = pFirst;
            Link* pPrevious = pFirst;
            while(pCurrent-> iData !=key){
                if(pCurrent ->pNext == NULL)
                    return false;
                else {
                    pPrevious = pCurrent;
                    pCurrent = pCurrent -> pNext;
                }
            }
            if(pCurrent == pFirst)
                pFirst = pFirst -> pNext;
            else
                pPrevious ->pNext = pCurrent -> pNext;
            delete pCurrent;
            return true;
        }
         
        void displayList(){
            cout<<"Lista (pierwsza -> ostatnia): ";
            Link* pCurrent = pFirst;
            while(pCurrent != NULL){
              pCurrent -> displayLink();
              pCurrent = pCurrent -> pNext;
            }
            cout<<endl;
        }

        Link* find(int key){
            Link* pCurrent = pFirst;
            while(pCurrent -> iData != key){
                if(pCurrent->pNext == NULL)
                    return NULL;
                else
                    pCurrent = pCurrent -> pNext;
            }
            return pCurrent;
        }
};



int main(){
    LinkList theList;

    theList.insertFirst(22, 2.2);
    theList.insertFirst(44, 3.44);

    theList.displayList();

    int findKey = 44;
    Link* pFind = theList.find(findKey);
    if(pFind!=NULL)
        cout<< "znalezione link z kluczem"<< pFind -> iData<<endl;
    else 
        cout << "nie moge znalezc link"<< endl;

    int remKey = 66; 
    bool remOK = theList.remove(remKey);
    if(remOK)
        cout<<"Removed link with key" << remKey<< endl;
    else
        cout<<"nie moge usunac link !!!! "<< endl;

    theList.displayList();
    return 0;
}