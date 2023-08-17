//euler10c - Сложение простых чисел
//Сумма простых чисел меньше 10 равна 2 + 3 + 5 + 7 = 17.
//Найдите сумму всех простых чисел меньше двух миллионов.

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_simple(int *num_arg)
//true - если число простое
{
    int i_arg = sqrt(*num_arg) + 1;
    
    for (int i = 2; i < i_arg; i++)
    {
        if (*num_arg%i == 0) 
            return false;
    }
    return true;
}

int main(void)
{    
    long long answ = 0;                      
    for (int i = 2; i < 2000000; i++)
    {
        if (is_simple(&i)) 
            answ += i;
    }  
    printf("%lld",answ);                     //142913828922
    return 0;  
}

