// euler27c - Квадратичные простые числа

// Эйлер опубликовал свою замечательную квадратичную формулу :

// n2 + n + 41

// Оказалось, что согласно данной формуле можно получить 40 простых чисел, последовательно подставляя значения 0≤n≤39

// Однако, при n = 40,
//  402 + 40 + 41 = 40(40 + 1) + 41
// делится на 41 без остатка, и, очевидно, при n = 41, 412 + 41 + 41
// делится на 41 без остатка.
//
// При помощи компьютеров была найдена невероятная формула

// n2−79n + 1601

//, согласно которой можно получить 80 простых чисел для последовательных значений n
// от 0 до 79. Произведение коэффициентов −79 и 1601 равно −126479.

// Рассмотрим квадратичную формулу вида :

// n2 + an + b
//, где | a | < 1000
//     и | b | ≤1000
//
//     где | n |
//     является модулем(абсолютным значением) n
//
//     К примеру, | 11 |= 11 и | −4 |= 4
//     Найдите произведение коэффициентов a и b квадратичного выражения,
//  согласно которому можно получить максимальное количество простых чисел для последовательных значений n, начиная со значения n = 0

#include <stdio.h>
#include <stdbool.h>                                            // для красоты кода использую bool
#include <math.h>                                               // для использовании функции sqrt()
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC
#include <stdlib.h>                                             // для calloc() и free()
#include <locale.h>                                             // русский язык в printf()

void *my_realloc(char *arr, int *len_arr, int len_add);
int note_prime_arr(char *comp_arr, int len_arr, int start, int finish);
bool is_composite(char comp_arr[], int len_arr, int num);
int note_composite(char comp_arr[], int len_arr, int prime, int start, int finish);
int count_primes(char comp_arr[], int *len_arr, int a, int b);
bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    setlocale(LC_ALL, "Rus");                                   // русский язык в printf()

    int len_arr = 1000;                                         // первонячальная длина массива
    int answ, cnt_max = 0;

    char *comp_arr = calloc(len_arr, sizeof(char));             // массив для хранения составных чисел

    note_prime_arr(comp_arr, len_arr, 2, len_arr);               // заполняем массив составными числами

    for (int a = -1000; a < 1000; a++)                          // в цикле перебираю все возможные коэффициенты
    {
        for (int b = -1000; b < 1000; b++)
        {
            int cnt = count_primes(comp_arr, &len_arr, a, b);   // считаю последовальные простые числа

            if (cnt > cnt_max)                                  // обновляем значения коэффициентов
            {
                cnt_max = cnt;
                answ = a * b;
            }
        }
    }

    free(comp_arr);                                             // освобождаем место

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("Ответ = %d время = %f\n", answ, time_spent);        // выводим результат и время работы программы
    return 0;
}

void *my_realloc(char *arr, int *len_arr, int len_add)
// Функция увеличивает размер массива
// Параметры:	arr[]   - массив с ранее вычисленными составными числами
//              len_arr - старая длина массива
//              len_add - на сколько увеличиваем массив
// return:      указатель на увеличенный массив
{
    char *new_arr = calloc(*len_arr + len_add, sizeof(char));   // создаем увеличенный массив

    if (new_arr == NULL)
    {
        printf("my_realloc: функция не смогла выделить место под массив");
        return arr;
    }

    for (int i = 0; i < *len_arr; i++)
        new_arr[i] = arr[i];                                    // копируем данные в новый массив из старого

    free(arr);                                                  // освобождаем память старого массива

    arr = new_arr;                                              // присваиваем адрес нового массива
    *len_arr += len_add;                                        // перезаписываем длину массива

    return arr;
}

int note_prime_arr(char *comp_arr, int len_arr, int start, int finish)
// Функция отмечает составные числа в массиве
// Параметры:	comp_arr[]  - массив с ранее вычисленными составными числами
//              len_arr     - длина массива
//              start       - начальное число
//              finish      - конечное число
{
    // отмечаем составные числа на основе ранее найденных простых
    for (int num = 2; num < start; num++)
        if (!comp_arr[num])                                         // если число не отмечено составным (простое)
            note_composite(comp_arr, len_arr, num, start, finish);  // отмечаем составные числа, кратные простому

    // ищем новые простые числа и отмечаем составные
    for (int num = start; num < finish; num++)                      // определяем список простых чисел (!составных)
    {
        // если число не отмечено составным -> проверяем число -> если число простое
        if (!comp_arr[num] && !is_composite(comp_arr, len_arr, num))
            note_composite(comp_arr, len_arr, num, start, finish);  // отмечаем составные числа, кратные простому
    }

    return 0;
}

bool is_composite(char comp_arr[], int len_arr, int num)
// функция принимает число и возвращает true - если число составное
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              len_arr             - длина массива
//              num                 - проверяемое число
// return:      true                - если число составное!
{
    if (more_limit("is_composite()", "num", num, "len_arr", len_arr)) // проверяем выход за пределы массива
        return false;

    int div_max = sqrt(num) + 1;                                            // выносим вычисление квадратного корня из цикла for

    for (int div = 2; div < div_max; div++)                                 // чтобы он не вычислялся каждую итерацию цикла
    {
        if (!comp_arr[div] && !(num % div))                                 // пропускаем составные делители и срабатываем при num % i == 0
            return true;
    }

    return false;
}

int note_composite(char comp_arr[], int len_arr, int prime, int start, int finish)
// функция отмечает составные числа в массиве
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              prime               - простое число, служит шагом
//              finish              - конечный индекс в массиве
// return:                          - количество отмеченных составных чисел
{
    if (more_limit("note_composite()", "prime", prime, "len_arr", len_arr))   // проверка на выход числа за пределы массива
        return 0;

    if (more_limit("note_composite()", "start", start, "len_arr", len_arr))
        return 0;

    if (more_limit("note_composite()", "finish", finish, "len_arr", len_arr))
        return 0;

    if (more_limit("note_composite()", "start", start, "finish", finish))
        return 0;

    start = (start > prime) ? start + (prime - start % prime) : 2 * prime;          // первое число - простое, не отмечаем его

    for (int i = start; i < finish; i += prime)
        comp_arr[i] = 1;                                                            // отмечаем составные числа

    return 0;
}

int count_primes(char comp_arr[], int *len_arr, int a, int b)
// функция, которая считает количество постых чисел подряд
// параметры:	comp_arr[]  - массив с ранее вычисленными составными числами
//              len_arr     - длина массива
//              a           - коэффициент в формуле (n * n) + (a * n) + b
//              b           - коэффициент
// return:                  - количество простых чисел подряд, вычисляемых формулой
{
    int cnt = 0;
    int answer = 1;
    int n = 0;

    while (answer > 0)                                                          // простое число не может быть отрицательным
    {
        answer = (n * n) + (a * n) + b;                                         // проверяем формулу

        if (answer >= *len_arr)                                                 // если ответ выходит за пределы массива
        {
            int past_len = *len_arr;                                            // сохраняем изначальную длину массива
            comp_arr = my_realloc(comp_arr, len_arr, answer - *len_arr + 1000); // увеличиваем массив (len_arr  увеличивается в функции!)
            note_prime_arr(comp_arr, *len_arr, past_len, *len_arr);              // отмечаем в добавленной части массива составные числа
        }

        if (answer < 0 || comp_arr[answer] == 1)                                // простое число не может быть отрицательным
            break;                                                              // прервем проверку формулы, если встретилось число не являющееся простым

        cnt++;
        n++;
    }

    return cnt;
}

bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
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
        printf("%s: %s = %d больше %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}

// #include <stdio.h>
// #include <stdbool.h>                                                //для красоты кода использую bool
// #include <math.h>                                                   //для использовании функции sqrt()
// #include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

// #define LEN_ARR 15000                                               //принял длину масиива опытным путем

// bool is_simple(int num_arg)
// //функция принимает число и возвращает true - если число простое
// {
//     int i_arg = sqrt(num_arg) + 1;                                  //выносим вычисление квадратного корня из цикла for

//     for (int i = 2; i < i_arg; i++)                                 //чтобы он не вычислялся каждую итерацию цикла
//     {
//         if (num_arg % i == 0)
//             return false;
//     }
//     return true;
// }
// int main(void)
// {
//     double time_spent = 0.0;                                // для хранения времени выполнения кода
//     clock_t begin = clock();                                // СТАРТ таймера
//     char arr[LEN_ARR] = {0};                                        //массив для записи простых чисел
//     int n, answ_a, answ_b, a, b, cnt, answ = 1, cnt_max = 0;

//     //вычисляю простые числа до 15000 один раз и заношу их массив по индексу
//     for (int i = 1; i < LEN_ARR; i++)                               //если arr[indx] = 1 => indx - простое число
//         arr[i] = is_simple(i);

//     //в цикле перебираю все возможные коэффициенты
//     for (a = -1000; a < 1000; a++)
//     {
//         for (b = -1000; b < 1000; b++)
//         {
//             cnt = 0;
//             n = 0;
//             for(n = 0; n < 100; n++)                                //предположил, что простых чисел будет не более ста
//             {
//                 answ = (n * n) + (a * n) + b;                       //проверяем формулу
//                 if (answ < 0 || arr[answ] == 0)                     //простое число не может быть отрицательным
//                     break;                                          //прервем проверку формулы если встретилось число не являющееся простым

//                 cnt++;
//             }

//             if (cnt > cnt_max)                                      //обновляем значения коэффициентов
//             {
//                 cnt_max = cnt;
//                 answ_a = a;
//                 answ_b = b;
//             }
//         }
//     }

//     // printf("cnt = %d\na*b = %d", cnt_max - 1, answ_a*answ_b);
//     clock_t end = clock();                                  // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

//     printf("Ответ = %d время = %f\n", answ_a*answ_b, time_spent);    // выводим результат и время работы программы
//     return 0;
// }