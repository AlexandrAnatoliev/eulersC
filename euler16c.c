// euler16c - Сумма цифр степени

// 2^15 = 32768, сумма цифр этого числа равна 3 + 2 + 7 + 6 + 8 = 26.
// Какова сумма цифр числа 2^1000?

#include <stdio.h>


int main(void)
{
    int count = 1;
    int num = 0;
    int dex_num = 0;
    int arr[304] = {2};
    int answ[306] = {};
    int sum_num = 0;

    while (count < 1000)
    {
        for (int i = 0; i < 304; i++)
        {
            num = arr[i];
            num *= 2;
            dex_num = num/10;
            answ[i+1] += dex_num;
            num = num%10;
            answ[i] += num;               
        }
        for (int i = 0; i < 304; i++)
        {
            arr[i] = answ[i];
            answ[i] = 0;
        }
    count++;   
    } 
    for (int i = 0; i < 304; i++)
    {
        sum_num += arr[i];                              //1366
    }  
    return 0;
}