#include <stdio.h>

//euler2c - Четные числа Фибоначчи
//Каждый следующий элемент ряда Фибоначчи получается при сложении двух предыдущих. 
//Начиная с 1 и 2, первые 10 элементов будут: 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
//Найдите сумму всех четных элементов ряда Фибоначчи, которые не превышают четыре миллиона.

int main(void)
{
    int fib1 = 1;
    int fib2 = 2;
    int fib_next = 0;
    int evens_summ = 0;
    while (fib_next < 4000000)
    {
        fib_next = fib1 + fib2;
        fib1 = fib2;
        if (fib2%2 == 0) evens_summ = evens_summ + fib2;
        fib2 = fib_next;    
    }
    printf("%d",evens_summ);
    return 0;
}