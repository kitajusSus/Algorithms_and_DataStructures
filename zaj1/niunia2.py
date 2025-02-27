import random
import statistics

# Baza danych1: minimalny próg przyjęcia na studia (ostatnie lata)
database1 = [55,54,55,56,55,55,67,60,52,52]

# Baza danych2: ilość punktów uzyskanych przez osobę aplikującą (tutaj wpisujemy 50)
database2 = 50.7 
"""
minimalna ilosc punktów jakie masz bez matury z chemii pol = 80%, mat = 80%, ang=90%
"""

# Obliczenie średniej i odchylenia standardowego z bazy danych1
mean_db1 = statistics.mean(database1)
std_db1 = statistics.stdev(database1)  # odchylenie standardowe

print(f"Średni próg punktowy z poprzednich lat: {mean_db1}")
print(f"Odchylenie standardowe progów punktowych: {std_db1}")

# Przygotuj 100 klas, każda o pojemności 60 osób
classes = []
for _ in range(1000):
    class_scores = [mean_db1 + random.uniform(-std_db1, std_db1) for _ in range(60)]
    classes.append(class_scores)

# Funkcja do obliczenia procentowego wskaźnika wygranych dla danego wyniku
def calculate_winratio(database2):
    win_count = 0
    for class_scores in classes:
        if database2 > min(class_scores):
            win_count += 1
    winratio = (win_count / len(classes)) * 100
    return winratio

# Symulacja dla wyników od x do x+10
x = database2
print(f"Wynik, {database2} jest to wynik otrzymany z matura z chemii =1%")
for i in range(11):
    current_score = x + i
    winratio = calculate_winratio(current_score)
    print(f"Dla wyniku {current_score:.1f}, procentowy wskaźnik wygranych (winratio): {winratio:.2f}%")
