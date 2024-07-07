// euler1c - Числа, кратные 3 или 5
// Если выписать все натуральные числа меньше 10, кратные 3 или 5, то получим 3, 5, 6 и 9.
// Сумма этих чисел равна 23. Найдите сумму всех чисел меньше 1000, кратных 3 или 5.

// test
// первый вариант
#include <stdio.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{
    int res = 0;

    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    for (int i = 1; i < 1000; i++)                          // перебираем числа
        if (!(i % 3) || !(i % 5))                           // если i%3 == 0 или i%5 == 0
            res += i;                                       // складываем числа

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("answer = %d runtime = %f\n", res, time_spent);  // выводим результат и время работы программы

    return 0;
}

// // второй вариант
// #include <stdio.h>
// #include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
//     int res = 0;

//     double time_spent = 0.0;                                    // для хранения времени выполнения кода
//     clock_t begin = clock();                                    // СТАРТ таймера

//     for(int i = 0; i < 1000; i += 3)                            // складываем числа кратные 3
//         res += i;
//     for(int i = 0; i < 1000; i += 5)                            // прибавляем числа кратные 5
//         res += i;
//     for(int i = 0; i < 1000; i += 15)                           // вычитаем числа кратные 15
//         res -= i;

//     clock_t end = clock();                                      // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

//     printf("answer = %d runtime = %f\n", res, time_spent);      // выводим результат и время работы программы

//     return 0;
// }