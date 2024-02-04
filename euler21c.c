// euler21c - Дружественные числа

// Пусть d(n) определяется как сумма делителей n (числа меньше n, делящие n нацело).
// Если d(a) = b и d(b) = a, где a ≠ b, то a и b называются дружественной парой,
// а каждое из чисел a и b - дружественным числом.

// Например, делителями числа 220 являются 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 и 110, поэтому d(220) = 284.
// Делители 284 - 1, 2, 4, 71, 142, поэтому d(284) = 220.

// Подсчитайте сумму всех дружественных чисел меньше 10000.

#include <stdio.h>
#include <math.h>   // для sqrt()
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <iso646.h> // заменяет &&, ||, ! на and, or, not

#define LEN_ARR 10000

int get_sum_div(int num);

int main(void)
{
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    static int div_arr[LEN_ARR] = {0};                          // массив для хранения сумм делителей числа по их индексу

    int answ = 0;                                               // сумма всех дружественных чисел

    for (int num = 1; num < LEN_ARR; num++)                     // перебираем числа
    {
        div_arr[num] = get_sum_div(num);                        // записываем их делители
        // div_arr[220] = 284 - сумма делителей числа 220 = 284

        if ((div_arr[div_arr[num]] == num) and (div_arr[num] != num))
        // (arr[220] = 284 => arr[arr[220]] => arr[284] == 220) И (220 != 284)
        {
            answ += num;                                        // число
            answ += div_arr[num];                               // дружественное ему число
            printf("%5d %5d\n", num, div_arr[num]);
        }
    }

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answers = %d runtime = %f\n", answ, time_spent);    // выводим результат и время работы программы

    return 0;
}

int get_sum_div(int num)
// функция возвращает сумму делителей числа
// параметры:	num - раскладываемое на множители число
// return:          - сумма делителей числа (начиная от 1)
{
    if (num < 1)                            // отрабатываем некорректные значения
    {
        printf("get_sum_div(): Num = % d! Used number more 0\n", num);
        return 0;
    }

    int sum_div = 1;                        // любое число делится на один

    int max_div = sqrt(num) + 1;            // выносим перед циклом for(), чтобы не вычислять на каждой итерации

    for (int div = 2; div < max_div; div++) // перебираем делители числа
    {
        if (num % div == 0)
        {
            sum_div += div;                 // добавляем меньший делитель
            sum_div += num / div;           // и больший
        }
    }

    return sum_div;
}

// #include <stdio.h>
// #include <math.h>

// int get_sum_div(int num_arg)
// //возвращает сумму делителей числа
// {
//     int div_arr[100] = {0};                         //массив для делителей числа
//     int div_cnt = 0;
//     int sum_div = 0;
//     for(int i = 1; i < (int)sqrt(num_arg) + 1; i++)
//     //определяем делители числа
//     {
//         if(num_arg%i == 0)
//         {
//             if(i == 1)
//                 div_arr[div_cnt++] = i;
//             else if(i != num_arg/i)
//             {
//                 div_arr[div_cnt++] = i;             //добавляем меньший делитель числа
//                 div_arr[div_cnt++] = num_arg/i;     //добавляем больший делитель числа
//             }
//         }
//     }
//     for(int i = 0; i < div_cnt; i++)
//         sum_div += div_arr[i];                      //сумма делителей числа
//     return sum_div;
// }

// int main(void)
// {
//     int sum_div;
//     int fr_num;                                         //дружественное число
//     int sum_fr_num = 0;                                 //сумма всех дружественных чисел

//     for(int num = 1; num < 10000; num++)                //перебираем числа
//     {
//         fr_num = get_sum_div(num);                      //потенциальное дружественное число
//         sum_div = get_sum_div(fr_num);                  //сумма множителей потенциального дружественного числа

//         if(sum_div == num && num != fr_num)             //если d(a) = b и d(b) = a, где a ≠ b
//             sum_fr_num += (num + fr_num);
//     }
//     printf("%d",sum_fr_num/2);
//     return 0;
// }
