/*
Zadanie 3: Haszowanie z podwójnym haszowaniem (Double Hashing)

Opis teoretyczny:
Podwójne haszowanie to metoda otwartej adresacji, w której przy kolizji
kolejne pozycje wyznacza się wg wzoru:
    hashVal = (hash1(key) + i * hash2(key)) % arraySize
gdzie hash1 to główna funkcja haszująca, hash2 to funkcja pomocnicza (nie powinna dawać zera!).
Zapewnia bardzo dobre rozproszenie, minimalizuje zjawisko klastrowania.
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
    int prime; // do hash2

    int getPrimeLessThanSize() {
        // Zwroc najwieksza liczbe pierwsza < arraySize
        for (int i = arraySize - 1; i >= 2; --i) {
            bool isPrime = true;
            for (int j = 2; j * j <= i; ++j)
                if (i % j == 0) { isPrime = false; break; }
            if (isPrime) return i;
        }
        return 3;
    }

public:
    HashTable(int size) : arraySize(size) {
        hashArray.resize(arraySize, nullptr);
        pNonItem = new DataItem(-1);
        prime = getPrimeLessThanSize();
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
    int hashFunc1(int key) {
        return key % arraySize;
    }
    int hashFunc2(int key) {
        return prime - (key % prime);
    }
    void insert(DataItem* pItem) {
        int key = pItem->iData;
        int hashVal = hashFunc1(key);
        int stepSize = hashFunc2(key);
        int i = 0;
        int idx;
        do {
            idx = (hashVal + i * stepSize) % arraySize;
            if (!hashArray[idx] || hashArray[idx]->iData == -1) {
                hashArray[idx] = pItem;
                return;
            }
            i++;
        } while (i < arraySize);
        cout << "Brak miejsca na element!\n";
    }
    DataItem* remove(int key) {
        int hashVal = hashFunc1(key);
        int stepSize = hashFunc2(key);
        int i = 0;
        int idx;
        while (i < arraySize) {
            idx = (hashVal + i * stepSize) % arraySize;
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
        int hashVal = hashFunc1(key);
        int stepSize = hashFunc2(key);
        int i = 0;
        int idx;
        while (i < arraySize) {
            idx = (hashVal + i * stepSize) % arraySize;
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

    cout << "Tablica haszująca - podwójne haszowanie\n";
    cout << "Podaj rozmiar tablicy haszującej: ";
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