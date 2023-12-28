// euler48c - Собственные степени

// Сумма 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

// Найдите последние десять цифр суммы 1^1 + 2^2 + 3^3 + ... + 1000^1000

#include <stdio.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

long long get_self_power(long long num)
// функция принимает число и возводит его в собственную степень
// параметры:	num         - проверяемое число                
// return:      последние 10 цифр num^num
{
    long long last_ten_digits = num;
    long long degree = num;                                 // степень числа

    while(last_ten_digits && degree > 1)                    // пока существует число 
    {
        last_ten_digits *= num;                             // возводим его в степень
        last_ten_digits %= 10000000000;                     // и выделяем из него младшие 10 разрядов
        degree--;
    }

	return last_ten_digits;                                 // последние 10 цифр числа в собственной степени
}

int main(void)
{
    long long answ = 0;
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    
    clock_t begin = clock();                                // СТАРТ таймера

    for(long long num = 1; num < 1001; num++)
        answ += get_self_power(num);                        // складываем последние 10 цифр чисел

    answ %= 10000000000;                                    // еще раз выделяем 10 цифр - уже из результата

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах
    
    printf("answer = %lld   runtime = %f\n", answ, time_spent);
	return 0;	
}
