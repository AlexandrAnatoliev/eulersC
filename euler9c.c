//euler9c - Особая тройка Пифагора
//Тройка Пифагора - три натуральных числа a < b < c, для которых выполняется равенство a**2 + b**2 = c**2
//Например, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.
//Существует только одна тройка Пифагора, для которой a + b + c = 1000.
//Найдите произведение abc.

// #include <stdio.h>
// #include <stdbool.h>

// bool is_triple(int a, int b, int c)
// // Функция проверяет, являются ли числа тройкой Пифагора (a^2 + b^2 == c^2)
// // параметры:   a, b, c - проверяемые натуральные числа
// // return:      true    - если являются
// {
//     return (a * a) + (b * b) == c * c;
// }

// bool is_correct(int a, int b, int c)
// // Функция проверяет, являются ли числа Особой тройкой (a + b + c == 1000)
// // параметры:   a, b, c - проверяемые натуральные числа
// // return:      true    - если являются
// {
//     return a + b + c == 1000;
// }

// int main(void)
// {    
//     int a, b, c, a_and_b;                   // стороны треугольника и ab
//     for (c = 500; c > 0; c--)               // сторона с не может быть больше a+b, т.е. 1000/2
//     {
//         a_and_b = 1000 - c;                 // сумма сторон a+b+c = 1000
//         for (b = a_and_b - 1; b > 0; b--)   // перебираем варианты и - уменьшается
//         {
//             a = a_and_b - b;                // a - увеличивается
//             if(a > b)
//                 break;
//             if (is_triple(a, b, c) && is_correct(a, b, c))
//             {
//                 printf("a*b*c = %d",a*b*c);
//                 return 0;
//             }
//         }
//     }
//     return 0;  
// }

#include <stdio.h>
#include <stdbool.h>

bool is_triple(int sq[], int a, int b, int c)
// Функция проверяет, являются ли числа тройкой Пифагора (a^2 + b^2 == c^2)
// параметры:   sq[]    - указатель на массив с уже вычисленными квадратами чисел
//              a, b, c - проверяемые натуральные числа
// return:      true    - если являются
{
    return sq[a] + sq[b] == sq[c];
}

bool is_correct(int a, int b, int c)
// Функция проверяет, являются ли числа Особой тройкой (a + b + c == 1000)
// параметры:   a, b, c - проверяемые натуральные числа
// return:      true    - если являются
{
    return a + b + c == 1000;
}

int main(void)
{
    int arr_sq[1000] = {0};                 // чтобы не вычислять многократно одно и тоже
    for(int i = 1; i < 1000; i++)           // вычисляем квадраты натуральных чисел до 1000
        arr_sq[i] = i*i;                    // и сохраняем их в массив
    
    int a, b, c, a_and_b;                   // стороны треугольника и a+b

    for (c = 500; c > 0; c--)               // сторона с не может быть больше a+b, т.е. 1000/2
    {
        a_and_b = 1000 - c;                 // сумма сторон a+b+c = 1000
        for (b = a_and_b - 1; b > 0; b--)   // перебираем варианты: b - уменьшается
        {
            a = a_and_b - b;                // a - увеличивается

            if(a > b)                       // прерываем цикл, чтобы не повторяться
                break;

            if (is_triple(arr_sq, a, b, c) && is_correct(a, b, c))
            {
                printf("a*b*c = %d",a*b*c);
                return 0;                   // прерываем, если есть ответ
            }
        }
    }
 
    return 0;
}
