Poniżej znajdziesz kompletny przykład w języku Zig, który pozwala na:

    Kompresję (kodowanie) pliku tekstowego algorytmem Huffmana,
    Dekompresję (rozpakowanie) pliku wcześniej zakodowanego tym samym programem.

Wszystko znajduje się w jednym pliku źródłowym huffman.zig.
Działanie programu:

Wywołanie 
```bash
zig run huffman.zig encode input.txt output.huff
````
spowoduje odczytanie pliku `input.txt`, zakodowanie (skompresowanie) za pomocą Huffmana i zapisanie wyniku w pliku `output.huff`.

*Uwaga techniczna*:
W tym przykładzie nie kodujemy bitów „upakowanych” w bajty, tylko zapisujemy sekwencję bitów w formie znaków '0'/'1'. Dzięki temu możesz łatwo podejrzeć zakodowany plik i sprawdzić, jak wygląda ciąg bitów. Nie jest to jednak maksymalnie efektywna kompresja – w praktyce warto byłoby spakować bity faktycznie do bajtów.

Mimo wszystko kod doskonale ilustruje ideę algorytmu Huffmana i pozwala na bezproblemową dekompresję.



