//euler7c - 10001-е простое число
//Выписав первые шесть простых чисел, получим 2, 3, 5, 7, 11 и 13. Очевидно, что 6-е простое число - 13.
//Какое число является 10001-м простым числом?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isSimpleNum(int num_arg)
{
    int num = sqrt(num_arg) + 1;    //не нужно доходить до числа A A=a*a. Достаточно дойти до a
    for (int i = 2; i < num; i++) 
    {        
        if (num_arg % i == 0) 
            return false;           //% может работать только с целочисленными значениями
    }
    return true;
}

int main(void)
{
    int count = 0;                  
    int answ = 0;                   //104743
    int num = 1;
    while (count < 10001)    
    {
        num++;
        if (isSimpleNum(num))
        {
            answ = num;
            count++;
        }
    }
    printf("%d",answ);
    return 0;  
}

