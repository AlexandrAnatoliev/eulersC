// euler15c - Пути через таблицу

// Начиная в левом верхнем углу сетки 2×2 и имея возможность двигаться только вниз или вправо, 
// существует ровно 6 маршрутов до правого нижнего угла сетки.

// Сколько существует таких маршрутов в сетке 20×20?

#include <stdio.h>

unsigned long long prev[21] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned long long next[21] = {0};
unsigned long long num;

int main(void)
{

    for (int j=0; j<20; j++)
    {
        for (int i=1; i<21; i++)
        {
            num = prev[i] + next[i-1];
            next[i] = num;
        }
        for (int i=0; i<21; i++)
        {
            prev[i] = next[i];
        }
    }
    unsigned long long answ = prev[20];                 //35345263800
 
    return 0;
}