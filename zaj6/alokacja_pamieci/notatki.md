# Co to jest malloc?
`malloc` (ang. memory allocation) to funkcja standardowej biblioteki w językach C i C++, która służy do dynamicznego alokowania pamięci na stercie. Funkcja malloc jest zdefiniowana w nagłówku <stdlib.h> w C i <cstdlib> w C++. Zwraca wskaźnik do początku zaalokowanego bloku pamięci.

# Jak używać malloc?
Składnia: `void* malloc(size_t size);`
```cpp
#include <iostream>
#include <cstdlib>

int main() {
    int *arr;
    int n = 5;
    
    // Alokacja pamięci dla tablicy 5 liczb całkowitych
    arr = (int*)malloc(n * sizeof(int));
    
    // Sprawdzenie, czy alokacja pamięci się powiodła
    if (arr == NULL) {
        std::cerr << "Nie udało się zaalokować pamięci." << std::endl;
        return 1;
    }
    
    // Zapis wartości do zaalokowanej pamięci
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    
    // Wyświetlenie wartości zapisanych w pamięci
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    
    // Zwolnienie zaalokowanej pamięci
    free(arr);
    
    return 0;
}
```
- `Parametr size`: Określa liczbę bajtów do zaalokowania.
- Zwracana wartość: Wskaźnik do zaalokowanego bloku pamięci lub NULL, jeśli alokacja się nie powiodła.

1. Alokacja pamięci:
Funkcja malloc alokuje blok pamięci na stercie o rozmiarze podanym w parametrze size. W powyższych przykładach alokujemy pamięć dla tablicy 5 liczb całkowitych (`int`).

W C: `arr = (int*)malloc(n * sizeof(int));`
W C++: `arr = (int*)malloc(n * sizeof(int));`
2. Sprawdzenie alokacji:
Po alokacji należy sprawdzić, czy malloc zwrócił wskaźnik NULL, co oznacza, że alokacja pamięci się nie powiodła.

W C: `if (arr == NULL)`
W C++: `if (arr == NULL)`
3. Użycie zaalokowanej pamięci:
Jeśli alokacja się powiodła, możemy używać zaalokowanej pamięci, np. zapisując wartości do tablicy.

W C: `for (int i = 0; i < n; ++i) { arr[i] = i + 1; }`
W C++: `for (int i = 0; i < n; ++i) { arr[i] = i + 1; }`
4. Zwolnienie pamięci:
Po zakończeniu używania zaalokowanej pamięci, należy ją zwolnić za pomocą funkcji free, aby uniknąć wycieków pamięci.

W C: `free(arr);`
W C++: `free(arr);`


# zig !!!!!!!!!

**Zarządzanie pamięcią w Zig**
W przeciwieństwie do C/C++, Zig nie polega na funkcjach standardowej biblioteki takich jak malloc. Zamiast tego, oferuje własne mechanizmy zarządzania pamięcią, które są bardziej solidne i bezpieczniejsze.
```zig
const std = @import("std");

pub fn main() void {
    const allocator = std.heap.page_allocator;

    var arr = try allocator.alloc(u32, 5);
    defer allocator.free(arr);

    for (arr) |*item, index| {
        item.* = @intCast(u32, index + 1);
    }

    for (arr) |item| {
        std.debug.print("{} ", .{item});
    }
}
```
Kluczowe cechy zarządzania pamięcią w Zig:
- **Interfejs Allocator:** Zig używa interfejsu allocator do obsługi alokacji pamięci. Pozwala to na definiowanie niestandardowych allocatorów i większą kontrolę nad zarządzaniem pamięcią.
- **Bezpieczeństwo:** Zarządzanie pamięcią w Zig ma na celu zminimalizowanie typowych problemów takich jak wycieki pamięci i przepełnienia bufora.
- **Jawna alokacja i dealokacja:** Chociaż Zig wspiera ręczne zarządzanie pamięcią, zachęca do jawnych i bezpieczniejszych praktyk.



# Różnice między malloc w C/C++ a zarządzaniem pamięcią w Zig
- Funkcja vs. Interfejs: malloc jest wywołaniem funkcji w C/C++, natomiast Zig używa abstrakcyjnego interfejsu allocator.
- Bezpieczeństwo: Zarządzanie pamięcią w Zig jest zaprojektowane z funkcjami bezpieczeństwa, aby zminimalizować typowe problemy takie jak wycieki pamięci i przepełnienia bufora, które są powszechne w C/C++.
- Niestandardowe allocatory: W Zig można definiować niestandardowe allocatory dostosowane do specyficznych potrzeb, oferując większą elastyczność i kontrolę nad zarządzaniem pamięcią.