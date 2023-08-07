//euler5c - Наименьшее кратное
//2520 - самое маленькое число, которое делится без остатка на все числа от 1 до 10.
//Какое самое маленькое число делится нацело на все числа от 1 до 20?

#include <stdio.h>
#include <stdbool.h>

bool isDiv(int num_arg)
//если число делится без остатка на весь ряд чисел, то возвращает 1, иначе - 0
{
    for (int i = 2; i < 20; i++)
    {
        if (num_arg%i != 0) 
            return false;
    }
    return true;
}

int main(void)
{
    int num = 10;
    while (isDiv(num) == false) 
        num++;
    printf("%d",num);
    return 0;  
}

