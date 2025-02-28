#include <iostream>
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
      if (arr[j] > arr[j + 1]) { // Jeśli element jest większy niż następny, zamieniamy je miejscami
        swap(arr[j], arr[j + 1]); // procedura zamiany miejsc tak jak opisane w linijce 5 czy cos takiego.
        swapped = true; // Ustawiamy flagę na true, bo dokonaliśmy zamiany
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

// SPRAWDZAMY CZY DZIAŁA
int main() {
   
  cout<<"Tablica przed sortowaniem(adres): ";
  cout<<skibidi<<endl;
  int n = sizeof(skibidi) / sizeof(skibidi[0]); // Obliczamy liczbę elementów w tablicy
  cout << "Tablica przed sortowaniem: ";
  printArray(skibidi, n); // Wypisujemy tablicę przed sortowaniem

    bombelkoweSortowanie(skibidi, n); // Sortowanie tablicy

    cout << "Tablica po sortowaniu: ";
    printArray(skibidi, n);
    cout<<"Tablica po sortowaniu(adres): ";
    cout<<skibidi<<endl;
    return 0;
}
