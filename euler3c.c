#include <stdio.h>
#include <math.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{
    long long answer = 600851475143;

    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

                                                                // диапазон в котором изменяется делитель числа
    int div = 2;                                                // начало диапазона
    int sq_answ = sqrt(answer) + 1;                             // конец диапазона

    while(div < sq_answ)                                        // пока число делится
    {
        for(div = 2 ; div < sq_answ; div++)
            if( !(answer % div) )                               // если число делится нацело (answer % div == 0)
            {                                    
                answer /= div;                                  // уменьшаем число
                sq_answ = sqrt(answer) + 1;                     // обновляем диапазон
                break;   
            }
    } 
    
    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %lld runtime = %f\n", answer, time_spent); // выводим результат и время работы программы
    return 0;
}

