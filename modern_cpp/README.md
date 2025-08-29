# Przykłady nowoczesnego C++

Katalog zawiera krótkie programy pokazujące zalety wykorzystania funkcji z C++20.

## ranges_examples.cpp

Demonstruje użycie biblioteki `std::ranges` do przetwarzania kolekcji:

- budowanie potoków z `views::filter` i `views::transform`,
- operacje algorytmiczne (`std::ranges::all_of`) bez konieczności podawania par iteratorów,
- leniwa ewaluacja – transformacje są wykonywane dopiero podczas iteracji.

## concepts_sort.cpp

Plik prezentuje użycie `concepts` do ograniczania typów przy sortowaniu. Funkcja
`sort_and_print` przyjmuje jedynie zakresy spełniające zdefiniowany koncept
`SortableRange` (losowy dostęp + możliwość porównania i sortowania). Pozwala to na:

- wykrywanie błędów w czasie kompilacji,
- klarowniejsze definiowanie wymagań wobec parametrów szablonu,
- lepszą czytelność i bezpieczeństwo kodu.

Nowe możliwości języka upraszczają kod i redukują liczbę błędów, co jest szczególnie
ważne w bardziej rozbudowanych projektach.
