# Algorytmy i Struktury Danych – Drzewa AVL i Red-Black Tree

## Notatki własne na podstawie wykładów dr Andrzeja Pisarskiego

---

## 1. Drzewa AVL

**AVL Tree** to samobalansujące się drzewo binarne, w którym dla każdego węzła różnica wysokości lewego i prawego poddrzewa nie przekracza 1. Dzięki temu gwarantowany jest czas operacji O(log N).

### Struktura węzła AVL
```cpp
struct AVLTreeNode {
    int key;
    // (możliwe dodatkowe dane)
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode *parent;
    char balanceFactor; // 'L', 'R', '='
};
```

### Kluczowe operacje:

- **Insert** – wstawianie nowego węzła z zachowaniem własności AVL.
- **restoreAVL** – przywracanie balansu po wstawieniu węzła.
- **Rotacje** – klucz do naprawy balansu drzewa:
    - rotateLeft
    - rotateRight
    - podwójne rotacje: left-right oraz right-left

**Schemat działania Insert:**
1. Szukamy miejsca wstawienia węzła.
2. Znajdujemy ostatniego przodka, który może się rozbalansować.
3. Wstawiamy węzeł jako liść.
4. Przywracamy własność AVL za pomocą rotacji i aktualizacji balanceFactor.

**Przykład testowania drzewa AVL:**
Po każdej operacji wstawiania, wywołujemy `PrintTree()`, aby zobaczyć aktualny stan drzewa i współczynniki balansu.

```cpp
theAVLTree->Insert(createNewNode(50));
theAVLTree->PrintTree();

theAVLTree->Insert(createNewNode(20));
theAVLTree->PrintTree();

// itd.
```

---

## 2. Drzewa czerwono-czarne (Red-Black Tree)

Drzewo czerwono-czarne (RBT) to również samobalansujące się drzewo binarne, w którym w każdym węźle przechowujemy dodatkowy kolor (czerwony lub czarny).

**Dlaczego?**  
W zwykłym BST wstawienie posortowanych elementów prowadzi do bardzo nieefektywnego drzewa (wygląda jak lista). RBT gwarantuje O(log N) na wyszukiwanie, wstawianie i usuwanie.

### Własności drzewa czerwono-czarnego:
1. Każdy węzeł jest czerwony lub czarny.
2. Korzeń drzewa zawsze jest czarny.
3. Każde dziecko czerwonego węzła jest czarne (nie może być dwóch czerwonych po sobie).
4. Każda ścieżka od korzenia do liścia zawiera tyle samo czarnych węzłów.

### Struktura węzła RBT:
```cpp
class Node {
public:
    char iData;
    Node* pLeftChild;
    Node* pRightChild;
    int red; // 1 = red, 0 = black
    // ...
};
```

### Podstawowe operacje:

- **insert** – wstawia nowy węzeł i naprawia drzewo (rotacje + zamiany kolorów)
- **rotL/rotR** – rotacje odpowiednio w lewo i w prawo
- **find** – wyszukiwanie węzła po kluczu
- **traverse** – przechodzenie przez drzewo (preorder, inorder, postorder)
- **displayTree** – graficzne wypisanie drzewa

**Przykład automatycznego wstawiania znaków:**
```cpp
theTree.insert('A');
theTree.insert('S');
theTree.insert('E');
// itd.
```

### Główne różnice AVL vs. RBT:

| AVL Tree | Red-Black Tree |
|----------|----------------|
| Bardziej zbalansowane (wyższa wydajność wyszukiwania) | Szybsze wstawianie/usuwanie (mniej rotacji) |
| Używane w systemach wymagających szybkiego dostępu (np. bazy danych) | Stosowane w implementacjach STL, map, set, itp. |

---

## Materiały źródłowe

- Robert Lafore – “Teach Yourself Data Structures And Algorithms In 24 Hours”
- Robert Sedgewick – “Algorytmy w C++”
- Materiały wykładowe dr Andrzeja Pisarskiego

---

### TL;DR
- **AVL** – balansowanie przez wysokość, szybkie wyszukiwanie, więcej rotacji.
- **Red-Black** – balansowanie przez kolory, mniej rotacji, szybciej przy masowych wstawieniach/usuwaniach.

---

> Te notatki powstały na bazie przykładowych implementacji w C++ oraz omawianych przypadków testowych z zajęć.