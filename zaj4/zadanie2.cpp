#include <iostream>
#include <cstdlib>


using namespace std;
void polish_flag(int a[10],  int s=10);
int index = 1;
const int asize =11;


int main(){
    int a[asize] = {0,1,1,0,0,0,1,1,1,0};
    cout<< "tablica 1 :"<<endl;
    for(int i = 0; i<asize;i++){
        cout<<a[i]<<", ";
    }
    cout<<endl;
    polish_flag(a,asize);

    cout<<"Po posortowaniu tablicy przez polish_flag algorytm: ";
    for(int i = 0; i<asize;i++){
        cout<<a[i]<<", ";
    }
    cout<<endl;
}


void polish_flag(int a[10], int s) {
    // Implementacja algorytmu Polish flag
    int x = 0;
    int y = s - 1; //s to jest ilosc elementów y idzie od tyłu hehe
    
    while (x < y) {
        while (x < y && a[x] == 0) {
            x++;
        }
        while (x < y && a[y] == 1) {
            y--;
        }
        if (x < y) {
            int n = a[x];
            a[x] = a[y];
            a[y] = n;
        }
    }
}