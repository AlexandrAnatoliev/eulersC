// euler21c - Дружественные числа

// Пусть d(n) определяется как сумма делителей n (числа меньше n, делящие n нацело).
// Если d(a) = b и d(b) = a, где a ≠ b, то a и b называются дружественной парой, 
// а каждое из чисел a и b - дружественным числом.

// Например, делителями числа 220 являются 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 и 110, поэтому d(220) = 284. 
// Делители 284 - 1, 2, 4, 71, 142, поэтому d(284) = 220.

// Подсчитайте сумму всех дружественных чисел меньше 10000.

#include <stdio.h>
#include <math.h>

int main(void)
{
    int div_arr[100] = {0};                             //массив для делителей числа
    int div_cnt = 0;                 
    int sum_div = 0;                        
    int fr_num;                                         //дружественное число
    int sum_fr_num = 0;                                 //сумма всех дружественных чисел                  

    for(int num = 1; num < 10000; num++)                //перебираем числа
    {
        for(int i = 1; i < (int)sqrt(num) + 1; i++)
        //определяем делители числа
        {
            if(num%i == 0)
            {
                if(i == 1)
                    div_arr[div_cnt++] = i;
                else if(i != num/i)
                {
                    div_arr[div_cnt++] = i;             //добавляем меньший делитель числа 
                    div_arr[div_cnt++] = num/i;         //добавляем больший делитель числа
                }
            }
        }         

        for(int i = 0; i < div_cnt; i++)
        {
            sum_div += div_arr[i];                      //сумма делителей числа
            div_arr[i] = 0;                             //обнуляем массив
        }    
        
        div_cnt = 0;                                    //обнуляем счетчик массива
        fr_num = sum_div;                               //дружественное число?
        sum_div = 0;
        for(int i = 1; i < (int)sqrt(fr_num) + 1; i++)  //проверяем на дружественность
        {
            if(fr_num%i == 0)
            {
                if(i == 1)
                    div_arr[div_cnt++] = i;
                else if(i != fr_num/i)
                {
                    div_arr[div_cnt++] = i;             //добавляем меньший делитель числа 
                    div_arr[div_cnt++] = fr_num/i;      //добавляем больший делитель числа
                }
            }
        }

        for(int i = 0; i <= div_cnt; i++)
        {
            sum_div += div_arr[i];                      //сумма делителей числа
            div_arr[i] = 0;
        }    

        if(sum_div == num && num != fr_num)             //если d(a) = b и d(b) = a, где a ≠ b     
            sum_fr_num += (num + fr_num);      

        div_cnt = 0;
        sum_div = 0;
    }    
    printf("%d",sum_fr_num/2);                          //31626
    return 0;
}