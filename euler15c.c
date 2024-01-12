// euler15c - Пути через таблицу

// Начиная в левом верхнем углу сетки 2×2 и имея возможность двигаться только вниз или вправо,
// существует ровно 6 маршрутов до правого нижнего угла сетки.

// Сколько существует таких маршрутов в сетке 20×20?

// #include <stdio.h>

// int main(void)
// {
//     unsigned long long prev[22] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//     unsigned long long next[22] = {0};
//     unsigned long long num;

//     for (int row = 1; row < 21; row++)
//     {
//         //считаем количество маршрутов до каждой ячейки в сетке
//         for (int column = 1; column < 22; column++)
//         {
//             num = prev[column] + next[column-1];
//             next[column] = num;
//         }
//         //обновляем состояние предыдущего ряда
//         for (int column = 0; column < 22; column++)
//         {
//             prev[column] = next[column];
//         }
//     }
//     unsigned long long answ = prev[21];                 
//     printf("%llu",answ);
//     return 0;
// }

#include <stdio.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    long long answ;
    long long knot_row[22] = {0};
    knot_row[1] = 1;                                            // только один способ добраться в начальный узел

    for (int row = 1; row < 22; row++)
        for (int column = 1; column < 22; column++)
            knot_row[column] += knot_row[column - 1];           // считаем количество маршрутов до каждого узла в сетке

    answ = knot_row[21];                                        // правый нижний угол

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %lld runtime = %f\n", answ, time_spent);   // выводим результат и время работы программы
    return 0;
}