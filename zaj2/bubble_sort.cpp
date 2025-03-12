#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace  std; 


// Bubble Sort / sortowanie bąbelkowe - generalnie podstawa, najłatwiej to zrobić dwiema pętlami, bierzemy sobie tablice danych tzw array[], i robimy kolejno takie cos:
// 1. sprawdzamy po kolei każdy element w tablicy 0,1,2,3, itd aż do konca czyli n-1 (cpp liczy od zera czyli pierwszy element ma index = 0 )
// jeśli element  array[i] > (jest większy) od elementu array[i+1] to zamieniamy je miejscami, 
// swap(array[i], array[i+1]) - funkcja swap która zamienia miejcami elementy w tablicy.\

//2.  powtarzamy aż array[i] < array[i+1]
//3. Logiczne myslenie podpowiada mi że ostatni element po pierwszej iteracji bedzie = max(array[]), czyli największy element z tablicy bedzie na miejscu ostatnim. 
//4. to sprawia że w każdej kolejnej iteracji bedziemy musieli sprawdziać o 1 element mniej
//5. złożoność obliczeniowa O(n^2) - czyli dla 100 elementów musimy wykonać 100*100 = 10000 operacji// taka ciekawostka
//kod w cpp na buble sort:
/*
void bubble_sort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
tak z definicji
*/
int skibidi[] = {99,2,3,6,7,1,2,3,-1,1};
int skibidi2[] = {99,2,3,6,7,1,2,3,-1,1};

//argumentami naszej funkcji do sortowania bąbelkowego będą tablica, i jej rozmiar
void bombelkoweSortowanie(int arr[], int n ){
  bool swapped; //to nie jest obowiazkowe ale stanowi to element optymalizacji, 
  //dzięki temu bedziemy wiedzieli czy algorytm dokona zmiany jakiejkolwiek 
  //czyli czy wykona sie jakakolwiek zamiana miejsc w tablicy (swap)

  for (int i =0; i< n -1; i++){
    swapped = false; // ustawiam sobie wartosc na falce bo na poczatku nie dokonano zmian
    // nie wykorzystujemy rekurencji wiec wszystko dzieje się w dwóch pętlach tak długo  aż się nie skonczy.  
  
    // Przechodzimy przez tablicę, ale tylko do n-i-1 (bo koniec jest już posortowany)
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) { 
        // Jeśli element jest większy niż następny, zamieniamy je miejscami
        swap(arr[j], arr[j + 1]); 
        // procedura zamiany miejsc tak jak opisane w linijce 5 czy cos takiego.
        swapped = true; 
        // Ustawiamy flagę na true, bo dokonaliśmy zamiany
      }
    }
    if (swapped == false) break; // jeśli nie dokona sie zmiana, tzw petla idzie dalej. 
  }
}


// Funkcja pomocnicza do wypisywania tablicy
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void kod_z_zajec(int a[], int r){
   
 
 
    for(int i=0;i<r;i++) 
    { 
        cout<<endl; 
        cout<<"i="<<i<<":"; 
        for(int j=0;j<r-i-1;j++) 
        { 
            if(a[j]>a[j+1]) 
            { 
                int temp=a[j+1]; 
                a[j+1]=a[j]; 
                a[j]=temp; 
            } 
 
            // The intermediate stages of sorting: 
            cout<<endl; 
            for(int j=0;j<r;j++) 
                cout<<a[j]<<" "; 
        } 
    } 
 
    //cout<<"\n An array after sorting:"<<endl; 
    //for(int i=0;i<r;i++) 
    //    cout<<a[i]<<" "; 
 
    //delete [] a; 
    //system("pause"); 
    //return 0; 
} 

// Funkcja do losowania tablicy
void Random(int* array, int size, int minValue, int maxValue) {
  for (int i = 0; i < size; ++i) {
      array[i] = minValue + rand() % (maxValue - minValue + 1);
  }
}


// SPRAWDZAMY CZY DZIAŁA
int main() {
  // Inicjalizacja generatora liczb losowych
  srand(static_cast<unsigned int>(time(nullptr)));
  // Parametry tablicy
  const int rozmiar = 10;
  const int min = 1;
  const int max = 100;

  //losowa tablica
  int* losowa_tablica1 = new int[rozmiar];
  Random(losowa_tablica1, rozmiar, min,max);

   
  cout<<"Tablica przed sortowaniem(adres): ";
  cout<<losowa_tablica1<<endl;
  int n = sizeof(losowa_tablica1) / sizeof(losowa_tablica1[0]); // Obliczamy liczbę elementów w tablicy
  cout << "Tablica przed sortowaniem: ";
  //printArray(skibidi, n); // Wypisujemy tablicę przed sortowaniem


  //liczenie czasu dla SWAP FUNKCJA NR.1
  clock_t start = clock();
  bombelkoweSortowanie(losowa_tablica1, n); // Sortowanie tablicy
  clock_t end = clock();
  long double duration_1 =  double(end - start) / CLOCKS_PER_SEC;
  
  // drugie podejscie
  clock_t start1 = clock();
  kod_z_zajec(losowa_tablica1,n);
  clock_t end1 =clock();
  long double duration_2 = (end1 - start1) / CLOCKS_PER_SEC;


  cout<<"Czas sortowania z funckcja swap: "<<duration_1<<endl;
  cout<<"Czas sortowania dla kod_z_zajec: "<<duration_2<<endl;

  cout << "Tablica po sortowaniu: ";
  //printArray(skibidi, n);
  cout<<"Tablica po sortowaniu(adres): ";
  //cout<<skibidi<<endl;


  return 0;
}
