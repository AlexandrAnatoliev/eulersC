// euler21c - Дружественные числа

// Пусть d(n) определяется как сумма делителей n (числа меньше n, делящие n нацело).
// Если d(a) = b и d(b) = a, где a ≠ b, то a и b называются дружественной парой, 
// а каждое из чисел a и b - дружественным числом.

// Например, делителями числа 220 являются 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 и 110, поэтому d(220) = 284. 
// Делители 284 - 1, 2, 4, 71, 142, поэтому d(284) = 220.

// Подсчитайте сумму всех дружественных чисел меньше 10000.

#include <stdio.h>

int main(void)
{
    int div_arr[100] = {};
    int div_cnt = 0;
    int num = 220;
    int sum_div = 0;
    int fr_num;
    int sum_fr_num = 0;                                         //80568

    for(int j = 1; j < 10000; j ++)
    {
        num = j;
        for(int i = 1; i < num; i++)
        {
            if(num%i == 0)
            {
                div_arr[div_cnt] = i;
                div_cnt++;
            }
        }

        for(int i = 0; i <= div_cnt; i++)
        {
            sum_div += div_arr[i];
            div_arr[i] = 0;
        }    
        
        div_cnt = 0;
        fr_num = sum_div;
        sum_div = 0;
        for(int i = 1; i < fr_num; i++)
        {
            if(fr_num%i == 0)
            {
                div_arr[div_cnt] = i;
                div_cnt++;
            }
        }

        for(int i = 0; i <= div_cnt; i++)
        {
            sum_div += div_arr[i];
            div_arr[i] = 0;
        }    

        if(sum_div == num)
            sum_fr_num = sum_fr_num + num + fr_num;

        div_cnt = 0;
        sum_div = 0;
    }    
    
    return 0;
}