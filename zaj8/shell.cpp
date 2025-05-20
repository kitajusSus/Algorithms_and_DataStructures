// przepisane z pdf nie mam sily


#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class ArrayShell{
    private:
        vector<double> v;
        int nElems;
    public:
        ArrayShell(int max) : nElems(0){
            v.resize(max);
        }
        void insert(double value){
            v[nElems]= value;
            nElems++;
        }
        void display(){
            for(int j=0; j<nElems; j++)
                cout<<setw(2)<<v[j]<<" ";
            cout<<endl;
        }
        void exch(double& x, double& y){
            int t=x;
            x=y;
            y=t;
        }
        void ShellSort(){
            int h = 1;
            while (h<nElems/3) h = 3*h +1;
            while(h>=1){
                for(int i=h; i<nElems;i++){
                    cout<<"h="<<h<<"";
                    display();
                    for(int j=i; j>=h&&v[j]<v[j-h];j-=h) exch(v[j], v[j-h]);
                }
                h/=3;
            }
        }
};

int main(){
    int maxSize= 100;
    ArrayShell arr(maxSize);
    arr.insert(22);
    arr.insert(3345);
    arr.insert(62);
    arr.insert(29);
    arr.insert(123);
    arr.insert(899);
    arr.insert(7);
    arr.insert(6);
    arr.insert(35);
    arr.insert(2);
    cout<<" ";
    arr.display();
    cout<<"h - sorotowanie:"<<endl;
    arr.ShellSort();
    cout<<" ";
    arr.display();
    return 0;

}