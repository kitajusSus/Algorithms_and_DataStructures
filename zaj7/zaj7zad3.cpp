// zadanie 3 program realizujacy wyszukiwanie binarne

#include <iostream>
#include <cstdlib>

using namespace std;

int t[12] = {-1,1,4,5,6,7,8,9,9,9,9,9};

void pb(int *m, int szuk, int left,int right );


int main(){
    int s=0;
    for(int i=1;i<12;i++){
        s=t[i];
        cout<<"Znajdowanie elemtnut s="<<s<<"w tablicy t[]: \n";
        pb(t,s,0,11);
    }
    s=3;
    cout<<"Znajdowanie elemntu s= "<<s<<" w tablicy t[]; \n";
    pb(t,s,0,11);
cout<<endl;

system("pause");
return 0;
}


void pb(int *m, int szuk, int left,int right ){
    int mid= (left+right)/2;
    cout<<mid<<" ("<<m[mid]<<"), "<<left<<" "<<right<<endl;
    if(szuk==m[mid]){
        cout<<"Element "<<szuk<<" zostal zanelziony. \n *****************\n";
        return;
    } 
    else{
        if(szuk!=m[mid]&&right==left){
            cout<<"Element ["<<szuk<<" ]nie zosta znalezion. \n";
        }
    }
    if(right>left){
        if(szuk<m[mid]){
            right=mid -1;
        }
        else{
            left = mid+1;
        }
        pb(m,szuk,left,right);
    }
}