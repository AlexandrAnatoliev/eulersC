// euler14c - Самая длинная последовательность Коллатца

// Следующая повторяющаяся последовательность определена для множества натуральных чисел:
//  n → n/2 (n - четное)
//  n → 3n + 1 (n - нечетное)

// Используя описанное выше правило и начиная с 13, сгенерируется следующая последовательность:
// 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
// Получившаяся последовательность (начиная с 13 и заканчивая 1) содержит 10 элементов.
// Хотя это до сих пор и не доказано (проблема Коллатца (Collatz)), предполагается,
// что все сгенерированные таким образом последовательности оканчиваются на 1.

// Какой начальный элемент меньше миллиона генерирует самую длинную последовательность?

// Примечание: Следующие за первым элементы последовательности могут быть больше миллиона.

// #include <stdio.h>
// int main(void)
// {
//     unsigned long long n = 13;
//     // важно использовать тип unsigned long long т.к в процессе вычислений цепочки получаются огромные числа
//     int first_n;
//     int max_count = 0;
//     for (int i = 1; i < 1000000; i++)
//     {
//         n = i;
//         int count = 1;
//         while (n != 1)
//         {
//             if(n%2 == 0)
//                 n = n / 2;
//             else
//                 n = 3 * n + 1;
//             count++;
//         }
//         if (max_count < count)
//         {
//             max_count = count;
//             first_n = i;
//         }
//     }
//     printf("%d",first_n);
//     return 0;
// }

// вариант для сайта

#include <stdio.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 1000000

int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    static int len_seq_arr[LEN_ARR] = {0};                  // массив для хранения длин цепочек чисел
    unsigned long long n;

    // важно использовать тип unsigned long long т.к в процессе вычислений цепочки получаются огромные числа

    int answ;
    int max_count = 0;

    for (int i = 1; i < LEN_ARR; i++)
    {
        n = i;
        int count = 1;

        while (n > 1) // n != 1
        {
            if (n < LEN_ARR && len_seq_arr[n])              // для данного числа уже считалась длина цепочки
            {
                count += len_seq_arr[n];
                break;
            }

            n = !(n & 1) ? (n >> 1) : (3 * n + 1);          // n = (n%2 == 0) ? n/2 : 3*n+1;
            count++;
        }

        if (n < LEN_ARR)
            len_seq_arr[i] = count;                         // заносим длину цепочки для числа в массив

        if (max_count < count)                              // обновляем ответ
        {
            max_count = count;
            answ = i;
        }
    }

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("answer = %d runtime = %f\n", answ, time_spent); // выводим результат и время работы программы
    return 0;
}