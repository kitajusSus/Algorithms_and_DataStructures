#include <iostream>
// NIE DZIAŁA NIE SPRAWDZAC NAWET PROSZE
class Pies {
private:
  int wiek;
  int waga;
  bool szczepienie;
  string imie;

public:
}


int main(){
  int arr[100];
  int n = 0;
  arr[2] = 22;
  int *ptr = &arr[2];
  std::cout << *ptr;
  // ptr wyswietlanie adresu
  // *ptr wyswietlanie wartosci pod adresem
  // arr[2]  wyswetlanie poprosti czytsej wartosci
  return 0;
}
