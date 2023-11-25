#include <stdio.h>
#include <math.h>

int main(void)
{
    long long answer = 600851475143;

    // диапазон в котором изменяется делитель числа
    int div = 2;                                // начало диапазона
    int sq_answ = sqrt(answer) + 1;             // конец диапазона

    while(div < sq_answ)                        // пока число делится
    {
        for(div = 2 ; div < sq_answ; div++)
            if( !(answer % div) )               // если число делится нацело (answer % div == 0)
            {                                    
                answer /= div;                  // уменьшаем число
                sq_answ = sqrt(answer) + 1;     // обновляем диапазон
                break;   
            }
    } 
    printf("%lld", answer);                     // 6857
    return 0;
}

