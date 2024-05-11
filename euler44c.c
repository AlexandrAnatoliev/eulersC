// euler44c - Пятиугольные числа

// Пятиугольные числа вычисляются по формуле: Pn=n(3n−1)/2. Первые десять пятиугольных чисел:

// 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

// Можно убедиться в том, что P4 + P7 = 22 + 70 = 92 = P8.
// Однако, их разность, 70 − 22 = 48, не является пятиугольным числом.

// Найдите пару пятиугольных чисел Pj и Pk, для которых сумма и разность являются пятиугольными числами
// и значение D = |Pk − Pj| минимально, и дайте значение D в качестве ответа.// 5482660

// euler44c - Пятиугольные числа

// Пятиугольные числа вычисляются по формуле: Pn=n(3n−1)/2. Первые десять пятиугольных чисел:

// 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

// Можно убедиться в том, что P4 + P7 = 22 + 70 = 92 = P8.
// Однако, их разность, 70 − 22 = 48, не является пятиугольным числом.

// Найдите пару пятиугольных чисел Pj и Pk, для которых сумма и разность являются пятиугольными числами
// и значение D = |Pk − Pj| минимально, и дайте значение D в качестве ответа.// 5482660

#include <stdio.h>
#include <stdbool.h>
#include <time.h>                   // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>                 // русский язык в printf()
#include <stdlib.h>

typedef struct pentagonal_numbers   // структура "пятиугольные числа"
{
    char *is_pent;                  // is_pent[12] = 1, число 5 - пятиугольное
    int len_pent;                   // длина массива is_pent[]
    int *arr;                       // массив цифр числа [1,5,12...]
    int len_arr;                    // количество цифр в массиве arr[]
} pen_t;

pen_t pent_init_malloc(int nums);

int main(void)
{
    setlocale(LC_ALL, "Rus");                                   // русский язык в printf()

    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    int answ = 0;
    int nums = 2500;
    int past_nums = 1;
    pen_t pent;

    while (answ == 0)
    {
        pent = pent_init_malloc(nums);                          // вычисляем ряд пятиугольных чисел

        for (int k = past_nums / 2; k < nums / 2; k++)          // проверяем числа на отрезке
        {
            for (int j = 0; j < k; j++)
            {
                if (pent.is_pent[pent.arr[k] - pent.arr[j]] &&  // разность пятиугольных чисел - пятиугольное число
                    pent.is_pent[pent.arr[k] + pent.arr[j]])    // и и сумма тоже
                {
                    answ = pent.arr[k] - pent.arr[j];           // первые встреченные числа - минимальны и являются ответом
                    break;
                }
            }
        }

        past_nums = nums;                                       // значения нового отрезка чисел
        nums *= 2;

        free(pent.is_pent);                                     // освобождаем память из под обоих массивов
        free(pent.arr);
    }

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("Ответ = %d время = %f\n", answ, time_spent);        // выводим результат и время работы программы

    return 0;
}

pen_t pent_init_malloc(int nums)
// Функция для вычисления ряда пятиугольных чисел
// Выделяет память под массивы! Требуется после освобождать!
// Параметры:   nums    - количество пятиугольных чисел
// return:              - структуру с указателями на ряд пятиугольных чисел
{
    pen_t pentag;

    pentag.len_arr = nums;
    pentag.arr = malloc(nums * sizeof(int));                // выделяем место под массив
    pentag.len_pent = nums * ((3 * nums) - 1) / 2 + 1;      // вычисляем последнее число
    pentag.is_pent = calloc(pentag.len_pent, sizeof(char)); // массив под флаги заполняем нулями

    for (int i = 0, num = 1, step = 4; i < pentag.len_arr; i++)

    {
        pentag.arr[i] = num;                                // заполняем массив пятиугольными числами по порядку
        pentag.is_pent[num] = 1;                            // и отмечаем их флаги
        num += step;                                        // 1, 5, 12, 22, 35... => step = 4 += 3
        step += 3;
    }

    return pentag;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC

// int get_pentagon(int num)
// // функция возвращает значение пятиугольного числа по его номеру
// // параметры:	num - номер пятиугольного числа
// // return:          - значение пятиугольного числа -> Pn=n(3n−1)/2
// {
//     return (num * (3 * num - 1)) / 2;
// }

// bool is_answer(char arr[], int pent1, int pent2)
// // функция проверяет выполнение условий задачи
// // параметры:	arr[]   - массив для хранения пятиугольных чисел по индексу
// //              pent1   - пятиугольное число 1
// //              pent2   - пятиугольное число 2 > пятиугольного числа 2!
// // return:              - true - удовлетворяет условиям задачи
// {
//     return arr[pent2 + pent1] && arr[pent2 - pent1];
// }

// int main(void)
// {
//     double time_spent = 0.0;                    // для хранения времени выполнения кода
//     clock_t begin = clock();                    // СТАРТ таймера

//     static char pent_arr_indx[40000000] = { 0 };    // массив для хранения пятиугольных чисел по индексу
//     static int pent_arr[5000] = { 0 };              // массив для хранения значений пятиугольных чисел
//     int pent = 0;                                   // пятиугольное число
//     int answ = 10000000;

//     for (int i = 1; i < 5000; i++)                  // вычисляем первые 5000 пятиугольных чисел
//     {
//         pent = get_pentagon(i);
//         pent_arr[i] = pent;                         // заполняем массив со значениями пятиугольных чисел
//         pent_arr_indx[pent] = 1;                    // заполняем массив индексов пятиугольных чисел
//     }

//     for(int p2 = 2499; p2 > 1; p2--)                // перебираем номера пятиугольных чисел
//     {
//         for(int p1 = p2 - 1; p1 > 0; p1--)
//         {
//             int pent1 = pent_arr[p1];               // значения пятиугольных чисел
//             int pent2 = pent_arr[p2];
//             if(is_answer(pent_arr_indx, pent1, pent2))
//                 answ = (answ < (pent2 - pent1)) ? answ : (pent2 - pent1);
//         }
//     }

//     clock_t end = clock();                                  // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

//     printf("Ответ = %d время = %f\n", answ, time_spent);  // выводим результат и время работы программы
//     return 0;
// }
