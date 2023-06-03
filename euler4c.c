//euler4c - Наибольшее произведение-палиндром
//Число-палиндром с обеих сторон (справа налево и слева направо) читается одинаково. 
//Самое большое число-палиндром, полученное умножением двух двузначных чисел – 9009 = 91 × 99.
//Найдите самый большой палиндром, полученный умножением двух трехзначных чисел.

#include <stdio.h>

int isPolinom(int num_arg)
//если число полином, то возвращает 1, иначе - 0
{
    //выделяем отдельные цифры из числа 123456
    int num6 = num_arg/100000;          //1
    int num5 = num_arg%100000/10000;    //2
    int num4 = num_arg%10000/1000;      //3...
    int num3 = num_arg%1000/100;
    int num2 = num_arg%100/10;
    int num1 = num_arg%10;

    if (num6 != 0)
    {
        if (num6 != num1 || num5 != num2 || num4 != num3) return 0;
        return 1;
    }
    else if (num5 != 0)
    {
        if (num5 != num1 || num4 != num2) return 0;        
        return 1;
    }
    else if (num4 != 0)
    {
        if (num4 != num1 || num3 != num2) return 0;
        return 1;
    }
    else if (num3 != 0)
    {
        if (num3 != num1) return 0;
        return 1;
    }
    else if (num2 != 0)
    {
        if (num2 != num1) return 0;
        return 1;
    }
    else return 0;
}

int main(void)
{
    int answ = 0;
    int num;    
    for (int i = 999; i > 99; i--)              //перебираем множители от большего к меньшему
    {
        for (int j = 999; j > 99; j--)
        {
            num = i*j;
            if (isPolinom(num) == 1)            //находим полином
            {
                if (answ < num) answ = num;     //сохраняем если он максимален 
                continue;                       //пропускаем цикл т.к последующие числа заведомо меньше
            }
        }
    }
    return answ;
}

