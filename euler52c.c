// euler52c - Перестановочные кратные

// Видно, что число 125874 и оно же удвоенное 251748, содержат точно такие же цифры, но в другом порядке.

// Найдите такое наименьшее натуральное число x, чтобы 2x, 3x, 4x, 5x и 6x состояли из одних и тех же цифр.

#include <stdio.h>
#include <stdbool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 10

int count_digits(int dig_ar[], int num);
text_t compare(int dig_ar1[], int dig_ar2[]);
void clear_arr(int dig_ar[]);

int main(void)
{
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    int answ = 0;
    int cnt = 0;                                                // счетчик количества совпадений

    while (cnt < 4)                                             // 4 совпадения для 2x, 3x, 4x, 5x и 6x
    {
        answ++;
        cnt = 0;
        int dig_arr1[LEN_ARR] = {0};                            // массивы для хранения количества цифр в числе по их индексу
        int dig_arr2[LEN_ARR] = {0};                            // обновляем массивы для каждого нового числа
        // при достаточно длинном числе возможно большое количество одинаковых цифр в нем, массив позволяет не ограничивать их количество

        count_digits(dig_arr1, answ);                           // считаем цифры в числе

        for (int i = 2; i < 6; i++)                             // ищем совпадения
        {
            count_digits(dig_arr2, answ * i);
            if (compare(dig_arr1, dig_arr2))
            {
                clear_arr(dig_arr2);                            // обнуляем массив для повторного использования
                cnt++;
            }

            else
                break;
        }
    }

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answers = %d runtime = %f\n", answ, time_spent);    // выводим результат и время работы программы

    return 0;
}

int count_digits(int dig_ar[], int num)
// функция считает количество разных цифр в числе
// параметры:	dig_ar[]        - массив для сохранения количества цифр в числе
//              dig_ar[6] = 2   - в числе две цифры 6
//              num             - проверяемое число
// return:                      - количество цифр в числе
{
    if (LEN_ARR < 10)                               // отрабатываем некорректные значения
    {
        printf("count_digits(): LEN_ARR = % d! "    // % d - пробел нужен, чтобы выравнять значения -1 и 1 в при выводе в столбик
               "Used LEN_ARR more 10\n",
               LEN_ARR);                            // красивый вывод в одну строчку
        return 0;
    }

    int cnt = 0;
    while (num)
    {
        dig_ar[num % 10]++;                         // раскладываем число на цифры и подсчитываем их
        num /= 10;
        cnt++;
    }
    return cnt;
}

text_t compare(int dig_ar1[], int dig_ar2[])
// функция сранивает соответствие цифр в двух числах (двух массивов)
// параметры:	dig_ar1[]   - массив с посчитанными цифрами первого числа
//              dig_ar2[]   - массив с посчитанными цифрами второго числа
// return:      true        - цифры в числах (массивы) совпадают
{
    if (LEN_ARR < 10)                       // отрабатываем некорректные значения
    {
        printf("compare(): LEN_ARR = % d! " // % d - пробел нужен, чтобы выравнять значения -1 и 1 в при выводе в столбик
               "Used LEN_ARR more 10\n",
               LEN_ARR);                    // красивый вывод в одну строчку

        return 0;
    }

    for (int i = 0; i < LEN_ARR; i++)
        if (dig_ar1[i] != dig_ar2[i])
            return false;

    return true;
}

void clear_arr(int dig_ar[])
// функция заполняет массив нулями
// параметры:	dig_ar[]    - массив с посчитанными цифрами числа
{
    for (int i = 0; i < LEN_ARR; i++)
        dig_ar[i] = 0;
}