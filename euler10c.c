//euler10c - Сложение простых чисел
//Сумма простых чисел меньше 10 равна 2 + 3 + 5 + 7 = 17.
//Найдите сумму всех простых чисел меньше двух миллионов.

#include <stdio.h>
#include <stdbool.h>

bool is_simple(int num_arg)
{
    int i_arg = sqrt(num_arg) + 1;
    for (int i = 2; i < i_arg; i++)
    {
        if (num_arg%i == 0) return false;
    }
    return true;
}

int main(void)
{    
    int answ = 0;                       //1179908154
    int num = 0;
    for (int i = 2; i < 2000000; i++)
    {
        if (is_simple(i)) num += i;
    }    
    return 0;  
}

