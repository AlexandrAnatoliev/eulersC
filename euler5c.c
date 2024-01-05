// euler5c - Наименьшее кратное

// 2520 - самое маленькое число, которое делится без остатка на все числа от 1 до 10.
// Какое самое маленькое число делится нацело на все числа от 1 до 20?

// вариант для сайта
#include <stdio.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

long long get_NOD(long long num1, long long num2)
// функция определяющая наибольший общий делитель двух чисел
// параметры:	num1    - число 1
//              num2    - число 2    
// return:      наибольший общий делитель двух чисел
{
    while(num1 && num2)                                         // пока ни одно из чисел не равно нулю
    {
        if(num1 >= num2)
            num1 %= num2;
        else
            num2 %= num1;
    }
    return (num1 > num2) ? num1 : num2;                         // возвращает максимальное
}

long long get_NOD2(long long num1, long long num2)
// функция определяющая наибольший общий делитель двух чисел рекурсивно
// параметры:	num1    - число 1
//              num2    - число 2    
// return:      наибольший общий делитель двух чисел
{
    if(!num1 || !num2)                                          // если одно из чисел равно нулю 
        return (num1 > num2) ? num1 : num2;                     // возвращаем максимальное
    return get_NOD(num2 % num1, num1);
}

long long get_NOK(long long num1, long long num2)
// функция определяющая наибольшее общее кратное двух чисел
// параметры:	num1    - число 1
//              num2    - число 2    
// return:      наибольшее общее кратное двух чисел
{
    return num1 * num2 / get_NOD(num1, num2);
}

int main(void)
{
    long long answ = 1;

    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    for(int i = 2; i <= 20; i++)
        answ = get_NOK(answ, i);

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %lld runtime = %f\n", answ, time_spent);   // выводим результат и время работы программы                    
    return 0;
}



