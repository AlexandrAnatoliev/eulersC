//euler4c - Наибольшее произведение-палиндром
//Число-палиндром с обеих сторон (справа налево и слева направо) читается одинаково. 
//Самое большое число-палиндром, полученное умножением двух двузначных чисел – 9009 = 91 × 99.
//Найдите самый большой палиндром, полученный умножением двух трехзначных чисел.

#include <stdio.h>
#include <stdbool.h>

bool isPolinom(int num_arg)
//если число полином, то возвращает true, иначе - false
{
    //выделяем отдельные цифры из числа 123456
    char num6 = num_arg/100000;          //1
    char num5 = num_arg%100000/10000;    //2
    char num4 = num_arg%10000/1000;      //3...
    char num3 = num_arg%1000/100;
    char num2 = num_arg%100/10;
    char num1 = num_arg%10;

    if (num6 != 0)                      //если число - шестизначное
    {
        if (num6 != num1 || num5 != num2 || num4 != num3) 
            return false;
        return true;
    }
    else if (num5 != 0)                 //если число - пятизначное
    {
        if (num5 != num1 || num4 != num2) 
            return false;        
        return true;
;
    }
    else if (num4 != 0)                 //если число - четырехзначное
    {
        if (num4 != num1 || num3 != num2) 
            return false;
        return true;
    }
    else if (num3 != 0)                 //если число - трехзначное
    {
        if (num3 != num1) 
            return false;
        return true;
    }
    else if (num2 != 0)                 //если число - двузначное
    {
        if (num2 != num1) 
            return false;
        return true;
    }
    else 
        return false;
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
            //если произведение чисел меньше уже полученного ответа - то и дальше будет меньше
            if(answ > num)
                break;                       
            if (isPolinom(num))                 //находим полином
            {
                answ = num;                     //сохраняем если он максимален 
                break;                          //пропускаем цикл т.к последующие числа заведомо меньше
            }
        }
    }
    printf("%d",answ);                          //906609
    return 0;
}

