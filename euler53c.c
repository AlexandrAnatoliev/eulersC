// euler52c - Комбинаторные выборки

// Существует ровно десять способов выбора 3 элементов из множества пяти {1, 2, 3, 4, 5}:
// 123, 124, 125, 134, 135, 145, 234, 235, 245, и 345

// В комбинаторике для этого используется обозначение 5C3 = 10.
// В общем случае, nCr = n! / (r! * (n−r)!), где r ≤ n, n! = n×(n−1)×...×3×2×1 и 0! = 1.

// Это значение превышает один миллион, начиная с n = 23: 23C10 = 1144066.

// Cколько значений (не обязательно различных)  nCr для 1 ≤ n ≤ 100 больше одного миллиона?

#include <stdio.h>
#include <stdbool.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 102

typedef struct factors                                      // создаем структуру для хранения числа в виде ряда множителей
{                                                           // num = 2 * 3 * 4 * 18, к примеру
    char f_arr[LEN_ARR];                                    // массив[множитель] = 1 - есть такое число, 0 - нет
    int f_value;                                            // количество множителей в числе
} factors_t;                                                // для красоты меняем название типа данных "struct factors" -> "fаctоrs_t"

int factors_init(factors_t *number);
int mark_facrors(factors_t *number, int start, int finish);
bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);
int reduse_same_factors(factors_t *number1, factors_t *number2);
bool is_answer(factors_t *numerator, factors_t *denominator);

int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    int cnt = 0;

    factors_t numerator;                                    // числитель дроби
    factors_t denominator;                                  // знаменатель

    for (int r = 1; r <= 100; r++)
    {
        for (int n = r + 1; n <= 100; n++)
        {
            factors_init(&numerator);
            factors_init(&denominator);
            mark_facrors(&numerator, r + 1, n);             // n! / r!
            mark_facrors(&denominator, 1, n - r);           // (n - r)!
            reduse_same_factors(&numerator, &denominator);
            cnt += is_answer(&numerator, &denominator);
        }
    }

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("answer = %d runtime = %f\n", cnt, time_spent);  // выводим результат и время работы программы

    return 0;
}

int factors_init(factors_t *number)
// функция задает нулевые начальные значения
// параметры:	number  - число, состоящее из ряда множителей

{
    for (int fact = 0; fact < LEN_ARR; fact++)
        number->f_arr[fact] = 0;

    number->f_value = 0;

    return 0;
}

int mark_facrors(factors_t *number, int start, int finish)
// функция отмечает ряд множителей в массиве по их индексу: f_arr[fact] = 1
// параметры:	number  - число, состоящее из ряда множителей
//              start   - первый множитель с которого начинаем отмечать
//              finish  - последний множитель (ВКЛЮЧИТЕЛЬНО!!!)
// т.к. работаем с факториалами и запись 10! включает в себя множитель 10, удобнее заносить ряд множителей с последним ВКЛЮЧИТЕЛЬНО
// return:              - количество занесенных множителей в массив
{
    if (input_more_limit("mark_facrors()", "finish", finish, "LEN_ARR", LEN_ARR))   // обрабатываем выход за пределы массива
        return 0;
    if (input_more_limit("mark_facrors()", "start", start, "finish", finish))       // обрабатываем корректность значений start и finish
        return 0;

    int cnt = 0;
    for (int fact = start; fact <= finish; fact++, cnt++)
        number->f_arr[fact] = 1;

    number->f_value = cnt;

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
    if (input_value > limit_value)                                                  // обрабатываем превышение
    {
        printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}

int reduse_same_factors(factors_t *number1, factors_t *number2)
// функция сокращает одинаковые множители в массивах по их индексу
// параметры:	number1 - число 1, состоящее из ряда множителей
//              number2 - число 2
// return:      cnt     - количество сокращенных цифр
{
    if (input_more_limit("reduse_same_factors()", "number1->f_value", number1->f_value, "LEN_ARR", LEN_ARR)) 
        return 0;
    if (input_more_limit("reduse_same_factors()", "number2->f_value", number2->f_value, "LEN_ARR", LEN_ARR))
        return 0;                                           // в массиве не может быть больше элементов чем его длина

    int cnt = 0;
    int cnt_num1 = number1->f_value;
    int cnt_num2 = number2->f_value;

    for (int fact = 0; fact < LEN_ARR; fact++)
    {
        if (number1->f_arr[fact])                           // считаем пройденные множители в числах
            cnt_num1--;

        if (number2->f_arr[fact])
            cnt_num2--;

        if (number1->f_arr[fact] && number2->f_arr[fact])   // сокращаем множители, совпадающие в двух массивах
        {
            number1->f_arr[fact] = 0;
            number2->f_arr[fact] = 0;
            number1->f_value--;
            number2->f_value--;
            cnt++;
        }

        if (cnt_num1 == 0 || cnt_num2 == 0)                 // прерываем если в одном из чисел прошлись уже по всем множителям
            break;
    }

    return cnt;
}

bool is_answer(factors_t *numerator, factors_t *denominator)
// функция перемножает множители числителя и делит на множители знаменателя
// параметры:	fact_num    - числитель, состоит из ряда множителей
//              denom_num   - знаменатель
// return:      true        - количество выборок превышает один миллион
{
    if (input_more_limit("is_answer()", "numerator->f_value", numerator->f_value, "LEN_ARR", LEN_ARR))
        return 0;
    if (input_more_limit("is_answer()", "denominator->f_value", denominator->f_value, "LEN_ARR", LEN_ARR))
        return 0;                                                                       // выход запределы 

    unsigned long long num_tor = 1;                                                     // текущее произведение множителей в числителе
    int den_tor = 1;                                                                    // в знаменателе
    int num_fact = 1;                                                                   // текущий множитель из массива числителя
    int den_fact = 1;                                                                   // текущий множитель из массива знаменателя

    while (numerator->f_value || denominator->f_value)  // пока есть еще не использованные множители в числителе или знаменателе 
    {
        while ((den_tor == 1 || numerator->f_value == 0) && den_fact < LEN_ARR && denominator->f_value)
        // знаменатель равен единице или в числителе кончились множители  
        {                                                                              
            if (denominator->f_arr[den_fact])                                           // если есть множитель
            {
                den_tor *= den_fact++;                                                  // увеличиваем знаменатель
                denominator->f_value--;
            }

            else
                den_fact++;                                                             // ищем следующий множитель в знаменателе
        }

        while ((num_tor % den_tor || denominator->f_value == 0) && num_fact < LEN_ARR && numerator->f_value)
        // числитель не делится нацело на знаменатель или в знаменателе кончились множители
        {
            if (denominator->f_value == 0 && den_tor == 1 && num_tor > 1000000)
                return true;                                                            // если в знаменателе 1 и кончились множители

            else if (numerator->f_arr[num_fact])
            {
                num_tor *= num_fact++;                                                  // увеличиваем числитель
                numerator->f_value--;
            }

            else
                num_fact++;                                                             // ищем следующий множитель числителя
        }

        if (num_tor % den_tor == 0)                                                     // сокращаем дробь
        {
            num_tor /= den_tor;
            den_tor = 1;
        }

        if (numerator->f_value == 0 && denominator->f_value == 0 && num_tor > 1000000)  // перебрали все множители числителя и знаменателя
            return true;

        if (numerator->f_value == 0 && num_tor <= 1000000)                              // в числителе кончились множители
            return false;
    }

    return false;
}