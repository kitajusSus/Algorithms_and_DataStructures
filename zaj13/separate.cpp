/*
Zadanie 4: Haszowanie z łańcuchowaniem (Separate Chaining)

Opis teoretyczny:
Metoda łańcuchowa (separate chaining) polega na tym, że każda komórka tablicy haszującej
zawiera wskaźnik na listę (np. listę jednokierunkową) wszystkich elementów o tej samej wartości klucza haszującego.
Kolizje są obsługiwane poprzez dołączanie do listy na odpowiedniej pozycji.
Zalety: brak ograniczenia na liczbę elementów, które mogą być skojarzone z jednym hashem.
*/

#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

class HashTable {
private:
    vector<list<int>> table;
    int arraySize;

public:
    HashTable(int size) : arraySize(size) {
        table.resize(arraySize);
    }
    void displayTable() {
        cout << "Table:\n";
        for (int i = 0; i < arraySize; ++i) {
            cout << i << ": ";
            for (int val : table[i])
                cout << val << " ";
            cout << endl;
        }
    }
    int hashFunc(int key) {
        return key % arraySize;
    }
    void insert(int key) {
        int idx = hashFunc(key);
        table[idx].push_front(key);
    }
    bool remove(int key) {
        int idx = hashFunc(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (*it == key) {
                table[idx].erase(it);
                return true;
            }
        }
        return false;
    }
    bool find(int key) {
        int idx = hashFunc(key);
        for (int val : table[idx])
            if (val == key)
                return true;
        return false;
    }
};

int main() {
    int aKey, size, n, keysPerCell;
    time_t aTime;
    char choice = 'b';

    cout << "Tablica haszująca - separate chaining (łańcuchy)\n";
    cout << "Podaj rozmiar tablicy haszującej: ";
    cin >> size;
    cout << "Podaj początkową liczbę elementów: ";
    cin >> n;
    keysPerCell = 10;
    HashTable theHashTable(size);
    srand(static_cast<unsigned>(time(&aTime)));
    for (int j = 0; j < n; j++) {
        aKey = rand() % (keysPerCell * size);
        theHashTable.insert(aKey);
    }
    while (choice != 'x') {
        cout << "\nWybierz: show (s), insert (i), delete (d), find (f), exit (x): ";
        cin >> choice;
        switch (choice) {
            case 's':
                theHashTable.displayTable();
                break;
            case 'i':
                cout << "Podaj wartość do wstawienia: ";
                cin >> aKey;
                theHashTable.insert(aKey);
                break;
            case 'd':
                cout << "Podaj wartość do usunięcia: ";
                cin >> aKey;
                if (!theHashTable.remove(aKey))
                    cout << "Nie znaleziono " << aKey << endl;
                break;
            case 'f':
                cout << "Podaj wartość do wyszukania: ";
                cin >> aKey;
                if (theHashTable.find(aKey))
                    cout << "Znaleziono " << aKey << endl;
                else
                    cout << "Nie znaleziono " << aKey << endl;
                break;
            case 'x':
                cout << "Koniec.\n";
                break;
            default:
                cout << "Błąd wyboru.\n";
        }
    }
    return 0;
}