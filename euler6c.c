//euler6c - Разность между суммой квадратов и квадратом суммы
// Сумма квадратов первых десяти натуральных чисел равна 1^2 + 2^2 + ... + 10^2 = 385
// Квадрат суммы первых десяти натуральных чисел равен (1 + 2 + ... + 10)^2 = 55^2 = 3025
// Следовательно, разность между суммой квадратов и квадратом суммы первых десяти натуральных чисел составляет 3025 − 385 = 2640.
// Найдите разность между суммой квадратов и квадратом суммы первых ста натуральных чисел.

// брут-форс вариант 
// #include <stdio.h>
// #include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
//     int answer = 0;                                             // ответ
//     int sum_sq = 0;                                             // сумма квадратов
//     int sum_num = 0;                                            // сумма чисел

//     double time_spent = 0.0;                                    // для хранения времени выполнения кода
//     clock_t begin = clock();                                    // СТАРТ таймера

//     for (int num = 1; num < 101; num++)
//     {
//         sum_sq += num * num;
//         sum_num += num;
//     }
//     answer = sum_num * sum_num - sum_sq;

//     clock_t end = clock();                                      // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

//     printf("answer = %d runtime = %f\n", answer, time_spent);   // выводим результат и время работы программы                             
//     return 0;  
// }

// геометрическое решение 
#include <stdio.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{
    int answer;                                                 // ответ
    int num = 100;
    int sum_sq;                                                 // сумма квадратов
    int sum_num;                                                // сумма чисел
    
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    sum_num = (num * num + num) / 2;
    sum_sq = (num * (num + 1) * (2 * num + 1)) / 6;

    answer = sum_num * sum_num - sum_sq;

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %d runtime = %f\n", answer, time_spent);   // выводим результат и время работы программы 
    return 0;  
}