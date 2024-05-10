// euler24c - Словарные перестановки

// Перестановка - это упорядоченная выборка объектов.
// К примеру, 3124 является одной из возможных перестановок из цифр 1, 2, 3 и 4.
// Если все перестановки приведены в порядке возрастания или алфавитном порядке,
// то такой порядок будем называть словарным. Словарные перестановки из цифр 0, 1 и 2 представлены ниже:

// 012   021   102   120   201   210

// Какова миллионная словарная перестановка из цифр 0, 1, 2, 3, 4, 5, 6, 7, 8 и 9?

#include <stdio.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC
#include <stdbool.h>

#define LEN_ARR 10

int get_indx_arr(int indx_arr[], int count);
int get_factorial(int factorial[], int number);
text_t more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);
int show_permutation(int sort_arr[], int indx_arr[]);

int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    int num = 999999;                                       // искомый номер перестановки чисел (первоначальное положение тоже считается)
    int sort_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};        // отсортированные числа (которые будут переставляться)
    int indx_arr[LEN_ARR] = {0};                            // промежуточный ответ из индексов

    get_indx_arr(indx_arr, num);                            // вычисляем промежуточный ответ
    show_permutation(sort_arr, indx_arr);                   // выводим ответ

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf(" runtime = %f\n", time_spent);                  // выводим результат и время работы программы

    return 0;
}

int get_indx_arr(int indx_arr[], int count)
// Функция вычисляет промежуточный ответ из индексов и заносит их в массив
// параметры:	indx_arr[]  - массив, в котором хранится промежуточный ответ из индексов
//              count       - номер словарной перестановки
{
    int indx = 0;
    int factorial[LEN_ARR] = {0};                                   // факториалы чисел до 9!

    get_factorial(factorial, LEN_ARR - 1);                          // вычисляем факториалы

    for (int num = LEN_ARR - 1; num >= 0; num--)
    {
        indx_arr[indx++] = count / factorial[num];
        count %= factorial[num];
    }

    if (more_limit("get_indx_arr()", "count", count, "0", 0)) // остался остаток => занесено не все число
        return 1;

    return 0;
}

int get_factorial(int factorial[], int number)
// Функция вычисляет факториалы чисел и заносит их в массив
// параметры:	fact_arr[]  - массив, в котором хранятся факториалы чисел по их индексу
//              fact_arr[numb] = numb!
//              numb        - число, до которого ВКЛЮЧИТЕЛЬНО считаются факториалы
// return:      numb!
{
    if (more_limit("get_factorial()", "number", number, "LEN_ARR - 1", LEN_ARR - 1))  // обрабатываем выход за пределы массива
        return 0;

    factorial[0] = 1;                                                                       // 0! = 1
    for (int num = 1; num <= number; num++)
        factorial[num] = num * factorial[num - 1];

    return factorial[number];
}

text_t more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
    if (input_value > limit_value) // обрабатываем превышение
    {
        printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}

int show_permutation(int sort_arr[], int indx_arr[])
// Функция выводит на экран искомую перестановку
// параметры:	indx_arr[]  - массив, в котором хранится промежуточный ответ из индексов
//              sort_arr[]  - массив отсортированных по возрастанию чисел (из которых формируется перестановка)
{
    printf("answer = ");

    for (int indx = 0; indx < LEN_ARR; indx++)
    {
        if (more_limit("show_permutation()", "indx_arr[indx]", indx_arr[indx], "LEN_ARR - 1", LEN_ARR - 1)) 
            return 1;                                   // обрабатываем некорректные индексы в массиве

        printf("%d", sort_arr[indx_arr[indx]]);         // выводим число по индексу из отсортированного массива

        for (int i = indx_arr[indx]; i < LEN_ARR; i++)  // изымаем число из массива
            sort_arr[i] = sort_arr[i + 1];
    }

    return 0;
}

// #include <stdio.h>
// #include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
//     double time_spent = 0.0;                                // для хранения времени выполнения кода
//     clock_t begin = clock();                                // СТАРТ таймера

//     // искомый номер перестановки чисел (первоначальное положение тоже считается)
//     int num = 999999;
//     long long answ = 0;
//     int inter_answ[10] = {0};                   // промежуточный ответ
//     int arr[10] = {0,1,2,3,4,5,6,7,8,9};        // отсортированные числа
//     int arr_fact[10] = {1,1,1,1,1,1,1,1,1,1};   // факториалы до 9!

//     for(int i = 7, j = 1; i >= 0; i--)          //вычисляем факториалы
//         arr_fact[i] = (++j)*arr_fact[i+1];

//     //вычисляем 1000000-ное промежуточное число
//     for (int i = 0; i < 10; i++)
//     {
//         inter_answ[i] = num/arr_fact[i];
//         num = num%arr_fact[i];
//     }

//     //переводим промежуточное число в ответ - искомую перестановку чисел
//     long long place = 1000000000;               //разряд числа
//     for(int i = 0; i < 10; i++, place /= 10)
//     {
//         //берем число по индексу из отсортированного массива
//         answ += place*arr[inter_answ[i]];
//         //изымаем число из массива
//         for(int j = inter_answ[i]; j < 9; j++)
//             arr[j] = arr[j + 1];
//     }

//     // printf("%lld", answ);
//     clock_t end = clock();                                  // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

//     printf("answer = %lld runtime = %f\n", answ, time_spent);  // выводим результат и время работы программы

//     return 0;
// }