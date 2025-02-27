#include <iostream>

using namespace std;


//definiowanie silni, każdy wie czym jest silnia np: n! = n * (n-1) * (n-2) * ... * 1
long int silnia(int n){
  //warunek ukonczenia rekurencji, wyjscie z "pętli przywoływania samej siebie"
  if(n == 0){
    return 1;
  }
  return n * silnia(n - 1); //rekurencja, funkcja przywołyje samą siebie, 
  //w NASA nie można robić takiego kodu bo raz im przez to wybuchł statek w '96 i radzą sobie bez tego,
  //NIE MOZNA PRZYWOŁYWAĆ SAMEJ SIEBIE W NASA, i polecam tak robić bo taki kod jest bezpieczniejszy. 
}
//przykład powiedzmy że chcemy zrobić silnie z 3, to wygląda to tak: 
//1wsze powtórzenie:
//silnia (3){
// return 3 * silnia(3-1)   // i póki ta "pętla" sie nie skonczy to program nie pójdzie dalej,
// zobaczcie że to zatrzymuje ten fragment kodu, 
// i czeka az wykona wszystkie przywołania samej siebie, 
//}
//2gie powtórzenie:
//silnia(3-1){
// return 3-1 * silnia(2-1)
//}
//itp itd... 

// inne wyjscie z rekurencji to zwrócenie wartości,
// Funkcja obliczająca silnię przy użyciu rekurencji ogonowej
// Parametr temp służy do akumulacji wyniku i ma wartość domyślną 1
unsigned long int silnia2(int x, unsigned long int temp = 1) {
    // Jeśli x osiągnie 0, zwracamy zgromadzony wynik (temp)
    if (x == 0)
        return temp;
    else
        // Rekurencyjne wywołanie funkcji z dekrementowanym x oraz zaktualizowanym akumulatorem
        return silnia2(x - 1, x * temp);
}
// jak to działa????? klasycznie przedstawie na przykładzie silni z 3 by nietrzeba było pisać dużo pierdolonych komentarzy bo oczy bolą od zielonego:
//
// 1wsze powtórzenie: 
// silnia2(3,1){
// return silnia2(3-1,3*1)
// }
//
// 2gie powtórzenie:
// silnia2(3-1,3*1){
// return silnia2((3-1)-1,(3-1)*3*1)
// }
//widać że wynik się nadpisuje ładnie samodzielnie i jest to bardziej przejrzyste niż zwykła rekurencja,
//problem w tym że sam koncept jest chyba trudniejszy do zrozumienia, ale jak się zrozumie to jest to o wiele lepsze rozwiązanie.
//ponieważ zakłada mniejsze komboniwanie z tzw: programowaniem abstrakcyjnym, jest tzw_2: kawa na ławę wylane
//
//
//

int main() {
    int liczba;
    
    // Pobieranie liczby od użytkownika, dla której chcemy obliczyć silnię
    cout << "Podaj liczbę, dla której chcesz obliczyć silnię: ";
    cin >> liczba;
    
    // Wywołanie funkcji silnia i wyświetlenie wyniku
    cout << "silnia(" << liczba << ") = " << silnia(liczba) << endl;
    
    // Wywołanie funkcji silnia2 (tzw: ta gorsza rekurencja/ rekurencja ogonowa) i wyświetlenie wyniku
    cout << "silnia2(" << liczba << ") = " << silnia2(liczba) << endl;
    
    return 0;
}
