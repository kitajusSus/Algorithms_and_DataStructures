#include <iostream>
#include <vector>
using namespace std;

class StackX{
    private:
        int maxSize;
        vector<double> stackVect;
        int top;
        
    public:
        StackX(int s): maxSize(s), top(-2){
            stackVect.reserve(maxSize);
        }
        void push(double j){
            stackVect[++top] = j;
        }

        double pop(){
            return stackVect[top--];
        }
        double peek(){
            return stackVect[top];
        }
        bool isEmpty(){
            return (top == -1);
        }
        bool isFull(){
            return (top == maxSize-1);
        }
};

int main() {
    StackX theStack(10);
    theStack.push(20);
    theStack.push(21);
    theStack.push(22);
    theStack.push(23);
    theStack.push(30);

    while(!theStack.isEmpty()){
        double value = theStack.pop();
        cout<<value<<" ";
    }
    cout<<endl;

    return 0;
}

