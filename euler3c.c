#include <stdio.h>
#include<math.h>

//euler3c - Наибольший простой делитель
//Простые делители числа 13195 - это 5, 7, 13 и 29.
//Каков самый большой делитель числа 600851475143, являющийся простым числом?

int isSimple(long long num_arg)
//если число простое, то возвращает 1, иначе - 0
{
    //проскольку число А можно предствить как квадрат a^2, множители можно проверять до а
    int n = round(sqrt(num_arg) + 1);       
    for (int i = 2; i < n; i++)
    {
        if (num_arg%i == 0) return 0;
    }        
    return 1;
}

long long getMaxDiv(long long num_arg)
//возвращает максимальный делитель числа
{
    int j = 2;
    while (num_arg%j != 0) j++;
    long long answer = round(num_arg/j);
    return answer;
}

int main(void)
{
    int res;
    long long answer = 600851475143;

    answer = getMaxDiv(answer);
    res = isSimple(answer);
    while (res == 0)
    {
         answer = getMaxDiv(answer);
         res = isSimple(answer);         
    }      
    printf("%lld\n", answer);
    return 0;
}

