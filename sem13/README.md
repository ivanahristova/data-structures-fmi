# Упражнение № 13
# Задачи върху дървета и графи.

### Задача 1. (Контролно 2021)
Нека е дадено двоично дърво от цели числа с възли, представени със следната структура:

    struct Node {int data, Node* left, Node* right;};

"Растящ път" в непразно дърво наричаме всеки път от корена на дървото до негово листо, такъв че стойностите на последователните елементи от пътя нарастват. Да се дефинира функция int maxpath(Node* t), където t е корен на непразно двоично дърво. Да се намери най-голямото число, което може да се получи при сумиране на елементите на някой нарастващ път от дървото. <br />

Пример: ((\*3\*)2*)1((\*9\*)1(\*8\*)) <br />
Най-голям растящ път: 1->2->3 : 6 <br />

### Задача 2. (Контролно 2021)
Нека е дадено двоично дърво. "Десен изглед" на дървото наричаме най-десните елементи от всяко от нивата на дървото, взети в ред от корена към листата (все едно гледаме дървото от дясната му страна).

Пример: ((\*2(\*5\*))1(\*3\*)) <br />
Десен изглед: 1,3,5 <br /> <br />
При представянето от предишната задача да се дефинира функция rightLook, която по корен на двоично дърво връща неговия десен изглед под формата на вектор или масив от числа. <br />

### Задача 3.
Да се напише функция, която проверява дали двоично дърво погледнато от ляво е същото като погледнато от дясно.