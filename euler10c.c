// euler10c - Сложение простых чисел
// Сумма простых чисел меньше 10 равна 2 + 3 + 5 + 7 = 17.
// Найдите сумму всех простых чисел меньше двух миллионов.

// #include <stdio.h>
// #include <stdbool.h>
// #include <math.h>

// bool is_simple(int num_arg)
// //true - если число простое
// {
//     int i_arg = sqrt(num_arg) + 1;
    
//     for (int i = 2; i < i_arg; i++)
//     {
//         if (num_arg%i == 0) 
//             return false;
//     }
//     return true;
// }

// int main(void)
// {    
//     long long answ = 0;                      
//     for (int i = 2; i < 2000000; i++)
//     {
//         if (is_simple(i)) 
//             answ += i;
//     }  
//     printf("%lld",answ);                     
//     return 0;  
// }

// вариант через Решето Эрастосфена

// euler10c - Сложение простых чисел
// Сумма простых чисел меньше 10 равна 2 + 3 + 5 + 7 = 17.
// Найдите сумму всех простых чисел меньше двух миллионов.

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 2000000                                         // длина массивов - зависит от размера искомого числа

text_t is_composite(char comp_arr[], int num)
// функция принимает число и возвращает true - если число составное
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              num                 - проверяемое число    
// return:      true                - если число составное!
{
    int div_max = sqrt(num) + 1;                                // выносим вычисление квадратного корня из цикла for

    for (int div = 2; div < div_max; div++)                     // чтобы он не вычислялся каждую итерацию цикла
    {
        // пропускаем составные делители и срабатываем при num % i == 0
        if (!comp_arr[div] && !(num % div))
            return true;
    }

    return false;
}

int note_composite(char comp_arr[], int step, int start, int finish)
// функция отмечает составные числа в массиве
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              step                - простое число, служит шагом
//              start               - начальный индекс в массиве
//              finish              - конечный индекс 
// return:                          - количество отмеченных составных чисел
{
    int cnt = 0;
    int shift = (start % step == 0) ? 0 : step - (start % step);// смещение индекса start
    start += shift;                                             // первое составное число

    for (int i = start; i < finish; i += step)
    {
        if (!comp_arr[i])                                       // если еще не отмечено
        {
            comp_arr[i] = 1;                                    // отмечаем составные числа
            cnt++;                                              // и считаем их
        }
    }

    return cnt;
}

int main(void)
{
    static char composit_arr[LEN_ARR] = { 0 };		            // массив[состаное число] = 1 - static писать!                                  
    long long answ = 0;

    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    for (int num = 2; num < LEN_ARR; num++)
    {
        // если число не отмечено составным -> проверяем число -> если число простое
        if (!composit_arr[num] && !is_composite(composit_arr, num)) 
        {
            note_composite(composit_arr, num * 2, num, LEN_ARR);    // отмечаем составные числа, кратные простому
            answ += num;                                        // складываем простое число с остальными
        } 
    }

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %lld   runtime = %f\n", answ, time_spent);
    return 0;
}
