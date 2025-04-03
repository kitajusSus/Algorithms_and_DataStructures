// zadanie2 lista jednostronnie wiązana , 
// zadanie2_lists.cpp

#include <iostream>

using namespace std;

class Link{
    public:
        double dData;
        Link* pNext;

        Link( double dd):  dData(dd), pNext(NULL){
        }
        
        void displayLink(){
            cout<<", "<<dData<< "}";
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
        void insertFirst(double dd){ 
            // Metoda ta została zrobiona tak by pozwalała na przesłanie do niej argumentow (Przez Wartość)
            // typu `int` i `double`. (Ponieważ takie zmienne ustawiliśmy w `private`  w `Link`)
            // Następnie zmienia się obiekt `link` w powyżej opisany sposób. 
            Link* pNewLink = new Link(dd); 
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


class LinkStack{
    private:
        LinkList* pList;

    public:
        LinkStack(){
            pList = new LinkList;
        }
        ~LinkStack(){
            delete pList;
        }
        void push(double j){
            pList -> insertFirst(j);
        }
        double pop(){
            pList -> deleteFirst();
        }
        bool isEmpty(){
            return (pList -> isEmpty());
        }
        void displayStack(){
            cout<< "Stack (top --> botton); ";
            pList->displayList();
        }
};


int main(){
    LinkStack theStack;

    theStack.insertFirst(22, 2.2);
    theStack.insertFirst(44, 3.44);

    theStack.displayStack();

    int findKey = 44;
    Link* pFind = theStack.find(findKey);
    if(pFind!=NULL)
        cout<< "znalezione link z kluczem"<< pFind -> iData<<endl;
    else 
        cout << "nie moge znalezc link"<< endl;

    int remKey = 66; 
    bool remOK = theStack.remove(remKey);
    if(remOK)
        cout<<"Removed link with key" << remKey<< endl;
    else
        cout<<"nie moge usunac link !!!! "<< endl;

    theStack.displayStack();
    return 0;
}