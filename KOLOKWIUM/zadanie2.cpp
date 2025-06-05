// zadanie 2 kolokwium aisd
// Krzysztof Bezubik nr. albumu: 89219
//

#include <iostream>
#include <stack>

using namespace std;

class Node {
public:
    int iData;
    double dData;
    Node *pLeftChild;
    Node *pRightChild;
    Node *pFather; // nowy wskaznik 
    //konstruktor
    Node() : iData(0), dData(0.0), pLeftChild(NULL), pRightChild(NULL), pFather(NULL) {
    }
    // destoyer - niszczyciel  ktore elementy zostały usuniete
    ~Node() {
         cout << "X - " << iData << " "; 
    }

    void displayNode() {
         cout << "{" << iData << "," << dData << "}"; 
    }
};

class Tree {
private:
    Node *pRoot; // korzen drzewa

public:
    Tree() : pRoot(NULL) {}

    Node *find(int key) { // zakladamy niepuste drzewo
        Node *pCurrent = pRoot;
        while (pCurrent && pCurrent->iData != key) {
            if (key < pCurrent->iData)
                pCurrent = pCurrent->pLeftChild;
            else
                pCurrent = pCurrent->pRightChild;
        }
        return pCurrent;
    }

    void insert(int id, double dd) {
        Node *pNewNode = new Node;
        pNewNode->iData = id;
        pNewNode->dData = dd;
        if (pRoot == NULL) {
            pRoot = pNewNode;
        } else {
            Node *pCurrent = pRoot;
            Node *pParent = NULL;
            while (pCurrent != NULL) {
                pParent = pCurrent;
                if (id < pCurrent->iData)
                    pCurrent = pCurrent->pLeftChild;
                else
                    pCurrent = pCurrent->pRightChild;
            }
            // pParent wskazuje na ojca, pCurrent jest NULL
            if (id < pParent->iData) {
                pParent->pLeftChild = pNewNode;
            } else {
                pParent->pRightChild = pNewNode;
            }
            pNewNode->pFather = pParent; // ustawiamy ojca
        }
    }

    // NOWA FUNKCJA zwracająca wskaźnik na węzeł z największą wartością
    Node *getMaxNode() {
        // jesli nie bedzie korzenia to zwraca null
        if (!pRoot) return NULL;
        Node *pCurrent = pRoot;
        // tak długo jak jest to mozliwe to pCurrent ma przechodzic po prawej stronie drzewa
        // "tak dlugo jesli True"
        while (pCurrent->pRightChild)
        //pCurrent jest aktualizowany na wskaznik na "obecnie najwieksze dziecko" czyli te po prawej
            pCurrent = pCurrent->pRightChild;
        return pCurrent;
    }

    // NOWA FUNKCJA wyświetlająca wartości węzłów podczas przechodzenia w górę drzewa
    // zaczynając od największego liścia, kończąc na korzeniu - jak w zadaniu
    void displayPathUpFromMax() {
        cout<<endl;
        cout <<"-------------------------------------"<< endl;
        //pCurrent przechodzi po prawej stronie
        Node *pMax = getMaxNode();

        //jesli nie ma pMax to znaczy ze nie ma zadnych elementow bo, 
        // nawet gdyby był jeden element to on byłby tym maksymalnym i najwikeszym 
        if (!pMax) {
            cout << "Drzewo jest puste." << endl;
            return;
        }
        cout << "Sciezka w gore od najwiekszego liscia do korzenia: ";
        
        Node *pCurrent = pMax;
        while (pCurrent != NULL) {
            cout << pCurrent->iData << " ";
            pCurrent = pCurrent->pFather;
        }
        //dla estetyki w terminalu
        cout<<endl;
        cout <<"-------------------------------------"<< endl;
    }
//nic nie zmienione
    void traverse(int traverseType) {
        switch (traverseType) {
        case 1:
            cout << "\nPreorder traversal: ";
            preOrder(pRoot);
            break;
        case 2:
            cout << "\nInorder traversal:  ";
            inOrder(pRoot);
            break;
        case 3:
            cout << "\nPostorder traversal: ";
            postOrder(pRoot);
            break;
        }
        cout << endl;
    }

    void preOrder(Node *pLocalRoot) {
        if (pLocalRoot != NULL) {
            cout << pLocalRoot->iData << " ";
            preOrder(pLocalRoot->pLeftChild);
            preOrder(pLocalRoot->pRightChild);
        }
    }

    void inOrder(Node *pLocalRoot) {
        if (pLocalRoot != NULL) {
            inOrder(pLocalRoot->pLeftChild);
            cout << pLocalRoot->iData << " ";
            inOrder(pLocalRoot->pRightChild);
        }
    }

    void postOrder(Node *pLocalRoot) {
        if (pLocalRoot != NULL) {
            postOrder(pLocalRoot->pLeftChild);
            postOrder(pLocalRoot->pRightChild);
            cout << pLocalRoot->iData << " ";
        }
    }

    void displayTree() {
        stack<Node *> globalStack;
        globalStack.push(pRoot);
        int nBlanks = 32;
        bool isRowEmpty = false;
        cout << "......................................................";
        cout << endl;
        while (isRowEmpty == false) {
            stack<Node *> localStack;
            isRowEmpty = true;
            for (int j = 0; j < nBlanks; j++)
                cout << ' ';
            while (globalStack.empty() == false) {
                Node *temp = globalStack.top();
                globalStack.pop();
                if (temp != NULL) {
                    cout << temp->iData;
                    localStack.push(temp->pLeftChild);
                    localStack.push(temp->pRightChild);
                    if (temp->pLeftChild != NULL || temp->pRightChild != NULL)
                        isRowEmpty = false;
                } else {
                    cout << "--";
                    localStack.push(NULL);
                    localStack.push(NULL);
                }
                for (int j = 0; j < nBlanks * 2 - 2; j++)
                    cout << ' ';
            }
            cout << endl;
            nBlanks /= 2;

            while (localStack.empty() == false) {
                globalStack.push(localStack.top());
                localStack.pop();
            }
        }
        cout << "........................................." << endl;
        cout << endl;
    }

    void destroy() {
        destroyRec(pRoot);
    }

    void destroyRec(Node *pLocalRoot) {
        if (pLocalRoot != NULL) {
            destroyRec(pLocalRoot->pLeftChild);
            destroyRec(pLocalRoot->pRightChild);
            delete pLocalRoot;
        }
    }
};

int main() {
    int value;
    char choice = ' ';
    Node *found;
    Tree theTree;
    theTree.insert(50, 5.0);
    theTree.insert(25, 2.5);
    theTree.insert(75, 7.5);
    theTree.insert(12, 1.2);
    theTree.insert(37, 3.7);
    theTree.insert(43, 4.3);
    theTree.insert(30, 3.0);
    theTree.insert(33, 3.3);
    theTree.insert(87, 8.7);
    theTree.insert(93, 9.3);
    theTree.insert(97, 9.7);

    while (choice != 'q') {
        cout << "Enter first letter of (s)how, (i)nsert, (f)ind, (t)raverse, (m)ax, (p)ath or (q)uit: ";
        cin >> choice;
        switch (choice) {
        case 's':
            theTree.displayTree();
            break;
        case 'i':
            cout << "Enter value to insert: ";
            cin >> value;
            theTree.insert(value, value + 0.9);
            break;
        case 'f':
            cout << "Enter value to find: ";
            cin >> value;
            found = theTree.find(value);
            if (found != NULL) {
                cout << "Found: ";
                found->displayNode();
                cout << endl;
            } else
                cout << "Could not find " << value << endl;
            break;
        case 't':
            cout << "Enter traverse type (1=preorder, 2=inorder, 3=postorder): ";
            cin >> value;
            theTree.traverse(value);
            break;
        case 'm': // max
            {
                Node *maxNode = theTree.getMaxNode();
                if (maxNode) {
                    cout << "Max node: ";
                    maxNode->displayNode();
                    cout << endl;
                }
                else {
                    cout << "Tree is empty." << endl;
                }
            }
            break;
        case 'p': // path up from max
            theTree.displayPathUpFromMax();
            break;
        case 'q':
            theTree.destroy();
            cout << endl;
            break;
        default:
            cout << "Invalid entry\n";
        }
    }
    return 0;
}