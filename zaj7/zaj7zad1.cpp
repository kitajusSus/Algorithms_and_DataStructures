#include <iostream>
#include <string>

using namespace std;

void znajdzAnagramy(string slowo, int poczatek, int koniec);

int main() {
  string slowo = "skibidi";
  znajdzAnagramy(slowo, 0, slowo.length() - 1);
  return 0;
}

void znajdzAnagramy(string slowo, int poczatek, int koniec) {
  if (poczatek == koniec) {
    cout << slowo << endl;
    return;
  }

  for (int i = poczatek; i <= koniec; i++) {
    swap(slowo[poczatek], slowo[i]);
    znajdzAnagramy(slowo, poczatek + 1, koniec);
    swap(slowo[poczatek], slowo[i]);
  }
}
