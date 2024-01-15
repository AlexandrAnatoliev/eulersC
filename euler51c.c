// euler51c - Замена цифр в простом числе

// Меняя первую цифру числа *3 (двузначного числа, заканчивающегося цифрой 3), оказывается,
// что шесть из девяти возможных значений - 13, 23, 43, 53, 73 и 83 - являются простыми числами.

// При замене третьей и четвертой цифры числа 56**3 одинаковыми цифрами, получаются десять чисел,
// из которых семь - простые: 56003, 56113, 56333, 56443, 56663, 56773 и 56993.
// Число 56**3 является наименьшим числом, подставление цифр в которое дает именно семь простых чисел.
// Соответственно, число 56003, будучи первым из полученных простых чисел, является наименьшим простым числом,
// обладающим указанным свойством.

// Найдите наименьшее простое число, которое является одним из восьми простых чисел,
// полученных заменой части цифр (не обязательно соседних) одинаковыми цифрами.

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 1000000 // длина массивов - зависит от размера искомого числа

bool is_composite(char comp_arr[], int num)
// функция принимает число и возвращает true - если число составное
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              num                 - проверяемое число
// return:      true                - если число составное!
{
    int div_max = sqrt(num) + 1; // выносим вычисление квадратного корня из цикла for

    for (int div = 2; div < div_max; div++) // чтобы он не вычислялся каждую итерацию цикла
    {
        // пропускаем составные делители и срабатываем при num % i == 0
        if (!comp_arr[div] && !(num % div))
            return true;
    }

    return false;
}

int note_composite(char comp_arr[], int step, int start, int finish)
// функция отмечает составные числа в массиве
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              step                - простое число, служит шагом
//              start               - начальный индекс в массиве
//              finish              - конечный индекс
// return:                          - количество отмеченных составных чисел
{
    int shift = (start % step == 0) ? 0 : step - (start % step); // смещение индекса start
    start += shift;                                              // первое составное число

    for (int i = start + step; i < finish; i += step) // первое число - простое, не отмечаем его
    {
        if (!comp_arr[i])    // если еще не отмечено
            comp_arr[i] = 1; // отмечаем составные числа
    }

    return 0;
}

int get_factorial(int number)
// функция возвращает факториал числа
// параметры:	number  - натуральное число
// return:              - факториал числа
{
    int factorial = 1;
    for (int i = number; i > 0; i--) // считаем максимально возможную длину числа
        factorial *= i;

    return factorial;
}

int count_replacements(int number)
// функция считает количество возможных перестановок для числа и same_digits количества одинаковых цифр
// параметры:	number      - натуральное число
// return:                  - количество отмеченных составных чисел
{
    int max_len = 0; // максимально возможная длина числа (ограничена [LEN_ARR])
    int number_len = 0;
    int answ;
    int same_digits; // количество одинаковых чисел

    for (int i = LEN_ARR; i > 1; i /= 10) // ДО! 1000000 - 6-значные числа
        max_len++;

    for (int i = number; i > 0; i /= 10) // считаем длину числа
        number_len++;

    same_digits = max_len - number_len;

    answ = get_factorial(max_len - 1) / get_factorial(same_digits);
    // (max_len - 1)! / same_digits! - не считаем крайнее правое число (max_len - 1), его менять не будем

    return answ;
}

int main(void)
{
    double time_spent = 0.0; // для хранения времени выполнения кода
    clock_t begin = clock(); // СТАРТ таймера

    static char composit_arr[LEN_ARR] = {0}; // массив[составное число] = 1 - static писать!
    int answ = 0;

    for (int num = 2; num < LEN_ARR; num++) // определяем список простых чисел (!составных)
    {
        // если число не отмечено составным -> проверяем число -> если число простое
        if (!composit_arr[num] && !is_composite(composit_arr, num))
            note_composite(composit_arr, num, num, LEN_ARR); // отмечаем составные числа, кратные простому
    }

    answ = count_replacements(12);
    clock_t end = clock();                                // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

    printf("answer = %d runtime = %f\n", answ, time_spent); // выводим результат и время работы программы

    return 0;
}
