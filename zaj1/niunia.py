import random
import statistics

# Baza danych1: minimalny próg przyjęcia na studia (ostatnie lata)
# Używamy 10 elementów, każdy o wartości 1
database1 = [52,52,50,56,50,55,67,60,52,52]

# Baza danych2: ilość punktów uzyskanych przez osobę aplikującą (tutaj wpisujemy 50)
database2 = 50.7 
"""
minimalna ilosc punktów jakie masz bez matury z chemii pol = 80%, mat = 80%, ang=90%
"""

# Obliczenie średniej i odchylenia standardowego z bazy danych1
mean_db1 = statistics.mean(database1)
std_db1 = statistics.stdev(database1)  # odchylenie standardowe

print(f"Średni wynik z bazy danych1: {mean_db1}")
print(f"Odchylenie standardowe z bazy danych1: {std_db1}")

# Przygotuj 100 symulacji:
# Dla każdej symulacji losujemy wynik jako: mean_db1 ± losowa wartość z przedziału [-std_db1, std_db1]
simulated_scores = []
for _ in range(100):
    random_deviation = random.uniform(-std_db1, std_db1)  # losujemy wartość w przedziale [-std_db1, std_db1]
    simulated_score = mean_db1 + random_deviation
    simulated_scores.append(simulated_score)

# Znajdź najniższy wynik spośród symulacji
min_simulated = min(simulated_scores)
print(f"Najniższy wynik ze symulacji: {min_simulated}")

# Porównaj wynik z bazy danych2 z najniższym wynikiem symulacji
# Obliczamy, ile razy wynik z bazy danych2 (50) jest wyższy niż najniższy wynik
if min_simulated != 0:
    ratio = database2 / min_simulated
else:
    ratio = float('inf')  # jeśli najniższy wynik wynosi 0, stosunek jest nieskończony

print(f"Wynik matury dla ({database2}) jest {ratio:.2f} razy wyższy niż najniższy wynik symulacji.")
    
# Oblicz procentowy wskaźnik wygranych (winratio)
win_count = sum(1 for score in database1 if database2 > score)
winratio = (win_count / len(database1)) * 100

print(f"Procentowy wskaźnik wygranych (winratio): {winratio:.2f}%")

