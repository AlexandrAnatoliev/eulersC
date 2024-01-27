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
#include <math.h>       // для pow() - возвращает тип double!!!
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 1000000 // длина массива для простых чисел - зависит от размера искомого числа
// для корректной работы функции count_replacements() LEN_ARR должно быть "круглым" числом - 1000, 10000 и т.п.
#define LEN_CNT_AR 100  // длина массива для записи номеров размещений
#define LEN_REPLACE 5   // длина размещения без последней цифры xxx12 (3)
#define LEN_NUM 2       // длина перебираемого числа без последней цифры 12 (3)
#define VALUE_PRIME 8   // искомое количество простых чисел
#define START 101       // диапазон перебираемых чисел
#define FINISH 1000

bool is_composite(char comp_arr[], int num);
int note_composite(char comp_arr[], int prime, int finish);
int get_cnt_replacement(char cnt_ar[], int len_replace, int len_num);
int get_replacment(int len_replace, int num, int cnt_replace, int some);
int count_primes(char comp_arr[], int len_replace, int num, int cnt_replace, int value_prime);
int print_primes(char comp_arr[], int len_replace, int num, int cnt_replace);

int main(void)
{
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    static char composit_arr[LEN_ARR] = {0};                    // массив[составное число] = 1 - static писать!
    int answ = 0;

    for (int num = 2; num < LEN_ARR; num++)                     // определяем список простых чисел (!составных)
    {
        // если число не отмечено составным -> проверяем число -> если число простое
        if (!composit_arr[num] && !is_composite(composit_arr, num))
            note_composite(composit_arr, num, LEN_ARR);         // отмечаем составные числа, кратные простому
    }

    char cnt_arr[LEN_CNT_AR] = {0};                             // массив для записи номеров размещений
    int ptr;                                                    // указатель на число в массиве

    get_cnt_replacement(cnt_arr, LEN_REPLACE, LEN_NUM);         // записываем варианты размещения цифр в числе
    // xxx123 - (3) отделяем (не меняется), остается 5-значное число xxx12 (3)
    // c 2-значным числом из разных цифр [12] и 3-мя одинаковыми цифрами [xxx]

    int num = START;                                            // перебираем 3-значные числа
    while (answ != VALUE_PRIME && num < FINISH)
    {
        ptr = 0;
        while (cnt_arr[ptr] && answ != VALUE_PRIME)             // зная число (123) перебираем варинты 000123... 001203... 111123... 111213
            answ = count_primes(composit_arr, LEN_REPLACE, num, cnt_arr[ptr++], VALUE_PRIME);
        num += 2;                                               // перебираем только нечетные число, четные заведомо составные
    }

    print_primes(composit_arr, LEN_REPLACE, num - 2, cnt_arr[ptr - 1]);

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answers = %d runtime = %f\n", answ, time_spent);    // выводим результат и время работы программы

    return 0;
}

bool is_composite(char comp_arr[], int num)
// функция принимает число и возвращает true - если число составное
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              num                 - проверяемое число
// return:      true                - если число составное!
{
    if (num >= LEN_ARR || num < 0)          // проверка на выход числа за пределы массива
    {
        printf("is_composite(): array index (num) = % d out of bounds [0 - %d]\n", num, LEN_ARR);
        return false;
    }

    int div_max = sqrt(num) + 1;            // выносим вычисление квадратного корня из цикла for

    for (int div = 2; div < div_max; div++) // чтобы он не вычислялся каждую итерацию цикла
    {
        if (!comp_arr[div] && !(num % div)) // пропускаем составные делители и срабатываем при num % i == 0
            return true;
    }

    return false;
}

int note_composite(char comp_arr[], int prime, int finish)
// функция отмечает составные числа в массиве
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              prime               - простое число, служит шагом
//              finish              - конечный индекс в массиве
// return:                          - количество отмеченных составных чисел
{
    if (prime >= LEN_ARR + 1 || prime < 0)          // проверка на выход числа за пределы массива
    {
        printf("note_composite(): array index (prime) = % d out of bounds [0 - %d]\n", prime, LEN_ARR);
        return false;
    }

    if (finish >= LEN_ARR + 1 || finish < 0)        // проверка на выход числа за пределы массива
    {
        printf("note_composite(): array index (finish) = % d out of bounds [0 - %d]\n", finish, LEN_ARR);
        return false;
    }

    for (int i = prime * 2; i < finish; i += prime) // первое число - простое, не отмечаем его
    {
        if (!comp_arr[i])                           // если еще не отмечено
            comp_arr[i] = 1;                        // отмечаем составные числа
    }

    return 0;
}

int get_cnt_replacement(char cnt_ar[], int len_replace, int len_num)
// Для размещения числа 123 (3 цифры) в 5-значном числе вида хх123 функция формирует код 00111
// в виде x1x23 - код 01011 и так далее.
// где 1 - цифра исходного числа, 0 - одинаковые числа, которые будут меняться 00123... 11123... 22123... 33123
// Функция заполняет массив возможными размещениями в виде десятичных чисел 7 = 00111 в двоичном, 11 = 01011 и т.д.
// параметры:   cnt_ar[]    - массив для сохранения размещений числа в десятичном виде
//              len_replace - длина числа после перестановки
//              len_num     - длина исходного числа, в которое добавляются одинаковые числа
// return:                  - количество занесенных в массив размещений цифр
{
    int cnt = 0;
    int max_num = pow(2, len_replace);

    if (max_num >= LEN_CNT_AR)                                      // проверка на выход числа за пределы массива
    {
        printf("get_cnt_replacement(): array index (max_num) = % d out of bounds [0 - %d]\n", max_num, LEN_CNT_AR);
        return false;
    }

    for (int replace_num = 1; replace_num < max_num; replace_num++) // перебираем варинты размещения
    {
        int mask = 1;
        int cnt_coincidence = 0;

        while (mask < max_num)                                      // проходим маской по доичному числу
        {
            if (replace_num & mask)
                cnt_coincidence++;                                  // считаем 1

            if (cnt_coincidence > len_num)                          // пока не кончится число
                break;
            mask = mask << 1;
        }

        cnt_ar[cnt++] = replace_num;                                // заполняем массив варинтами размещения
    }
    return cnt;
}

int get_replacment(int len_replace, int num, int cnt_replace, int some)
// Формирует размещение чисел
// параметры:   len_replace - длина числа после перестановки (44123) - 5 чисел
//              num         - исходное число (123)
//              cnt_replace - номер размещения (7 - 00111)
//              some        - числа, являющиеся одинаковыми в размещении 44123 - цифра 4
// return:                  - размещение цифр в виде числа 44123
{
    int degree = 1;
    int replace = 0;
    int max_num = pow(2, len_replace);
    int mask = 1;
    int ptr = 0;
    char arr[16] = {0};                     // массив для хранения числа

    while (num)                             // раскладываем число в массив 123
    {
        arr[ptr++] = num % 10;
        num /= 10;
    }
    ptr = 0;

    while (mask < max_num)                  // проходим маской по двузначному числу размещению 00111
    {
        if (cnt_replace & mask)
            replace += arr[ptr++] * degree; // если 1 - берем число из 123
        else
            replace += some * degree;       // иначе берем число some (одинаковые числа)
        degree *= 10;
        mask = mask << 1;
    }

    return replace;
}

int count_primes(char comp_arr[], int len_replace, int num, int cnt_replace, int value_prime)
// перебирает размещения чисел и считает простые из них
// от числа отрезается младшая цифра и остальные перебираются
// 123 -> 12 (3) -> 44412(3) -> 44124(3) -> 41244(3) -> 12444(3)
// параметры:   comp_arr[]  - массив простых/составных чисел
//              len_replace - длина числа после перестановки (44412) - 5 чисел
//              num         - исходное число (123) - обрезается до 12
//              cnt_replace - номер размещения (3 - 00011)
//              some        - числа, являющиеся одинаковыми в размещении 44412 - цифра 4
//              value_prime - сколько простых чисел ищется
// return:                  - количество найденных простых чисел
{
    int cnt_prime = 0;
    int cnt_comp = 0;
    int replace;

    for (int some = 0; some < 10; some++)
    {
        replace = num % 10 + get_replacment(len_replace, num / 10, cnt_replace, some) * 10;

        bool len_fl = replace / (int)pow(10, len_replace);  // отсекаем числа меньшей длины 000123 -> 123

        if (replace >= LEN_ARR)                             // проверка на выход числа за пределы массива
        {
            printf("count_primes(): array index (replace) = % d out of bounds [0 - %d]\n", replace, LEN_ARR);
            return false;
        }

        if (comp_arr[replace] == 0 && len_fl)
            cnt_prime++;                                    // считаем простые числа
        else
            cnt_comp++;                                     // и составные

        if (cnt_comp > 10 - value_prime)                    // если число составных чисел велико
            return cnt_prime;                               // дальше можно не искать
    }

    return cnt_prime;
}

int print_primes(char comp_arr[], int len_replace, int num, int cnt_replace)
// перебирает размещения чисел и выводит простые из них
// от числа отрезается младшая цифра и остальные перебираются
// 123 -> 12 (3) -> 44412(3) -> 44124(3) -> 41244(3) -> 12444(3)
// параметры:   comp_arr[]  - массив простых/составных чисел
//              len_replace - длина числа после перестановки (44412) - 5 чисел
//              num         - исходное число (123) - обрезается до 12
//              cnt_replace - номер размещения (3 - 00011)
//              some        - числа, являющиеся одинаковыми в размещении 44412 - цифра 4
//              value_prime - сколько простых чисел ищется
// return:                  - количество найденных простых чисел
{
    int cnt_prime = 0;
    int replace;

    for (int some = 0; some < 10; some++)
    {
        replace = num % 10 + get_replacment(len_replace, num / 10, cnt_replace, some) * 10;

        if (replace >= LEN_ARR)                 // проверка на выход числа за пределы массива
        {
            printf("print_primes(): array index (replace) = % d out of bounds [0 - %d]\n", replace, LEN_ARR);
            return false;
        }

        if (comp_arr[replace] == 0)
        {
            printf("%d\n", replace);
            cnt_prime++;
        }
    }

    return cnt_prime;
}