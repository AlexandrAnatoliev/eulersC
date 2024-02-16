// euler52c - Комбинаторные выборки

// Существует ровно десять способов выбора 3 элементов из множества пяти {1, 2, 3, 4, 5}:
// 123, 124, 125, 134, 135, 145, 234, 235, 245, и 345

// В комбинаторике для этого используется обозначение 5C3 = 10.
// В общем случае, nCr = n! / (r! * (n−r)!), где r ≤ n, n! = n×(n−1)×...×3×2×1 и 0! = 1.

// Это значение превышает один миллион, начиная с n = 23: 23C10 = 1144066.

// Cколько значений (не обязательно различных)  nCr для 1 ≤ n ≤ 100 больше одного миллиона?

#include <stdio.h>
#include <stdbool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 102

typedef struct factors         // создаем структуру для хранения числа в виде ряда множителей
{                              // num = 2 * 3 * 4 * 18, к примеру
    char factors_arr[LEN_ARR]; // массив[множитель] = 1 - есть такое число, 0 - нет
    int factors_value;         // количество множителей в числе
} factors_t;                   // для красоты меняем название типа данных "struct factors" -> "fаctоrs_t"

bool factors_init(factors_t *number);
int mark_facrors(factors_t *number, int start, int finish);
bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);
int reduse_same_factors(factors_t *number1, factors_t *number2);
bool is_answer(factors_t *fact_num, factors_t *denom_num);

int main(void)
{
    double time_spent = 0.0; // для хранения времени выполнения кода
    clock_t begin = clock(); // СТАРТ таймера

    int cnt = 0;

    factors_t fact;
    factors_t denom;
    // factors_init(&fact);
    // factors_init(&denom);
    // mark_facrors(&fact, 3 + 1, 5); // 5! / 3!
    // mark_facrors(&denom, 1, 5 - 3); // (5 - 3)!
    // reduse_same_factors(&fact, &denom);

    // cnt = is_answer(&fact,&denom);

    for (int r = 1; r <= 100; r++)
    {
        for (int n = r + 1; n <= 100; n++)
        {
    // for (int r = 33; r <= 33; r++)
    // {
    //     for (int n = 64; n <= 64; n++)
    //     {
            factors_init(&fact);
            factors_init(&denom);
            mark_facrors(&fact, r + 1, n); // 5! / 3! n! / r!
            mark_facrors(&denom, 1, n - r); // (5 - 3)! (n - r)!
            reduse_same_factors(&fact,&denom);
            cnt += is_answer(&fact,&denom);
        }
    }
    clock_t end = clock();                                // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

    printf("answers = %d runtime = %f\n", cnt, time_spent); // выводим результат и время работы программы

    return 0;
}

bool factors_init(factors_t *number)
// функция задает нулевые начальные значения
// параметры:	number  - число, состоящее из ряда множителей
// return:      true    - успешная инициализация
{
    for (int fact = 0; fact < LEN_ARR; fact++)
        number->factors_arr[fact] = 0;

    number->factors_value = 0;
    return true;
}

int mark_facrors(factors_t *number, int start, int finish)
// функция отмечает ряд множителей в массиве по их индексу: factors_arr[fact] = 1
// параметры:	number  - число, состоящее из ряда множителей
//              start   - первый множитель с которого начинаем отмечать
//              finish  - последний множитель (ВКЛЮЧИТЕЛЬНО!!!)
// т.к. работаем с факториалами и запись 10! включает в себя множитель 10, удобнее заносить ряд множителей с последним ВКЛЮЧИТЕЛЬНО
// return:              - количество занесенных множителей в массив
{
    if (input_more_limit("mark_facrors()", "finish", finish, "LEN_ARR", LEN_ARR)) // обрабатываем выход за пределы массива
        return 0;
    if (input_more_limit("mark_facrors()", "start", start, "finish", finish)) // обрабатываем корректность значений start и finish
        return 0;

    int cnt = 0;
    for (int fact = start; fact <= finish; fact++, cnt++)
        number->factors_arr[fact] = 1;

    number->factors_value = cnt;
    return cnt;
}

bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
    if (input_value > limit_value) // отрабатываем превышение
    {
        printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}

int reduse_same_factors(factors_t *number1, factors_t *number2)
// функция сокращает одинаковые множители в массивах по их индексу
// параметры:	number1 - число1, состоящее из ряда множителей
//              number2 - число2
// return:              - количество сокращенных цифр
{
    if (input_more_limit("reduse_same_factors()", "number1->factors_value", number1->factors_value, "LEN_ARR", LEN_ARR)) // в массиве не может быть больше элементов, чем его длина
        return 0;
    if (input_more_limit("reduse_same_factors()", "number2->factors_value", number2->factors_value, "LEN_ARR", LEN_ARR))
        return 0;

    int cnt = 0;
    int cnt_num1 = number1->factors_value;
    int cnt_num2 = number2->factors_value;

    for (int fact = 0; fact < LEN_ARR; fact++)
    {
        if (number1->factors_arr[fact]) // считаем пройденные множители в числах
            cnt_num1--;
        if (number2->factors_arr[fact])
            cnt_num2--;

        if (number1->factors_arr[fact] && number2->factors_arr[fact]) // сокращаем множители, совпадающие в двух массивах
        {
            number1->factors_arr[fact] = 0;
            number2->factors_arr[fact] = 0;
            number1->factors_value--;
            number2->factors_value--;
            cnt++;
        }
        if (cnt_num1 == 0 || cnt_num2 == 0) // прерываем если в одном из чисел прошлись уже по всем множителям
            break;
    }
    return cnt;
}

bool is_answer(factors_t *fact_num, factors_t *denom_num)
// функция перемножает множители числителя и делит на множители знаменателя
// параметры:	fact_num    - числитель, состоит из ряда множителей
//              denom_num   - знаменатель
// return:      true        - количество выборок превышает один миллион
{
    if (input_more_limit("is_answer()", "fact_num->factors_value", fact_num->factors_value, "LEN_ARR", LEN_ARR)) // в массиве не может быть больше элементов, чем его длина
        return 0;
    if (input_more_limit("is_answer()", "denom_num->factors_value", denom_num->factors_value, "LEN_ARR", LEN_ARR))
        return 0;

    unsigned long long factor = 1; // числа большие, могут переполняться при недостаточном типе данных
    int denom = 1;
    int denom_indx = 1;
    int factor_indx = 1;
    // cnt_n_munus_r--;
    // int cnt_fact = fact_num->factors_value;

    while ((fact_num->factors_value || denom_num->factors_value) && (denom_indx < LEN_ARR || factor_indx < LEN_ARR))
    {
        while (denom_indx < LEN_ARR && (denom == 1 || fact_num->factors_value == 0) && denom_num->factors_value) // увеличиваем числитель
        {
            if (denom_num->factors_arr[denom_indx])
            {
                denom *= denom_indx; // увеличиваем знаменатель
                denom_num->factors_value--;
                denom_indx++; // убрать? упростить
            }
            else
                denom_indx++; // ищем следующий множитель в знаменателе
        }

        while (factor_indx < LEN_ARR && fact_num->factors_value && (factor % denom || (denom == 1 && denom_num->factors_value == 0))) // если числитель не делится нацело на знаменатель
        {
            if (factor > 1000000 && denom == 1 && denom_num->factors_value == 0)
                return true;

            else if (fact_num->factors_arr[factor_indx])
            {
                factor *= factor_indx; // увеличиваем числитель
                fact_num->factors_value--;
                factor_indx++;
            }
            else
                factor_indx++; // ищем следующий множитель числителя
        }

        if (factor % denom == 0)
        {
            factor /= denom;
            denom = 1;
        }

        // if (cnt_n_munus_r == 0 && denom == 1 && factor > 1000000) // в знаменателе сократили все множители
        //     return true;

        if (fact_num->factors_value == 0 && denom_num->factors_value == 0 && factor > 1000000) // перебрали все множители числителя и значенателя
            return true;

        if (fact_num->factors_value == 0 && factor <= 1000000)
            return false;
    }

    return false;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

// #define LEN_ARR 102

// int mark_facrors(char arr[], int start, int finish);
// bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);
// int reduse_same_num(char arr1[], int cnt_arr1, char arr2[], int cnt_arr2);
// bool is_answer(char n_div_r_arr[], int cnt_n_div_r, char n_munus_r_arr[], int cnt_n_munus_r);

// int main(void)
// {
//     double time_spent = 0.0; // для хранения времени выполнения кода
//     clock_t begin = clock(); // СТАРТ таймера

//     int cnt = 0;

//     for (int r = 2; r <= 100; r++)
//     {
//         for (int n = r + 1; n <= 100; n++)
//         {
//             char n_div_r_arr[LEN_ARR] = {0}; // n! / r!
//             char n_munus_r_arr[LEN_ARR] = {0};
//             int n_div_r = mark_facrors(n_div_r_arr, r + 1, n + 1);
//             int n_minus_r = mark_facrors(n_munus_r_arr, 1, n - r + 1);
//             int same = reduse_same_num(n_div_r_arr, n_div_r, n_munus_r_arr, n_minus_r);
//             cnt += is_answer(n_div_r_arr, n_div_r - same, n_munus_r_arr, n_minus_r - same);
//         }
//     }
//     clock_t end = clock();                                // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

//     printf("answers = %d runtime = %f\n", cnt, time_spent); // выводим результат и время работы программы

//     return 0;
// }

// int mark_facrors(char arr[], int start, int finish)
// // функция отмечает множители в массиве по их индексу: arr[num] = 1
// // параметры:	arr[]   - массив для хранения множителей
// //              start   - с этого числа отмечает
// //              finish  - до этого числа отмечает
// // return:              - количество занесенных цифр в массив
// {
//     if (input_more_limit("mark_factor()", "finish", finish, "LEN_ARR", LEN_ARR)) // обрабатываем выход за пределы массива
//         return 0;
//     if (input_more_limit("mark_factor()", "start", start, "finish", finish)) // обрабатываем корректность значений start и finifh
//         return 0;

//     int cnt = 0;
//     for (int i = start; i < finish; i++, cnt++)
//         arr[i] = 1;
//     return cnt;
// }

// bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// // функция определяет превышение переменной своего предельного значения и выводит предупреждение
// // параметры:   *name_func  - название функции
// //              input_value - значение переменной
// //              *name_input - название переменной
// //              limit_value - предельное значение
// //              *name_limit - название предельного значения
// // return:      true        - при превышении
// {
//     if (input_value > limit_value) // отрабатываем превышение
//     {
//         printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
//         return true;
//     }

//     return false;
// }

// int reduse_same_num(char arr1[], int cnt_arr1, char arr2[], int cnt_arr2)
// // функция сокращает одинаковые множители в массивах по их индексу
// // параметры:	arr1[]      - массив 1 для хранения множителей
// //              cnt_arr1    - количество множителей в нем
// //              arr2[]      - массив 2 для хранения множителей
// //              cnt_arr1    - количество множителей в нем
// // return:                  - количество сокращенных цифр
// {
//     if (input_more_limit("reduse_same_num()", "cnt_arr1", cnt_arr1, "LEN_ARR", LEN_ARR)) // в массиве не может быть больше элементов, чем его длина
//         return 0;
//     if (input_more_limit("reduse_same_num()", "cnt_arr2", cnt_arr2, "LEN_ARR", LEN_ARR))
//         return 0;

//     int cnt = 0;

//     for (int i = 0; i < LEN_ARR; i++)
//     {
//         if (arr1[i]) // считаем пройденные множители в массивах
//             cnt_arr1--;
//         if (arr2[i])
//             cnt_arr2--;

//         if (arr1[i] && arr2[i]) // сокращаем множители, совпадающие в двух массивах
//         {
//             arr1[i] = 0;
//             arr2[i] = 0;
//             cnt++;
//         }
//         if (cnt_arr1 == 0 || cnt_arr2 == 0) // прерываем если в одном из массиво прошли по всем множителям
//             break;
//     }
//     return cnt;
// }

// bool is_answer(char n_div_r_arr[], int cnt_n_div_r, char n_munus_r_arr[], int cnt_n_munus_r)
// // функция перемножает множители числителя и делит на множители знаменателя
// // параметры:	n_div_r_arr[]   - массив для хранения множителей числителя
// //              cnt_n_div_r     - количество множителей в нем
// //              n_munus_r_arr[] - массив для хранения множителей знаменателя
// //              cnt_n_munus_r   - количество множителей в нем
// // return:      true        - количество выборок превышает один миллион
// {
//     if (input_more_limit("is_answer()", "cnt_n_div_r", cnt_n_div_r, "LEN_ARR", LEN_ARR)) // в массиве не может быть больше элементов, чем его длина
//         return 0;
//     if (input_more_limit("is_answer()", "cnt_n_munus_r", cnt_n_munus_r, "LEN_ARR", LEN_ARR))
//         return 0;

//     unsigned long long factor = 1;
//     int denom = 1;
//     int denom_num = 2;
//     int factor_num = 2;
//     cnt_n_munus_r--;

//     while ((cnt_n_munus_r || cnt_n_div_r) && (denom_num < LEN_ARR || factor_num < LEN_ARR))
//     {
//         if (denom_num < LEN_ARR && n_munus_r_arr[denom_num] == 0)
//             denom_num++; // ищем следующий множитель в знаменателе

//         if (denom_num < LEN_ARR && cnt_n_munus_r && n_munus_r_arr[denom_num])
//         {
//             denom *= denom_num; // увеличиваем знаменатель
//             cnt_n_munus_r--;
//             denom_num++;
//         }

//         while (factor_num < LEN_ARR && (factor % denom || (denom == 1 && cnt_n_munus_r == 0))) // если числитель не делится нацело на знаменатель
//         {
//             if (n_div_r_arr[factor_num] == 0)
//                 factor_num++; // ищем следующий множитель числителя

//             if (cnt_n_div_r && n_div_r_arr[factor_num])
//             {
//                 factor *= factor_num; // увеличиваем числитель
//                 cnt_n_div_r--;
//                 factor_num++;
//             }
//         }

//         if (factor % denom == 0)
//         {
//             factor /= denom;
//             denom = 1;
//         }

//         if (cnt_n_munus_r == 0 && denom == 1 && factor > 1000000) // в знаменателе сократили все множители
//             return true;

//         if (cnt_n_munus_r == 0 && cnt_n_div_r == 0 && factor > 1000000) // перебрали все множители числителя и значенателя
//             return true;

//         if (cnt_n_div_r == 0 && factor <= 1000000)
//             return false;
//     }

//     return false;
// }