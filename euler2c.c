//euler2c - Четные числа Фибоначчи
//Каждый следующий элемент ряда Фибоначчи получается при сложении двух предыдущих. 
//Начиная с 1 и 2, первые 10 элементов будут: 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
//Найдите сумму всех четных элементов ряда Фибоначчи, которые не превышают четыре миллиона.

// обычный вариант

#include <stdio.h>
#include <time.h>                                                   // for clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{
    int fib1 = 1;                           
    int fib2 = 2;
    int fib_next = 0;
    int evens_summ = 0;

    double time_spent = 0.0;                                        // для хранения времени выполнения кода
    clock_t begin = clock();                                        // СТАРТ таймера

    while (fib_next < 4000000)
    {
        fib_next = fib1 + fib2;                                     // следующее число Фибоначчи - сумма двух предыдущих
        fib1 = fib2;
        if ( !(fib2 % 2) )                                          // fib2%2 == 0
            evens_summ += fib2;
        fib2 = fib_next;    
    }
    
    clock_t end = clock();                                          // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;           // время работы в секундах

    printf("answer = %d runtime = %f\n", evens_summ, time_spent);   // выводим результат и время работы программы

    return 0;
}

// используем битовое сложение

// #include <stdio.h>
// #include <time.h>                                                   // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
//     int fib1 = 1;                           
//     int fib2 = 2;
//     int fib_next = 0;
//     int evens_summ = 0;

//     double time_spent = 0.0;                                        // для хранения времени выполнения кода
//     clock_t begin = clock();                                        // СТАРТ таймера

//     while (fib_next < 4000000)
//     {
//         fib_next = fib1 + fib2;                                     // следующее число Фибоначчи - сумма двух предыдущих
//         fib1 = fib2;
//         if ( !(fib2 & 1) )                                          // fib2%2 == 0
//             evens_summ += fib2;
//         fib2 = fib_next;    
//     }
    
//     clock_t end = clock();                                          // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;           // время работы в секундах

//     printf("answer = %d runtime = %f\n", evens_summ, time_spent);   // выводим результат и время работы программы

//     return 0;
// }