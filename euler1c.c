// euler1c - Числа, кратные 3 или 5
// Если выписать все натуральные числа меньше 10, кратные 3 или 5, то получим 3, 5, 6 и 9. 
// Сумма этих чисел равна 23. Найдите сумму всех чисел меньше 1000, кратных 3 или 5.

// первый вариант
/*#include <stdio.h>

int main(void)
{
    int res = 0;                    
    for (int i = 1; i < 1000; i++)  // перебираем числа
        if (!(i % 3) || !(i % 5))   // если i%3 == 0 или i%5 == 0
            res += i;               // складываем числа

    printf("%d", res);              // выводим результат           
    return 0;
}*/

// второй вариант
#include <stdio.h>

int main(void)
{
    int res = 0;
    for(int i = 0; i < 1000; i += 3)    // складываем числа кратные 3
        res += i;
    for(int i = 0; i < 1000; i += 5)    // прибавляем числа кратные 5
        res += i;
    for(int i = 0; i < 1000; i += 15)   // вычитаем числа кратные 15
        res -= i;
    printf("%d", res);                  // выводим результат      
    return 0;
}