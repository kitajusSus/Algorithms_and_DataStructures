#include <iostream>
#include <stack>
using namespace std;

class Node{
public:
    char iData; //data item (key)
    Node* pLeftChild; //this node's left child
    Node* pRightChild; //this node's right child
    int red; //1 - red, 0 - black node

    //constructor
    Node(char x) : iData(x), pLeftChild(NULL), pRightChild(NULL), red(1)
    { }

    ~Node() //destructor
    { cout << "X-" << iData << " "; }
    void displayNode() //display ourself: 75,
    {
        cout << iData << ", ";
    }
};


class RBTree{
private:
    typedef Node* link;
    link pRoot; //first node of tree

    int red(link x)
    {
        if (x == NULL)
        return 0;
        return x->red;
    }

    void rotR(link& pN)
    { //Node*& pN
        Node* pCurrent = pN -> pLeftChild;
        pN -> pLeftChild = pCurrent -> pRightChild;
        pCurrent -> pRightChild = pN;
        pN = pCurrent;
    }

    void rotL(link& pN)
    {
        Node* pCurrent = pN -> pRightChild;
        pN -> pRightChild = pCurrent -> pLeftChild;
        pCurrent -> pLeftChild = pN;
        pN = pCurrent;
    }

    void RBinsert(link& pN, char id, int sw)
    {
        if ( pN == NULL){
            pN = new Node(id);
            return;
        }
        if( red(pN->pLeftChild)&&red(pN->pRightChild))
        {
            pN->red = 1; pN->pLeftChild->red = 0; pN->pRightChild->red = 0;
        }
        if (id < pN->iData)
        {
            RBinsert(pN->pLeftChild,id, 0);
            if(red(pN) && red (pN->pLeftChild) && sw) rotR(pN);
            if (red(pN->pLeftChild) && red(pN->pLeftChild->pLeftChild))
            {
                rotR(pN); pN->red =0; pN->pRightChild->red =1;
            }
        }
        else
        {
            RBinsert(pN->pRightChild,id, 1);
            if(red(pN) && red (pN->pRightChild) && !sw)
                rotL(pN);
            if (red(pN->pRightChild) && red(pN->pRightChild->pRightChild))
            {
                rotL(pN); pN->red =0; pN->pLeftChild->red =1;
            }
        }
    } //end RBinsert()

public:
    RBTree() : pRoot(NULL) //constructor
    { }

    Node* find(char key) //find node with given key
    { //(assumes non-empty tree)
        Node* pCurrent = pRoot; //start at root
        while(pCurrent->iData != key) //while no match,
        {
            if(key < pCurrent->iData) //go left?
            pCurrent = pCurrent->pLeftChild;
            else //or go right?
            pCurrent = pCurrent->pRightChild;
            if(pCurrent == NULL) //if no child,
            return NULL; //didn't find it
        }
        return pCurrent; //found it
    } //end find()

    void insert(char id)
    {
        RBinsert(pRoot, id, 0);
        pRoot->red = 0;
    }

    void traverse(int traverseType)
    {
        switch(traverseType)
        {
            case 1: cout << "\nPreorder traversal: ";
            preOrder(pRoot);
            break;
            case 2: cout << "\nInorder traversal: ";
            inOrder(pRoot);
            break;
            case 3: cout << "\nPostorder traversal: ";
            postOrder(pRoot);
            break;
        }
        cout << endl;
    }

    void preOrder(Node* pLocalRoot)
    {
        if(pLocalRoot != NULL)
        {
            cout << pLocalRoot->iData << " "; //display node
            preOrder(pLocalRoot->pLeftChild); //left child
            preOrder(pLocalRoot->pRightChild); //right child
        }
    }

    void inOrder(Node* pLocalRoot)
    {
        if(pLocalRoot != NULL)
        {
            inOrder(pLocalRoot->pLeftChild); //left child
            cout << pLocalRoot->iData << " "; //display node
            inOrder(pLocalRoot->pRightChild); //right child
        }
    }

    void postOrder(Node* pLocalRoot)
    {
        if(pLocalRoot != NULL)
        {
            postOrder(pLocalRoot->pLeftChild); //left child
            postOrder(pLocalRoot->pRightChild); //right child
            cout << pLocalRoot->iData << " "; //display node
        }
    }

    void displayTree()
    {
        stack<Node*> globalStack;
        globalStack.push(pRoot);
        int nBlanks = 32;
        bool isRowEmpty = false;
        cout <"......................................................";
        cout << endl;
        while(isRowEmpty==false)
        {
            stack<Node*> localStack;
            isRowEmpty = true;
            for(int j=0; j<nBlanks; j++)
            cout << ' ';
            while(globalStack.empty()==false)
            {
                Node* temp = globalStack.top();
                globalStack.pop();
                if(temp != NULL)
                {
                    cout << temp->iData;
                    localStack.push(temp->pLeftChild);
                    localStack.push(temp->pRightChild);
                    if(temp->pLeftChild != NULL ||
                    temp->pRightChild != NULL)
                    isRowEmpty = false;
                }
                else
                {
                    cout << "--";
                    localStack.push(NULL);
                    localStack.push(NULL);
                }
                for(int j=0; j<nBlanks*2-2; j++)
                cout << ' ';
            } //end while globalStack not empty
            cout << endl;
            nBlanks /= 2;
            while(localStack.empty()==false)
            {
                globalStack.push( localStack.top() );
                localStack.pop();
            }
        } //end while isRowEmpty is false
        cout <"......................................................";
        cout << endl;
    } //end displayTree()

    void destroy() //deletes all nodes
    { destroyRec(pRoot); } //start at root

    void destroyRec(Node* pLocalRoot) //delete nodes in
    { // this subtree
        if(pLocalRoot != NULL)
        { //uses postOrder
            destroyRec(pLocalRoot->pLeftChild); //left subtree
            destroyRec(pLocalRoot->pRightChild); //right subtree
            delete pLocalRoot; //delete this node
        }
    }
};


int main()
{
    int value;
    char value2;
    char choice;
    Node* found;
    RBTree theTree; //create tree
    while(choice != 'q') //interact with user
    { //until user types 'q'
        cout << "Enter first letter of ";
        cout << "show, insert, find, traverse, automatic or quit: ";
        cin >> choice;
        switch(choice)
        {
            case 's': //show the tree
                theTree.displayTree();
                break;
            case 'a':
                cout<<"Automatic insertion of characters:
                ASERCHINGX"<<endl;
                theTree.insert('A'); //insert nodes
                theTree.insert('S');
                theTree.insert('E');
                theTree.insert('R');
                theTree.insert('C');
                theTree.insert('H');
                theTree.insert('I');
                theTree.insert('N');
                theTree.insert('G');
                theTree.insert('X');
                break;
            case 'i': //insert a node
                cout << "Enter value to insert: ";
                cin >> value2;
                theTree.insert(value2);
                break;
            case 'f': //find a node
                cout << "Enter value to find: ";
                cin >> value2;
                found = theTree.find(value2);
                if(found != NULL)
                {
                    cout << "Found: ";
                    found->displayNode();
                    cout << endl;
                }
                else
                    cout << "Could not find " << value2 << endl;
                break;
            case 't': //traverse the tree
                cout<<"Enter traverse type (1=preorder, "<<"2=inorder, 3=postorder): ";
                cin>>value;
                theTree.traverse(value);
                break;
            case 'q': //quit the program
                theTree.destroy();
                cout << endl;
                break;
            default:
                cout << "Invalid entry\n";
        }
    }
    return 0;
}
