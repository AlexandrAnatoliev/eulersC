// euler15c - Пути через таблицу

// Начиная в левом верхнем углу сетки 2×2 и имея возможность двигаться только вниз или вправо, 
// существует ровно 6 маршрутов до правого нижнего угла сетки.

// Сколько существует таких маршрутов в сетке 20×20?

#include <stdio.h>

int main(void)
{
    unsigned long long prev[22] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    unsigned long long next[22] = {0};
    unsigned long long num;

    for (int row = 1; row < 21; row++)
    {
        //считаем количество маршрутов до каждой ячейки в сетке
        for (int column = 1; column < 22; column++)        
        {
            num = prev[column] + next[column-1];
            next[column] = num;
        }
        //обновляем состояние предыдущего ряда
        for (int column = 0; column < 22; column++)
        {
            prev[column] = next[column];
        }
    }
    unsigned long long answ = prev[21];                 //137846528820
    printf("%llu",answ);
    return 0;
}