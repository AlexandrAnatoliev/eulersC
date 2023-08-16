//euler9c - Особая тройка Пифагора
//Тройка Пифагора - три натуральных числа a < b < c, для которых выполняется равенство a**2 + b**2 = c**2
//Например, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.
//Существует только одна тройка Пифагора, для которой a + b + c = 1000.
//Найдите произведение abc.

#include <stdio.h>
#include <stdbool.h>

bool is_triple(int *a_arg, int *b_arg, int *c_arg)
//true - если числа являются тройкой Пифагора
{
    return (*a_arg) * (*a_arg) + (*b_arg) * (*b_arg) == (*c_arg) * (*c_arg);
}

bool is_correct(int *a_arg, int *b_arg, int *c_arg)
//true - если числа являются Особой тройкой
{
    return *a_arg + *b_arg + *c_arg == 1000 && *a_arg < *b_arg && *b_arg < *c_arg;
}

int main(void)
{    
    int a, b, c, ab;
    for (c = 998; c > 0; c--)
    {
        ab = 1000 - c;
        for (b = ab; b > 0; b--)
        {
            a = ab - b;
            if(a>b)
                break;
            if (is_triple(&a, &b, &c) && is_correct(&a, &b, &c))
            {
                printf("a*b*c = %d",a*b*c);
                return 0;
            }
        }
    }
    return 0;  
}

