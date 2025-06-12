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
        hashArray.resize(arraySize);
        for (int j = 0; j < arraySize; j++)
            hashArray[j] = nullptr;
        pNonItem = new DataItem(-1);
    }

    ~HashTable() {
        for (auto item : hashArray) {
            if (item != nullptr && item != pNonItem) {
                delete item;
            }
        }
        delete pNonItem;
    }

    void displayTable() {
        cout << "Table: ";
        for (int j = 0; j < arraySize; j++) {
            if (hashArray[j] != nullptr && hashArray[j] != pNonItem)
                cout << hashArray[j]->iData << " ";
            else
                cout << "** ";
        }
        cout << endl;
    }

    int hashFunc(int key) {
        return key % arraySize;
    }

    void insert(DataItem* pItem) {
        int key = pItem->iData;
        int hashVal = hashFunc(key);
        while (hashArray[hashVal] != nullptr && hashArray[hashVal]->iData != -1) {
            ++hashVal;
            hashVal %= arraySize;
        }
        hashArray[hashVal] = pItem;
    }

    DataItem* remove(int key) {
        int hashVal = hashFunc(key);

        while (hashArray[hashVal] != nullptr) {
            if (hashArray[hashVal]->iData == key) {
                DataItem* pTemp = hashArray[hashVal];
                hashArray[hashVal] = pNonItem;
                return pTemp;
            }
            ++hashVal;
            hashVal %= arraySize;
        }
        return nullptr;
    }

    DataItem* find(int key) {
        int hashVal = hashFunc(key);

        while (hashArray[hashVal] != nullptr) {
            if (hashArray[hashVal]->iData == key)
                return hashArray[hashVal];
            ++hashVal;
            hashVal %= arraySize;
        }
        return nullptr;
    }
};

int main() {
    DataItem* pDataItem;
    int aKey, size, n, keysPerCell;
    time_t aTime;
    char choice = 'b';

    cout << "Enter size of hash table: ";
    cin >> size;
    cout << "Enter initial number of items: ";
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
        cout << "Enter first letter of: show (s), insert (i), delete (d), or find (f), or exit (x): ";
        cin >> choice;

        switch (choice) {
            case 's':
                theHashTable.displayTable();
                break;
            case 'i':
                cout << "Enter key value to insert: ";
                cin >> aKey;
                pDataItem = new DataItem(aKey);
                theHashTable.insert(pDataItem);
                break;
            case 'd':
                cout << "Enter key value to delete: ";
                cin >> aKey;
                pDataItem = theHashTable.remove(aKey);
                if (pDataItem != nullptr && pDataItem != theHashTable.find(-1))
                    delete pDataItem;
                break;
            case 'f':
                cout << "Enter a key value to find: ";
                cin >> aKey;
                pDataItem = theHashTable.find(aKey);
                if (pDataItem != nullptr)
                    cout << "Found " << aKey << endl;
                else
                    cout << "Could not find " << aKey << endl;
                break;
            case 'x':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid entry\n";
        }
    }
    return 0;
}