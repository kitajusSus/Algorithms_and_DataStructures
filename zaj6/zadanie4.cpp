#include <iostream>

using namespace std;

class Link {
public:
    double dData;
    Link* pNext;

    Link(double dd) : dData(dd), pNext(NULL) {}

    void displayLink() {
        cout << "{ " << dData << " } ";
    }
};

class LinkList {
private:
    Link* pFirst; // Pointer to first link on list
public:
    LinkList() : pFirst(NULL) {}

    ~LinkList() {
        Link* pCurrent = pFirst;
        while (pCurrent != NULL) {
            Link* pOldCur = pCurrent;
            pCurrent = pCurrent->pNext;
            delete pOldCur;
        }
    }

    void insertFirst(double dd) {
        Link* pNewLink = new Link(dd);
        pNewLink->pNext = pFirst; // newLink --> previous first
        pFirst = pNewLink; // first --> newLink
    }

    // Removes the first link
    double deleteFirst() {
        if (pFirst == NULL) {
            cout << "List is empty, nothing to delete." << endl;
            return -1; // or some other sentinel value indicating failure
        }

        Link* pTemp = pFirst;
        pFirst = pFirst->pNext;
        double key = pTemp->dData;
        delete pTemp;
        return key;
    }

    void displayList() {
        cout << "List (first -> last): ";
        Link* pCurrent = pFirst;
        while (pCurrent != NULL) {
            pCurrent->displayLink();
            pCurrent = pCurrent->pNext;
        }
        cout << endl;
    }

    bool isEmpty() {
        return (pFirst == NULL);
    }

    Link* find(double key) {
        Link* pCurrent = pFirst;
        while (pCurrent != NULL) {
            if (pCurrent->dData == key) {
                return pCurrent;
            }
            pCurrent = pCurrent->pNext;
        }
        return NULL;
    }

    bool remove(double key) {
        Link* pCurrent = pFirst;
        Link* pPrevious = NULL;

        while (pCurrent != NULL) {
            if (pCurrent->dData == key) {
                if (pPrevious == NULL) {
                    pFirst = pCurrent->pNext;
                } else {
                    pPrevious->pNext = pCurrent->pNext;
                }
                delete pCurrent;
                return true;
            }
            pPrevious = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        return false;
    }
};

class LinkStack {
private:
    LinkList* pList;

public:
    LinkStack() {
        pList = new LinkList;
    }

    ~LinkStack() {
        delete pList;
    }

    void push(double j) {
        pList->insertFirst(j);
    }

    double pop() {
        return pList->deleteFirst();
    }

    bool isEmpty() {
        return pList->isEmpty();
    }

    void displayStack() {
        cout << "Stack (top -> bottom): ";
        pList->displayList();
    }

    Link* find(double key) {
        return pList->find(key);
    }

    bool remove(double key) {
        return pList->remove(key);
    }
};

int main() {
    LinkStack theStack;

    theStack.push(22.2);
    theStack.push(44.44);

    theStack.displayStack();

    double findKey = 44.44;
    Link* pFind = theStack.find(findKey);
    if (pFind != NULL)
        cout << "Found link with key " << pFind->dData << endl;
    else
        cout << "Can't find link" << endl;

    double remKey = 66.66;
    bool remOK = theStack.remove(remKey);
    if (remOK)
        cout << "Removed link with key " << remKey << endl;
    else
        cout << "Can't remove link" << endl;

    theStack.displayStack();
    return 0;
}