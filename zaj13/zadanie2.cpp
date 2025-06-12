/*
Zadanie 2: Wyszukiwanie kwadratowe (Quadratic Probing)

Opis teoretyczny:
Tablica haszująca z otwartą adresacją i kwadratowym próbkowaniem.
Przy kolizji, kolejne próby są realizowane według wzoru: 
    hashVal = (hash(key) + i^2) % arraySize, gdzie i = 1, 2, 3, ...
Zapobiega klastrowaniu pierwotnemu, ale nie wtórnemu.
Wymaga, by rozmiar tablicy był liczbą pierwszą dla gwarancji znalezienia pustego miejsca.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class DataItem {
public:
    int iData;
    DataItem(int ii) : iData(ii) {}
};

class HashTable {
private:
    vector<DataItem*> hashArray;
    int arraySize;
    DataItem* pNonItem;

public:
    HashTable(int size) : arraySize(size) {
        hashArray.resize(arraySize, nullptr);
        pNonItem = new DataItem(-1);
    }
    ~HashTable() {
        for (auto item : hashArray)
            if (item && item != pNonItem) delete item;
        delete pNonItem;
    }
    void displayTable() {
        cout << "Table: ";
        for (int j = 0; j < arraySize; j++)
            if (hashArray[j] && hashArray[j] != pNonItem)
                cout << hashArray[j]->iData << " ";
            else
                cout << "** ";
        cout << endl;
    }
    int hashFunc(int key) {
        return key % arraySize;
    }
    void insert(DataItem* pItem) {
        int key = pItem->iData;
        int hashVal = hashFunc(key);
        int i = 0;
        int idx;
        do {
            idx = (hashVal + i * i) % arraySize;
            if (!hashArray[idx] || hashArray[idx]->iData == -1) {
                hashArray[idx] = pItem;
                return;
            }
            i++;
        } while (i < arraySize);
        cout << "Brak miejsca na element!\n";
    }
    DataItem* remove(int key) {
        int hashVal = hashFunc(key);
        int i = 0;
        int idx;
        while (i < arraySize) {
            idx = (hashVal + i * i) % arraySize;
            if (!hashArray[idx])
                return nullptr;
            if (hashArray[idx]->iData == key) {
                DataItem* temp = hashArray[idx];
                hashArray[idx] = pNonItem;
                return temp;
            }
            i++;
        }
        return nullptr;
    }
    DataItem* find(int key) {
        int hashVal = hashFunc(key);
        int i = 0;
        int idx;
        while (i < arraySize) {
            idx = (hashVal + i * i) % arraySize;
            if (!hashArray[idx])
                return nullptr;
            if (hashArray[idx]->iData == key)
                return hashArray[idx];
            i++;
        }
        return nullptr;
    }
};

int main() {
    DataItem* pDataItem;
    int aKey, size, n, keysPerCell;
    time_t aTime;
    char choice = 'b';

    cout << "Tablica haszująca - kwadratowe próbkowanie\n";
    cout << "Podaj rozmiar tablicy haszującej (najlepiej liczba pierwsza!): ";
    cin >> size;
    cout << "Podaj początkową liczbę elementów: ";
    cin >> n;
    keysPerCell = 10;
    HashTable theHashTable(size);
    srand(static_cast<unsigned>(time(&aTime)));
    for (int j = 0; j < n; j++) {
        aKey = rand() % (keysPerCell * size);
        pDataItem = new DataItem(aKey);
        theHashTable.insert(pDataItem);
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
                pDataItem = new DataItem(aKey);
                theHashTable.insert(pDataItem);
                break;
            case 'd':
                cout << "Podaj wartość do usunięcia: ";
                cin >> aKey;
                pDataItem = theHashTable.remove(aKey);
                if (pDataItem && pDataItem->iData != -1) delete pDataItem;
                break;
            case 'f':
                cout << "Podaj wartość do wyszukania: ";
                cin >> aKey;
                pDataItem = theHashTable.find(aKey);
                if (pDataItem)
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