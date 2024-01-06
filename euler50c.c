// euler50c - Сумма последовательных простых чисел

// Простое число 41 можно записать в виде суммы шести последовательных простых чисел:

// 41 = 2 + 3 + 5 + 7 + 11 + 13
// Это - самая длинная сумма последовательных простых чисел, 
// в результате которой получается простое число меньше одной сотни.

// Самая длинная сумма последовательных простых чисел, в результате которой получается простое число меньше одной тысячи, 
// содержит 21 слагаемое и равна 953.

// Какое из простых чисел меньше одного миллиона можно записать в виде суммы наибольшего количества последовательных 
// простых чисел?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 1000000                                         // длина массивов - зависит от размера искомого числа

bool is_composite(char comp_arr[], int num)
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
    int shift = (start % step == 0) ? 0 : step - (start % step);// смещение индекса start
    start += shift;                                             // первое составное число

    for (int i = start + step; i < finish; i += step)           // первое число - простое, не отмечаем его
    {
        if (!comp_arr[i])                                       // если еще не отмечено
            comp_arr[i] = 1;                                    // отмечаем составные числа

    }

    return 0;
}

int main(void)
{
    static char composit_arr[LEN_ARR] = { 0 };		            // массив[составное число] = 1 - static писать!
    int cnt_primes = 0;
    int answ = 0;
    int cnt_max = 0;
    int answ_max = 0;      
    
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    for (int num = 2; num < LEN_ARR; num++)                     // определяем список простых чисел (!составных)
    {
        // если число не отмечено составным -> проверяем число -> если число простое
        if (!composit_arr[num] && !is_composite(composit_arr, num))
            note_composite(composit_arr, num, num, LEN_ARR);    // отмечаем составные числа, кратные простому   
    }
    
    for(int i = 2; i < 10; i++)                                 // перебираем начальные числа
    {
        if(composit_arr[i])                                     // начинаем последовательноесть только с простых чисел
            continue;

        cnt_primes = 0;
        answ = 0;
        int num = i;

        while(answ + num < LEN_ARR)
        {
            if(composit_arr[num])                               // пропускаем составные числа
            {
                num++;
                continue;
            }

            answ += num;                                        // складываем простые числа
            cnt_primes++;                                       // количество простых чисел в ряду

            if(!composit_arr[answ] && cnt_primes > cnt_max)     // если число простое и ряд чисел длиннее
            {
                answ_max = answ;                                // обновляем максимумы
                cnt_max = cnt_primes;
            }

            num++;                                              // перебираем числа 
        }
    }

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %d runtime = %f\n", answ_max, time_spent); // выводим результат и время работы программы

    return 0;
}
