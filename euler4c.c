// euler4c - Наибольшее произведение-палиндром

// Число-палиндром с обеих сторон (справа налево и слева направо) читается одинаково. 
// Самое большое число-палиндром, полученное умножением двух двузначных чисел – 9009 = 91 × 99.
// Найдите самый большой палиндром, полученный умножением двух трехзначных чисел.

// вариант для сайта
#include <stdio.h>
#include <stdbool.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

text_t is_palindrom(int num)
// функция определяет, является ли число палиндромом
// параметры:	num     - проверяемое число
// return:      true    - число является палиндромом
{
    int check_num = num;
    int revers_num = 0;                                     // chec_num = 123 -> 321 = revers_num
    
    while (check_num)                                       // пока число не уменьшится до нуля
    {   
        revers_num *= 10;                                   // увеличиваем регистр цифр обратного числа
        revers_num += check_num % 10;                       // прибавляем к обратному числу младший регистр проверяемого числа
        check_num /= 10;                                    // обрезаем младший регистр
    }
    
    return revers_num == num;
}

int main(void)
{
    int answ = 0;
    int num;

    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    for (int i = 999; i > 99; i--)                          // перебираем множители от большего к меньшему
    {
        for (int j = 990; j > 99; j -= 11)                  // все палиндромы с четным количеством цифр делятся на 11!
        {
            num = i*j;
            // если произведение чисел меньше уже полученного ответа - то и дальше будет меньше
            if(answ > num)
                break;                       
            if (is_palindrom(num))                          // находим палиндром
            {
                answ = num;                                 // сохраняем если он максимален 
                break;                                      // пропускаем цикл т.к последующие числа заведомо меньше
            }
        }
    }

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("answer = %d runtime = %f\n", answ, time_spent); // выводим результат и время работы программы                         
    return 0;
}
