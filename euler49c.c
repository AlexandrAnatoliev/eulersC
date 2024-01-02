// euler49c - Перестановки простых чисел

// Арифметическая прогрессия: 1487, 4817, 8147, в которой каждый член возрастает на 3330, необычна в двух отношениях: 
// (1) каждый из трех членов является простым числом, (2) все три четырехзначные числа являются перестановками друг друга.

// Не существует арифметических прогрессий из трех однозначных, двухзначных и трехзначных простых чисел, 
// демонстрирующих это свойство. Однако, существует еще одна четырехзначная возрастающая арифметическая прогрессия.

// Какое 12-значное число образуется, если объединить три члена этой прогрессии?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 100000                                          // длина массивов - зависит от размера искомого числа

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

int get_permutation(int numb, int perm_num)
// функция вычисляет перестановку числа 
// не превышать максимальный номер перестановки - 23! при больших будет счистывать "мусорные" значения за массивом
// параметры:	num         - число
//              perm_num    - порядковый номер перестановки числа (меньший 24!)             
// return:      перестановленное числа
{
    int fact_arr[] = { 6, 2, 1, 1 };                              // факториалы чисел {3! 2! 1! 0!} 
    int indx_arr[4] = { 0 };
    int numb_arr[4] = { 0 };
    int answ_arr[4] = { 0 };
    int answ = 0;

    for (int i = 0; i < 4; i++)                                  // преобразуем порядковый номер в массив с индексами
    {
        indx_arr[i] = perm_num / fact_arr[i];
        perm_num %= fact_arr[i];
    }

    for (int i = 3; i >= 0; i--)                                 // раскладываем число на цифры в массив
    {
        numb_arr[i] = numb % 10;
        numb /= 10;
    }

    for (int i = 0; i < 4; i++)                                 // делаем нужную перестановку цифр в числе
    {
        answ_arr[i] = numb_arr[indx_arr[i]];                    // выбираем число из отсортированного массива
        for (int j = indx_arr[i]; j < (3 - i); j++)             // смещаем числа в массиве
            numb_arr[j] = numb_arr[j + 1];
    }

    for (int i = 0, j = 1000; i < 4; i++, j /= 10)              // преобразуем массив чисел обратно в число
        answ += answ_arr[i] * j;

    return answ;
}

int sort_arr(int arr[], int len_arr)
// функция сортирует массив "пузырьком" по возрастанию
// параметры:	arr[]   - указатель на массив чисел
//              len_arr - количество чисел в массиве 

{
    int max_num;
    for (int i = 0; i < len_arr; i++)
    {
        max_num = arr[0];                                       // берем первое число из массива
        for (int j = 1; j < len_arr; j++)
        {
            if (arr[j] > max_num)
            {
                arr[j - 1] = max_num;                           // обновляем максимум
                max_num = arr[j];
            }
            else
                arr[j - 1] = arr[j];                            // смещаем числа в массиве
        }
        arr[len_arr - 1] = max_num;                             // записываем последенее число в массиве
    }
    return 0;
}

bool is_sequence(int arr[], int len_arr)
// функция ищет в массиве арифметическую прогрессию
// параметры:	arr[]   - указатель на массив чисел
//              len_arr - количество чисел в массиве 
// return:      true    - в массиве есть арифметическая прогрессия
{
    int diff_arr[23] = { 0 };                                     // массив с разностями ряда чисел перестановок

    for (int i = 0; i < len_arr - 1; i++)
        diff_arr[i] = arr[i + 1] - arr[i];

    for (int i = 0; i < len_arr - 2; i++)
    {
        int diff_1 = diff_arr[i];
        int i_ptr = i;

        while (i_ptr < len_arr - 2)
        {
            int diff_2 = diff_arr[i_ptr + 1];
            for (int j = i_ptr + 1; j < len_arr - 1; j++)
            {
                if (diff_1 > diff_2 && (j + 1) < (len_arr - 1))
                    diff_2 += diff_arr[j + 1];
                else if (diff_1 == diff_2)
                {
                    // выводим ответ (пишем все три числа подряд)
                    printf("answer: %d%d%d\n", arr[i], arr[i_ptr + 1], arr[j + 1]);
                    return true;
                }
                else
                    break;
            }
            i_ptr++;
            diff_1 += diff_arr[i_ptr];
        }
    }
    return false;
}
int main(void)
{
    static char composit_arr[LEN_ARR] = { 0 };		            // массив[составное число] = 1 - static писать!       
    static int used_numbs[LEN_ARR] = { 0 };                     // использованные в процессе вычисления числа
    int mult_arr[24] = { 0 };
    int mult_cnt = 0;
    int num = 1000;
    int mult_num;
    bool answ_fl = false;
    int answ_cnt = 0;                                           // счетчик ответов

    double time_spent = 0.0;                                    // для хранения времени выполнения кода

    clock_t begin = clock();                                    // СТАРТ таймера

    for (int num = 2; num < LEN_ARR; num++)                     // определяем список простых чисел (!составных)
    {
        // если число не отмечено составным -> проверяем число -> если число простое
        if (!composit_arr[num] && !is_composite(composit_arr, num))
            note_composite(composit_arr, num, num, LEN_ARR);    // отмечаем составные числа, кратные простому   
    }

    while (!answ_fl && num < 10000)
    {
        mult_cnt = 0;                                           // сетчик количества перестановок
        num++;                                                  // перебираем числа

        if (composit_arr[num])                                  // пропускаем составные числа
            continue;

        for (int i = 0; i < 24; i++)
        {
            mult_num = get_permutation(num, i);

            if (mult_num > 999 && !composit_arr[mult_num] && !used_numbs[mult_num])
            // если перестановка - трехзначное и простое число и еще не использовалось
            {
                used_numbs[mult_num] = 1;                       // помечаем число как использованное
                mult_arr[mult_cnt++] = mult_num;                // заносим его в массив
            }
        }

        sort_arr(mult_arr, mult_cnt);                           // сортируем массив по возрастанию

        answ_fl = is_sequence(mult_arr, mult_cnt);              // проверяем найден ли ответ

        if(answ_fl && !answ_cnt)                                // пропускаем первый ответ из задания
        {
            answ_cnt++;
            answ_fl = false;
        }     
    }

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("runtime = %f\n", time_spent);                       // время работы программы

    return 0;
}
