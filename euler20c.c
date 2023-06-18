// euler20c - Сумма цифр факториала

// n! означает n × (n − 1) × ... × 3 × 2 × 1

// Например, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
// и сумма цифр в числе 10! равна 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

// Найдите сумму цифр в числе 100!.

#include <stdio.h>

int main(void)
{
    int count = 0;
    int arr[200] = {1};
    int answ[200] = {};
    for(int j = 1; j <= 100; j++)
    {
        for(int i = 0; i < 190; i++)
        {
            int num = 0;
            int dec = 0;
            int hndr = 0;
            int int_num = 0;

            num = arr[i] * j;

            int_num = num%10 + answ[i]; 
            if(int_num >= 10)
            {
                answ[i + 1] += int_num/10;
                int_num = int_num%10;
            }      
            
            dec = num%100/10 + answ[i + 1];
            if(dec >= 10)
            {
                answ[i + 2] += dec/10;
                dec = dec%10;
            }

            hndr = num/100 + answ[i + 2];
            if(hndr >= 10)
            {
                answ[i + 3] += hndr/10;
                hndr = hndr%10;
            }

            answ[i] = int_num;
            answ[i + 1] = dec;
            answ[i + 2] = hndr;

            if(answ[i + 3] >= 10)
            {
                answ[i + 4] += answ[i + 3]/10;
                answ[i + 4] = answ[i + 4]%10;
            }

        }
        for(int i = 0; i < 200;i++)
        {
            arr[i] = answ[i];
            answ[i] = 0;
        }
        }
    for(int i = 0; i < 200; i++)
    {
        count +=arr[i];                                             //648
    }
    return 0;
}