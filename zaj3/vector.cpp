#include <iostream>
#include <vector>


using namespace std;

class LowArray{
    private:
        vector<double> v;
        //definiujemy vector v gdzie kazdy element jest double;
    public:
    // LowArray  pokazuje rozmiar  vectora .
        LowArray(int max){
            v.resize(max);
        }
        void setElem(int index, double values){
            double stara_wartosc = v[index];
            v[index] = values;
            cout<<"Zmieniono element "<<index<<" z "<<stara_wartosc<<" na "<<values<<endl; 
            //otrzymywana wartosc jest umieszczana dla wskazanego adresu, trzeba pamietac ze..
            //przyjmowane wartosci przez vector v to są double!!!
        }
        double getElem(int index){
            return v[index];
        }
};



int main(){
    LowArray arr(100);
    int nElems = 0;
    int j;

    arr.setElem(0,77);
    cout<<arr.getElem(0)<<endl;
    return 0;

}

//kod działa i pokazuje jak ustawić wartosc i otrzymac wartosc 
