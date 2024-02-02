// euler20c - Сумма цифр факториала

// n! означает n × (n − 1) × ... × 3 × 2 × 1

// Например, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
// и сумма цифр в числе 10! равна 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

// Найдите сумму цифр в числе 100!.

// #include <stdio.h>

// int main(void)
// {
//     int count = 0;
//     int arr[200] = {1};                         //число до умножения
//     int answ[200] = {};                         //число после умножения
//     for(int j = 1; j <= 100; j++)
//     {
//         for(int i = 0; i < 190; i++)
//         {
//             int num = 0;
//             int dec = 0;
//             int hndr = 0;
//             int int_num = 0;

//             num = arr[i] * j;                   //умножаю каждую цифру числа

//             int_num = num%10 + answ[i];         //отделяю единицы
//             if(int_num >= 10)
//             {
//                 answ[i + 1] += int_num/10;
//                 int_num = int_num%10;
//             }

//             dec = num%100/10 + answ[i + 1];     //отделяю десятки
//             if(dec >= 10)
//             {
//                 answ[i + 2] += dec/10;
//                 dec = dec%10;
//             }

//             hndr = num/100 + answ[i + 2];       //отделяю сотни
//             if(hndr >= 10)
//             {
//                 answ[i + 3] += hndr/10;
//                 hndr = hndr%10;
//             }

//             answ[i] = int_num;
//             answ[i + 1] = dec;
//             answ[i + 2] = hndr;

//             if(answ[i + 3] >= 10)               //отделяю тысячи
//             {
//                 answ[i + 4] += answ[i + 3]/10;
//                 answ[i + 4] = answ[i + 4]%10;
//             }

//         }
//         for(int i = 0; i < 200;i++)
//         //обновляю факторивл
//         {
//             arr[i] = answ[i];
//             answ[i] = 0;
//         }
//         }
//     for(int i = 0; i < 200; i++)
//     {
//         count +=arr[i];
//     }
//     printf("%d",count);
//     return 0;
// }

#include <stdio.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 200

int multiply(int num_ar1[], int num2);
int get_sum_dig(int num_ar1[]);

int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    int num_arr[LEN_ARR] = {1, 1};                          // массив для хранения цифр числа

    for (int num = 2; num <= 100; num++)
        multiply(num_arr, num);                             // перемножаем числа 1 * 2 * 3 * ... * 100 и получаем 100!

    int answ = get_sum_dig(num_arr);                        // складываем цифры в масиве последнего числа

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("answer = %d runtime = %f\n", answ, time_spent); // выводим результат и время работы программы
    return 0;
}

int multiply(int num_ar1[], int num2)
// функция перемножает два числа и сохраняет результат в массиве
// параметры:	num_ar1[]   - первое число в виде массива
//              num_arr[0]  - количество занесенных в массив цифр числа
//              num2        - второе число
// return:                  - количество занесенных в массив цифр
{
    if (num2 >= LEN_ARR || num2 < 1)        // отрабатываем некорректные значения
    {
        printf("multiply(): Num2 = % d! "   // % d - пробел нужен, чтобы выравнять значения -1 и 1 в при выводе встолбик
               "Used number between 0 and % d \n",
               num2, LEN_ARR);              // красивый вывод в одну строчку
        return 0;
    }

    int residue = 0;                        // остаток
    int cnt = 0;                            // количество занесенных в массив цифр
    int ptr = 1;                            // указатель для перемещения по массиву (цифры начинаем заносить с num_ar1[1])

    while (ptr <= num_ar1[0] || residue)    // пока не перемножится на все цифры или есть остаток
    {
        residue += num_ar1[ptr] * num2;
        num_ar1[ptr++] = residue % 10;      // заносим младший разряд в массив
        residue /= 10;                      // и отрезаем его от остатка
        cnt++;
    }

    num_ar1[0] = cnt;                       // заносим в массив число цифр в нем

    return cnt;
}

int get_sum_dig(int num_ar1[])
// функция считает сумму цифр в числе (массиве)
// параметры:	num_ar1[]   - число в виде массива
//              num_arr[0]  - количество занесенных в массив цифр числа
// return:                  - сумма цифр числа
{
    if (num_ar1[0] >= LEN_ARR || num_ar1[0] < 1)    // отрабатываем некорректные значения
    {
        printf("get_sum_dig(): num_ar1[0] = % d! "  // % d - пробел нужен, чтобы выравнять значения -1 и 1 в при выводе встолбик
               "Used number between 0 and % d \n",
               num_ar1[0], LEN_ARR);                // красивый вывод в одну строчку

        return 0;
    }

    int sum = 0;

    for (int ptr = 1; ptr <= num_ar1[0]; ptr++)
        sum += num_ar1[ptr];                        // проходим по массиву и складываем цифры

    return sum;
}