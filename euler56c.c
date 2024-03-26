// euler56c - Максимальная сумма цифр

// Гугол (10^100) - гигантское число: один со ста нулями;
// 100^100 почти невообразимо велико: один с двумястами нулями. Несмотря на их размер, сумма цифр каждого числа равна всего лишь 1.

// Рассматривая натуральные числа вида ab, где a, b < 100, какая встретится максимальная сумма цифр числа?

#include <stdio.h>
#include <stdbool.h>
#include <time.h> // для clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 200

typedef struct num_pow // структура "число^степень"
{
    int num;           // снование степени
    int power;         // показатель степени
    char arr[LEN_ARR]; // массив для хранения отдельных цифр
    int lenght;        // длина числа
} pow_t;

int num_pow_next(pow_t *num_pow);
int num_pow_init(pow_t *num_pow, int num, int power);
int summ_digs(pow_t *num_pow);
bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
    double time_spent = 0.0;
    clock_t begin = clock(); // СТАРТ таймера

    int answ = 0;
    int answ_num;
    int answ_pow;

    pow_t num_pow; // "число^степень"

    for (int num = 1; num < 100; num++)
    {
        num_pow_init(&num_pow, num, 1); // инициализируем очередное число

        while (num_pow.power < 99)
        {
            num_pow_next(&num_pow);        // перебираем его степени
            int cnt = summ_digs(&num_pow); // суммируем цифры внутри числа
            // answ = (answ > cnt) ? answ : cnt; // обновляем ответ
            if (answ < cnt)
            {
                answ = cnt;
                answ_num = num;
                answ_pow = num_pow.power;
            }
        }
    }

    clock_t end = clock();                                // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

    printf("Ответ = %d (%d^%d)время = %f\n", answ, answ_num, answ_pow, time_spent); // выводим результат и время работы программы
    return 0;
}

int num_pow_next(pow_t *num_pow)
// Функция для возведения числа в следующую степень
// Параметры:   num_pow - число в определенной степени
{
    int cnt = 0;
    int residue = 0;

    while (residue || cnt < num_pow->lenght) // перемножаем се числа в массиве на число
    {
        int number = num_pow->arr[cnt] * num_pow->num + residue;

        if (input_more_limit("num_pow_next()", "cnt++", cnt + 1, "LEN_ARR", LEN_ARR))
            return 1; // выход за пределы массива

        num_pow->arr[cnt++] = number % 10;
        residue = number / 10; // отделяем и переносим остаток
    }

    num_pow->lenght = cnt; // обновляем длину числа и его степень
    num_pow->power++;

    return 0;
}

int num_pow_init(pow_t *num_pow, int num, int power)
// Функция для присваиванию начальных значений числу в определенной степени
// Параметры:   num_pow - число в определенной степени
//              num     - число
//              power   - степень
{
    num_pow->num = num;
    for (int i = 0; i < LEN_ARR; i++) // обнуляем массив
        num_pow->arr[i] = 0;

    num_pow->power = 0; // заносим начальные данные в число
    num_pow->lenght = 1;
    num_pow->arr[0] = 1;

    for (int pow = 0; pow < power; pow++) // возводим число в необходимую степень
        num_pow_next(num_pow);

    return 0;
}

int summ_digs(pow_t *num_pow)
// Функция для подсчета суммы цифр в числе
// Параметры:   num_pow - число в определенной степени
{
    int sum = 0;

    for (int i = 0; i < num_pow->lenght; i++)
        sum += num_pow->arr[i]; // суммируем цифры числа

    return sum;
}

bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// Функция для определения превышения переменной своего предельного значения и вывода предупреждения
// Параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
    if (input_value > limit_value) // обрабатываем превышение
    {
        printf("%s: %s = %d больше %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}
