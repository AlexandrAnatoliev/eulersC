// euler17c - Счет букв в числительных

// Если записать числа от 1 до 5 английскими словами (one, two, three, four, five),
// то используется всего 3 + 3 + 5 + 4 + 4 = 19 букв.

// Сколько букв понадобится для записи всех чисел от 1 до 1000 (one thousand) включительно?

// Примечание: Не считайте пробелы и дефисы.
// Например, число 342 (three hundred and forty-two) состоит из 23 букв, число 115 (one hundred and fifteen) - из 20 букв.
// Использование "and" при записи чисел соответствует правилам британского английского.

#include <stdio.h>
// 1        one                     3
// 2        two                     3
// 3        three                   5
// 4	    four                    4
// 5		five                    4
// 6		six	                    3
// 7		seven                   5
// 8		eight                   5
// 9		nine                    4
// 10		ten                     3
// 11		eleven                  6
// 12		twelve                  6
// 13		thirteen                8
// 14		fourteen	            8
// 15		fifteen	                7
// 16		sixteen	                7
// 17		seventeen               9
// 18		eighteen                8
// 19		nineteen                8
// 20		twenty	                6
// 21	 	twenty one              6 + [3]
// 30		thirty	                6
// 40		forty	                5
// 50		fifty	                5
// 60		sixty	                5
// 70		seventy	                7
// 80		eighty	                6
// 90		ninety	                6
// 100		one hundred	            [3] + 7
// 101	 	one hundred and one	    [3] + 7 + 3? + [3]
// 1000		one thousand            11

// int main(void)
// {
//     int sum_letter = 0;
//     int numb_arr_1_19[] = {3,3,5,4,4,3,5,5,4,3,6,6,8,8,7,7,9,8,8};
//     int numb_arr_20_90[] = {6,6,5,5,5,7,6,6};
//     for(int numb = 1; numb <= 1000; numb++)
//     {
//         int len_numb = 0;

//         if(numb <= 19)
//             len_numb = numb_arr_1_19[numb - 1];

//         else if(numb < 100)
//         {
//             int simpl_numb = numb%10;           //цифры до десяти
//             int dec_numb = numb/10;             //десятки
//             if(simpl_numb != 0)
//                 len_numb = numb_arr_20_90[dec_numb - 2] + numb_arr_1_19[simpl_numb - 1];
//             else
//                 len_numb = numb_arr_20_90[dec_numb - 2];
//         }

//         else if(numb < 1000)
//         {
//             if(numb%100 < 20 && numb%100 > 9)
//             {
//                 int simpl_numb = numb%100;      //цифры от 10 до 19
//                 int hundr_numb = numb/100;      //сотни
//                 len_numb = numb_arr_1_19[hundr_numb - 1] + 7 + 3 + numb_arr_1_19[simpl_numb - 1];
//             }
//             else
//             {
//                 int simpl_numb = numb%10;       //цифры до десяти
//                 int dec_numb = numb%100/10;     //десятки
//                 int hundr_numb = numb/100;      //сотни
//                 if(simpl_numb == 0 && dec_numb == 0)
//                     len_numb = numb_arr_1_19[hundr_numb - 1] + 7;
//                 else if(simpl_numb == 0)
//                     len_numb = numb_arr_1_19[hundr_numb - 1] + 7 + 3 + numb_arr_20_90[dec_numb - 2];
//                 else if(dec_numb == 0)
//                     len_numb = numb_arr_1_19[hundr_numb - 1] + 7 + 3 + numb_arr_1_19[simpl_numb - 1];
//                 else
//                     len_numb = numb_arr_1_19[hundr_numb - 1] + 7 + 3 + numb_arr_20_90[dec_numb - 2] + numb_arr_1_19[simpl_numb - 1];
//             }
//         }
//         else if (numb == 1000)
//             len_numb = 11;

//         sum_letter += len_numb;

//     }
//     printf("%d",sum_letter);
//     return 0;
// }

// 1        one                     3
// 2        two                     3
// 3        three                   5
// 4	    four                    4
// 5		five                    4
// 6		six	                    3
// 7		seven                   5
// 8		eight                   5
// 9		nine                    4
// 10		ten                     3
// 11		eleven                  6
// 12		twelve                  6
// 13		thirteen                8
// 14		fourteen	            8
// 15		fifteen	                7
// 16		sixteen	                7
// 17		seventeen               9
// 18		eighteen                8
// 19		nineteen                8
// 20		twenty	                6
// 21	 	twenty one              6 + [3]
// 30		thirty	                6
// 40		forty	                5
// 50		fifty	                5
// 60		sixty	                5
// 70		seventy	                7
// 80		eighty	                6
// 90		ninety	                6
// 100		one hundred	            [3] + 7
// 101	 	one hundred and one	    [3] + 7 + 3? + [3]
// 1000		one thousand            11

#include <stdio.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

int count_letters(int num);

int main(void)
{
    double time_spent = 0.0;                                        // для хранения времени выполнения кода
    clock_t begin = clock();                                        // СТАРТ таймера

    int sum_letter = 0;

    for (int num = -1; num <= 1000; num++)                           // перебираем числа и считаем в них буквы
        sum_letter += count_letters(num);

    clock_t end = clock();                                          // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;           // время работы в секундах

    printf("answer = %d runtime = %f\n", sum_letter, time_spent);   // выводим результат и время работы программы
    return 0;
}

int count_letters(int num)
// функция возвращает количество букв в английском числе
// параметры:	num - число
// return:          - количество букв в английском числе
{
    int count = 0;
    int len_ar_1_19[] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
    int len_ar_20_90[] = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};
    int len_100 = 7;                                                // hundred
    int len_1000 = 8;                                               // thousand
    int len_and = 3;

    if (num > 9999 || num < 1)                                      // отрабатываем некорректные значения
    {
        printf( "Number = % d! "                                    // % d - пробел нужен, чтобы выравнять значения -1 и 1 в при выводе встолбик
                "Input number between 1 and 9999\n", num);          // красивый вывод в одну строчку
        return 0;
    }

    count += (num / 1000) ? len_ar_1_19[num / 1000] + len_1000 : 0; // считаем тысячи: one thousand
    num %= 1000;

    count += (num / 100) ? len_ar_1_19[num / 100] + len_100 : 0;    // сотни: one thousand one hundred
    num %= 100;

    if (num && count)
        count += len_and;                                           // добавляем "и": one thousand one hundred and

    if (num < 20)
        count += len_ar_1_19[num];                                  // десятки и числа: one thousand one hundred and one
    else
    {
        count += len_ar_20_90[num / 10];
        num %= 10;
        count += len_ar_1_19[num];                                  // one thousand one hundred and twenty one
    }
    
    return count;
}