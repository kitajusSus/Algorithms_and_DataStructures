# zajecia 5 AiSD
Zrobione cwiczenia:
- [Zadanie1.cpp](zadanie1.cpp) : 

# Abstrakcyjne typy danych. 
Abstrakcyjne typy danych (ADS, ang. Abstract Data Types) to koncepcje programistyczne, które definiują zbiór operacji na pewnym zbiorze danych bez ujawniania wewnętrznej implementacji struktur danych. Innymi słowy, ADS skupia się na tym, “co” robi dana struktura danych (jakie operacje można wykonać), a nie na tym, “jak” dokładnie są one realizowane w kodzie.
**Stacks and Queues**
- Programmer tools
- Restricted access to data
- ADS (abstrakcyjne typy danych): dane typy zdefiniowane w interfejsie, samodzielnie zrobione, 
- [Stacs](#Stacks)
- [Queues](#queues-kolejki)
- [Interfejs](#interfejs)

## Stacks (Stosy)
- Strukturę stosu można opisać metaforą “stos talerzy”: jedyny sposób, aby “dostać się” do przedmiotu w środku lub na samym dole, to najpierw zdjąć wszystko, co jest na górze.
- Podstawowe operacje:
  - Push (umieszczenie elementu na górze),
  - Pop (usunięcie elementu ze szczytu),
  - Top/Peek (podejrzenie elementu na szczycie bez usuwania go).
- Zasada działania: LIFO (Last In, First Out), czyli ostatni element dodany jest też pierwszym elementem usuniętym.

## Queues (Kolejki)
- Kolejkę można przyrównać do “kolejki w sklepie”: pierwsza osoba, która wchodzi do kolejki, jest też pierwszą obsłużoną (chyba że przeskoczy ktoś uprzywilejowany – w klasycznym ADS nie ma jednak takich wyjątków).
- Podstawowe operacje:
  - Enqueue (dodanie elementu na koniec kolejki),
  - Dequeue (usunięcie elementu z przodu kolejki),
  - Front/Peek (pobranie informacji o pierwszym elemencie bez jego usuwania).
- Zasada działania: FIFO (First In, First Out), czyli pierwszy element dodany jest też pierwszym elementem usuniętym.

## Interfejs
Interfejs w kontekście programowania to zbiór metod (funkcji), który określa sposób komunikacji z danym typem danych lub modułem oprogramowania. W przypadku abstrakcyjnych typów danych interfejs opisuje, jakie operacje (metody) są dostępne i jakie mają parametry, nie ujawniając szczegółów ich implementacji. Dzięki temu można wymieniać lub ulepszać implementację w tle, zachowując niezmieniony “kontrakt” (zestaw operacji) dla kodu, który z tych struktur korzysta.