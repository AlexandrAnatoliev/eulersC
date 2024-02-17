// euler23c - Неизбыточные суммы

// Совершенным числом называется число, у которого сумма его делителей равна самому числу.
// Например, сумма делителей числа 28 равна 1 + 2 + 4 + 7 + 14 = 28, что означает,
// что число 28 является совершенным числом.

// Число n называется недостаточным, если сумма его делителей меньше n, и называется избыточным,
// если сумма его делителей больше n.

// Так как число 12 является наименьшим избыточным числом (1 + 2 + 3 + 4 + 6 = 16), наименьшее число,
// которое может быть записано как сумма двух избыточных чисел, равно 24.
// Используя математический анализ, можно показать, что все целые числа больше 28123 могут быть записаны
// как сумма двух избыточных чисел. Эта граница не может быть уменьшена дальнейшим анализом,
// даже несмотря на то, что наибольшее число, которое не может быть записано как сумма двух избыточных чисел,
// меньше этой границы.

// Найдите сумму всех положительных чисел, которые не могут быть записаны как сумма двух избыточных чисел.

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 28124

int get_sum_divisors(int number);
bool is_abundant(int number);
bool is_sum_abudants(const char abudant_arr[], int number);

int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    unsigned long long sum = 0;                             // искомая сумма
    char abundant_arr[LEN_ARR] = {0};                       // массив[число] == 1 - число избыточное

    for (int num = 3; num < LEN_ARR; num++)                 // заполняем массив избыточными числами
        abundant_arr[num] = is_abundant(num);

    for (int num = 1; num < LEN_ARR; num++)                 // считаем неизбыточные
    {
        if (is_sum_abudants(abundant_arr, num) == false)
            sum += num;
    }

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (end - begin) / CLOCKS_PER_SEC;           // время работы в секундах

    printf("answer = %d runtime = %f\n", sum, time_spent);  // выводим результат и время работы программы
    return 0;
}

int get_sum_divisors(int number)
// Функция возвращает сумму делителей числа
// параметры:	number  - раскладываемое число
// return:      sum_div - сумма делителей числа
{
    int sum_div = 1;                                        // на 1 число делится всегда
    int sqrt_num = sqrt(number) + 1;                        // вычисление корня заранее ускоряет расчеты

    for (int div = 2; div < sqrt_num; div++)
    {
        if (number % div == 0)                              // найден делитель
        {
            if (div != number / div)
            {
                sum_div += div;                             // добавляем меньший делитель числа
                sum_div += number / div;                    // добавляем больший делитель числа
            }
            else
                sum_div += div;                             // добавляем только один делитель числа
        }
    }

    return sum_div;
}

bool is_abundant(int number)
// Функция вернет true, если число избыточное
// параметры:	number  - раскладываемое число
{
    return get_sum_divisors(number) > number;
}

bool is_sum_abudants(const char abudant_arr[], int number)
// Функция возвращает true, если число может быть записано как сумма двух избыточных чисел.
// параметры:	number          - раскладываемое число
//              abudant_arr[]   - массив избыточных чисел
// return:      true            - если число может быть записано как сумма двух избыточных чисел
{
    if (number > 28123)         // все целые числа больше 28123 могут быть записаны как сумма двух избыточных чисел
        return true;

    for (int num = 3; num < number; num++)
    {
        if (abudant_arr[num] && abudant_arr[number - num])
            return true;
    }

    return false;
}
