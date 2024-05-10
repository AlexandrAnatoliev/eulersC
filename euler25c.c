// euler25c - 1000-Значное число Фибоначчи

// Последовательность Фибоначчи определяется рекурсивным правилом:

// Fn = Fn−1 + Fn−2, где F1 = 1 и F2 = 1.
// Таким образом, первые 12 членов последовательности равны:

// F1 = 1
// F2 = 1
// F3 = 2
// F4 = 3
// F5 = 5
// F6 = 8
// F7 = 13
// F8 = 21
// F9 = 34
// F10 = 55
// F11 = 89
// F12 = 144
// Двенадцатый член F12 - первый член последовательности, который содержит три цифры.

// Каков порядковый номер первого члена последовательности Фибоначчи, содержащего 1000 цифр?

#include <stdio.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>                                             // русский язык в printf()
#include <stdbool.h>

#define LEN_NUMB 9                                              // int -> 10-значные числа => одна ячейка будет вмещать 9 цифр
#define LEN_ARR 1000 / LEN_NUMB + 1                             // 1000 / 9 - количество ячеек в массиве

typedef enum priority
{
    prev,
    next
} prior_t;                                                      // очередность чисел Фибоначчи (предыдущее, последующее)

typedef struct big_num
{
    int bg_arr[LEN_ARR];                                        // храним число в виде массива девятизначных чисел [999999999,999999999...]
    int lenght;                                                 // количество цифр в числе
    int indx;                                                   // порядковый номер числа
    prior_t priority;                                           // порядок чисел относительно друг друга
} big_num_t;

int big_num_init(big_num_t *big_num, int num, int index, prior_t prior);
int get_len_num(int num);
int get_next_fib(big_num_t *fib_prev, big_num_t *fib_next);
text_t more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    setlocale(LC_ALL, "Rus");                                   // русский язык в printf()

    int answ;

    big_num_t fib1;
    big_num_t fib2;

    big_num_init(&fib1, 1, 1, prev);                            // первое число Фибоначчи
    big_num_init(&fib2, 1, 2, next);                            // второе

    while (fib1.lenght < 1000 && fib2.lenght < 1000)            // пока одно из чисел не достигло требуемой длины
    {
        if (fib1.priority == prev && fib2.priority == next)     // складываем и меняем fib1 и fib2 местами в зависимости от их очередности
            get_next_fib(&fib1, &fib2);
        else
            get_next_fib(&fib2, &fib1);
    }

    answ = (fib1.lenght > fib2.lenght) ? fib1.indx : fib2.indx; // ответ - индекс большего числа

    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("Ответ = %d время = %f\n", answ, time_spent);        // выводим результат и время работы программы
    return 0;
}

int big_num_init(big_num_t *big_num, int num, int index, prior_t prior)
// функция задает начальные значения числа
// параметры:	fib     - число Фибоначчи
//              num     - начальное значение числа
//              index   - порядковый номер числа
//              prior   - очередность числа
{
    for (int i = 0; i < LEN_ARR; i++)                           // обнуляем массив
        big_num->bg_arr[i] = 0;

    big_num->bg_arr[0] = num;
    big_num->indx = index;
    big_num->priority = prior;
    big_num->lenght = get_len_num(num);

    return 0;
}

int get_len_num(int num)
// функция получает количество цифр в числе
// параметры:   num - число
// return:          - количество цифр в числе
{
    int cnt = 0;

    while (num)
    {
        num /= 10;
        cnt++;
    }

    return cnt;
}

int get_next_fib(big_num_t *fib_prev, big_num_t *fib_next)
// функция получает следующее значение числа Фибоначчи
// параметры:	fib_prev    - число Фибоначчи
//              fib_next    - следующее за ним число
{
    if (fib_prev->priority != prev || fib_next->priority != next)
    {
        printf("get_next_fib(): В %d-м или %d-м числах не корректно заданы поля \"priority\"\n", fib_prev->indx, fib_next->indx);
        return 1;
    }

    int len_arr = fib_next->lenght / LEN_NUMB + 1;                                  // минимально необходимая длина массива для хранения числа
    int residue = 0;

    if (more_limit("get_next_fib()", "len_arr", len_arr, "LEN_ARR", LEN_ARR)) // обрабатываем выход за пределы массива
        return 1;

    for (int i = 0; i < len_arr; i++)
    {
        int sum_dig = (fib_prev->bg_arr[i] + fib_next->bg_arr[i]) + residue;        // складываем массивы по одной ячейке и переносим остаток
        fib_prev->bg_arr[i] = sum_dig % 1000000000;                                 // сохраняем в fib_prev сумму fib_prev и fib_next
        residue = sum_dig / 1000000000;
    }

    if (residue) // остался остаток
    {
        fib_prev->lenght = len_arr * LEN_NUMB + get_len_num(residue);               // определяем количество цифр в числе
        fib_prev->bg_arr[len_arr] = residue;
    }
    else
        fib_prev->lenght = (len_arr - 1) * LEN_NUMB + get_len_num(fib_prev->bg_arr[len_arr - 1]);

    fib_prev->indx += 2;                                                            // меняем порядковый номер числа
    fib_prev->priority = next;                                                      // и порядок чисел относительно друг друга
    fib_next->priority = prev;

    return 0;
}

text_t more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
    if (input_value > limit_value)                                                  // обрабатываем превышение
    {
        printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}

// #include <stdio.h>
// #include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
//     double time_spent = 0.0;                                // для хранения времени выполнения кода
//     clock_t begin = clock();                                // СТАРТ таймера

//     char arr_f1[1001] = {1};                        //первое число Фибоначчи
//     char arr_f2[1001] = {1};                        //второе
//     char arr_fnext[1001] = {0};                     //следующее - сумма первых двух
//     char num;
//     char dec = 0;
//     int cnt = 1;                                    //длина чисел
//     int f_num = 2;                                  //порядковый номер вычисленного числа Фибоначчи

//     while(cnt < 1000)
//     {
//         dec = 0;
//         for(int i = 0; i < cnt; i++)
//          {
//              num = arr_f1[i] + arr_f2[i] + dec;     //складываем поразрядно числа
//              arr_fnext[i] = num%10;                 //разделяем первый разряд
//              dec = num/10;                          //и второй - если есть
//              arr_f1[i] = arr_f2[i];                 //обновляем первое число Фибоначчи
//              arr_f2[i] = arr_fnext[i];              //обновляем второе
//          }

//         if (dec)                                    //если число не влезло в текущую разрядность
//         {
//             arr_f2[cnt] = dec;                      //записываем последнюю цифру в число
//             cnt++;                                  //увеличиваем разрядность чисел
//         }
//         f_num++;

//     }

//     clock_t end = clock();                                  // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

//     printf("answer = %d runtime = %f\n", f_num, time_spent);  // выводим результат и время работы программы
//     return 0;
// }