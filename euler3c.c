#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//euler3c - Наибольший простой делитель
//Простые делители числа 13195 - это 5, 7, 13 и 29.
//Каков самый большой делитель числа 600851475143, являющийся простым числом?

bool isSimple(long long num_arg)
//если число простое, то возвращает true, иначе - false
{
    //поскольку число N можно предствить как квадрат n^2, множители можно проверять до n
    int n = round(sqrt(num_arg) + 1);       
    for (int i = 2; i < n; i++)
    {
        if (num_arg%i == 0) 
            return false;
    }        
    return true;
}

long long getMaxDiv(long long num_arg)
//возвращает максимальный делитель числа
{
    int j = 2;
    while (num_arg%j != 0) 
        j++;
    long long answer = num_arg/j;
    return answer;
}

int main(void)
{
    long long answer = 600851475143;

    answer = getMaxDiv(answer);    
    while (isSimple(answer) == false)
    {
         answer = getMaxDiv(answer);                 
    }      
    printf("%lld\n", answer);
    return 0;
}

