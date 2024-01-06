// euler12c - Треугольное число с большим количеством делителей
// Последовательность треугольных чисел образуется путем сложения натуральных чисел. 
// К примеру, 7-е треугольное число равно 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. 
// Первые десять треугольных чисел: 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// Перечислим делители первых семи треугольных чисел:
// 1: 1
// 3: 1, 3
// 6: 1, 2, 3, 6
// 10: 1, 2, 5, 10
// 15: 1, 3, 5, 15
// 21: 1, 3, 7, 21
// 28: 1, 2, 4, 7, 14, 28
// Как мы видим, 28 - первое треугольное число, у которого более пяти делителей.
// Каково первое треугольное число, у которого более пятисот делителей?

// первый вариант для дзена

// #include <stdio.h>
// #include <math.h>

// int main(void)
// {
//     long triple_number = 0;                                  
//     int max_cnt = 0;                                        
//     for (int i = 1; i < 12376; i++)                         
//     {
//         triple_number += i;
//         int cnt = 0;
//         for (int j = 1; j < sqrt(triple_number) + 1; j++)
//         {
//             if (triple_number % j  == 0) 
//                 cnt += 2;                                   //получаем сразу два делителя (максимальный и минимальный)
//         }
//         if (max_cnt < cnt) 
//             max_cnt = cnt;
//         if (max_cnt > 500)
//         {       
//             printf("%ld",triple_number);
//             return 0;
//         }            
//     }    
//     return 0;
// }

// первый вариант с замером времени работы

// #include <stdio.h>
// #include <math.h>
// #include <time.h>                                                               // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
//     double time_spent = 0.0;                                                    // для хранения времени выполнения кода
//     clock_t begin = clock();                                                    // СТАРТ таймера

//     long triple_number = 0;                                                     
//     int max_cnt = 0;                                                            
//     for (int i = 1; i < 12376; i++)                                             
//     {
//         triple_number += i;
//         int cnt = 0;
//         for (int j = 1; j < sqrt(triple_number) + 1; j++)
//         {
//             if (triple_number % j  == 0) 
//                 cnt += 2;                                                       //получаем сразу два делителя (максимальный и минимальный)
//         }
//         if (max_cnt < cnt) 
//             max_cnt = cnt;
//         if (max_cnt > 500)
//         {       
//             clock_t end = clock();                                              // СТОП таймера
//             time_spent += (double)(end - begin) / CLOCKS_PER_SEC;               // время работы в секундах

//             printf("answer = %d runtime = %f\n", triple_number, time_spent);    // выводим результат и время работы программы
//             return 0;
//         }            
//     }    
//     return 0;
// }


// вариант для сайта
#include <stdio.h>
#include <math.h>                                                       // для работы функции sqrt()
#include <time.h>                                                       // для clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{
    double time_spent = 0.0;                                            // для хранения времени выполнения кода
    clock_t begin = clock();                                            // СТАРТ таймера

    int triple = 0;
    int num = 0;                                                     
    int cnt_div = 0;
                                                                   
    while(cnt_div < 500)                                         
    {
        num++;                                                          // перебираем натуральные числа
        triple += num;                                                  // получаем очередное треугольное число
        cnt_div = 0;                                                    // обнуляем счетчик делителей

        int max_div = sqrt(triple) + 1;                                 // выносим sqrt() перед циклом for, чтобы вычислялось только один раз
        for (int div = 1; div < max_div; div++)
        {
            if (triple % div  == 0)                                     // triple/div - максимальный делитель и div - минимальный
                if(triple / div == div)                                 // если максимальный и минимальный делитель равны
                    cnt_div++;                                          // получаем один делитель
                else
                    cnt_div += 2;                                       // получаем сразу два делителя (максимальный и минимальный)
        }

        if (cnt_div > 500)
        {       
            clock_t end = clock();                                      // СТОП таймера
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

            printf("answer = %d runtime = %f\n", triple, time_spent);   // результат и время работы программы
        }            
    }
        
    return 0;
}