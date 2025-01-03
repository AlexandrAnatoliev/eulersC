// euler26c - Обратные циклы

// Единичная дробь имеет 1 в числителе. Десятичные представления единичных дробей со знаменателями от 2 до 10 даны ниже:

// 1/2	=	0.5
// 1/3	=	0.(3)
// 1/4	=	0.25
// 1/5	=	0.2
// 1/6	=	0.1(6)
// 1/7	=	0.(142857)
// 1/8	=	0.125
// 1/9	=	0.(1)
// 1/10	=	0.1
// Где 0.1(6) значит 0.166666..., и имеет повторяющуюся последовательность из одной цифры.
// Заметим, что 1/7 имеет повторяющуюся последовательность из 6 цифр.

// Найдите значение d < 1000, для которого 1/d в десятичном виде содержит самую длинную повторяющуюся последовательность цифр.

#include <stdio.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>                                         // русский язык в printf()
#include <stdlib.h>                                         // для calloc() и free()

int get_len_rec_cycle(int den);
int get_start_rec_cycle(int residue, char res_arr[]);

int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    setlocale(LC_ALL, "Rus");                               // русский язык в printf()

    int answ = 0;
    int len_max = 0;
    int den = 1000;

    while (den > 2 && den > len_max)                        // длина последовательности не может быть больше делителя
    {
        int len = get_len_rec_cycle(den);
        if (len_max < len)                                  // обновляем ответ
        {
            len_max = len;
            answ = den;
        }
        den--;
    }

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("Ответ = %d время = %f\n", answ, time_spent);    // выводим результат и время работы программы

    return 0;
}

int get_len_rec_cycle(int den)
// Функция возвращает длину повторяющейся последовательности
// Параметры:   den - знаменатель дроби 1/denom
// return:      0   - если дробь не имеет повторяющейся последовательности
{
    int len = 0;                                        // длина последовательности
    int residue = 1;
    char *res_cash = calloc(den, sizeof(char)); // динамический массив для хранения остатков деления по индексу (заполнен нулями)
    char *res_arr = calloc(den, sizeof(char));

    while (residue && len < den)                        // пока есть остаток и не выходим за пределы массива
    {
        while (residue / den == 0)
        {
            residue *= 10;
            len++;
        }

        residue %= den;                                 // вычисляем очередной остаток от деления

        if (res_cash[residue])                          // если такой был
        {
            len++;
            break;
        }

        res_arr[len] = residue;                         // заносим остатки по очереди, чтобы найти первое включение
        res_cash[residue] = 1;                          // кэшуем в массив
    }

    if (residue == 0)                                   // дробь не имеет повторяющейся последовательности
        len = 0;
    else
        len -= get_start_rec_cycle(residue, res_arr);   // конец последовательности - ее начало = длина

    free(res_cash);
    free(res_arr);

    return len;
}

int get_start_rec_cycle(int residue, char res_arr[])
// Функция возвращает первое включение остатка в массив
// Параметры:   residue     - остаток
//              res_arr[]   - массив с записанными остатками по порядку
// return:      порядковый номер остатка
{
    int indx = 0;
    while (res_arr[indx++] != residue && indx < residue)    // ищем первое вхождение в массив
        ;
    return indx;
}

// #include <stdio.h>
// #define LEN_ARR 2000

// int get_div_arr(char arr_arg[], int den_arg)
// // принимает массив, в который заносятся результаты деления и делитель
// // возвращает количество занесенных знаков в массив
// {
//     int pos = 0;
//     int num_pos = 1;      // при делении 1/2  -> запишется 0
//     int num_next_pos = 0; //                  -> запишется 5
//     // делим 1 на делитель и записываем цифры в массив
//     while ((pos < LEN_ARR) && (num_pos / den_arg != 0 || num_pos % den_arg != 0))
//     {
//         if (num_pos / den_arg == 0)
//         {
//             num_pos *= 10;
//             arr_arg[pos++] = 0;
//         }
//         else
//         {
//             num_next_pos = num_pos % den_arg;
//             num_pos /= den_arg;
//             arr_arg[pos++] = num_pos;
//             num_pos = num_next_pos * 10;
//         }
//     }
//     return pos; // вернет количество занесенных цифр
// }

// int get_max_series(const char arr_arg[], int len_arr_arg)
// // принимает массив и количество записанных внего цифр
// // возвращает длину максимальной повторяющейся последовательности
// {
//     int answ_len = 0; // длина найденной последовательности
//     int cnt = 0;      // счетчик длины последовательности

//     for (int i_ptr = 1; i_ptr < len_arr_arg; i_ptr++) // сравниваем каждую цифру
//     {
//         if (arr_arg[i_ptr] == 0)
//             continue;
//         int max_cnt = 0;

//         for (int j_ptr = i_ptr + 1; j_ptr < len_arr_arg; j_ptr++) // со следующими за ней
//         {
//             cnt = 0;
//             if (arr_arg[i_ptr] == arr_arg[j_ptr]) // если совпали цифры
//             {
//                 while ((arr_arg[i_ptr + cnt] == arr_arg[j_ptr + cnt]) && (i_ptr + cnt < j_ptr) && (i_ptr + cnt < len_arr_arg))
//                 // пока совпадают и счетчик не зашел в уже посчитанные цифры и не вышел за пределы массива
//                 {
//                     cnt++; // увеличиваем счетчик и перемещаем указатели i_ptr и j_ptr
//                 }

//                 max_cnt = (max_cnt > cnt) ? max_cnt : cnt; // обновляем  максимум найденной последовательности
//                 if (i_ptr + cnt >= j_ptr)                  // если две последовательности подряд
//                     break;
//                 j_ptr += cnt - 1; // перемещаем указатель сразу на количество проверенных цифр
//             }
//         }

//         answ_len = max_cnt; // найденная максимальная последовательность

//         if (i_ptr + cnt >= max_cnt) // если две последовательности подряд
//             break;

//         i_ptr += max_cnt; // перемещаем указатель сразу на количество проверенных цифр
//     }
//     return answ_len;
// }

// int main(void)
// {
//     char arr[LEN_ARR] = {0}; // массив для записи результата деления
//     int den = 2;             // делитель
//     int len_arr = 0;         // количество знаков в результате деления
//     int answ_len = 0;
//     int answ = 0;

//     for (den = 2; den < 1000; den++)
//     {
//         len_arr = get_div_arr(arr, den);
//         int len_answ = get_max_series(arr, len_arr); // сохраняем результат вычислений, чтобы не вычислять многократно
//         if (answ_len < len_answ)
//         {
//             answ_len = len_answ;
//             answ = den;
//         }
//     }

//     printf("answ = %d\nansw_len = %d", answ, answ_len);
//     return 0;
// }