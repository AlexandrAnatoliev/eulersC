// euler43c - Делимость подстрок

// Число 1406357289, является пан-цифровым, поскольку оно состоит из цифр от 0 до 9 в определенном порядке.
// Помимо этого, оно также обладает интересным свойством делимости подстрок.

// Пусть d1 будет 1-й цифрой, d2 будет 2-й цифрой, и т.д. В таком случае, можно заметить следующее:

// d2d3d4=406 делится на 2 без остатка
// d3d4d5=063 делится на 3 без остатка
// d4d5d6=635 делится на 5 без остатка
// d5d6d7=357 делится на 7 без остатка
// d6d7d8=572 делится на 11 без остатка
// d7d8d9=728 делится на 13 без остатка
// d8d9d10=289 делится на 17 без остатка
// Найдите сумму всех пан-цифровых чисел из цифр от 0 до 9, обладающих данным свойством.// 16695334890

#include <stdio.h>
#include <stdbool.h>
#include <time.h>           // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>         // русский язык в printf()

#define PANDIG 10           // длина пан-цифрового числа
#define SUB_DIV 3           // длина подстроки

typedef enum name           // структура "имена подстрок"
{
    d1d2d3, d2d3d4, d3d4d5, d4d5d6, d5d6d7, d6d7d8, d7d8d9, d8d9d10
} name_t;

typedef struct text
{
    char *arr;          // ссылка на массив
    int lenght;         // длина массива
} text_t;

typedef struct sub_string   // структура "подстрока"
{
    char arr[SUB_DIV];      // массив цифр числа
    int num;                // само число
    int div;                // делитель
    name_t name;            // имя подстроки == индексу в массиве цифры
} sub_t;

typedef struct pangigital   // структура "пан-цифровое число"
{
    char fl_arr[PANDIG];    // fl_arr[4] = 1, в числе есть цира 4
    char dig_arr[PANDIG];   // массив цифр числа
    sub_t str_arr[8];       // массив подстрок [d1d2d3, d2d3d4,...,d8d9d10]
} pandig_t;

bool sub_div_init(sub_t *sub_div, name_t name, int num);
bool pandig_init(pandig_t *pandig);
int get_next_sub_str(pandig_t *pandig, sub_t *sub_div);
bool put_digs(pandig_t *pandig, sub_t *sub_div);
bool clear_digs(pandig_t *pandig, sub_t *sub_div);

int main(void)
{
    setlocale(LC_ALL, "Rus");                                           // русский язык в printf()

    double time_spent = 0.0;                                            // для хранения времени выполнения кода
    clock_t begin = clock();                                            // СТАРТ таймера

    long long answ = 0;
    pandig_t pandig;
    name_t sub_str = d8d9d10;                                           // начинаем подбор подстрок с крайней справа

    pandig_init(&pandig);

    while (pandig.str_arr[d8d9d10].num < 999)                           // пока три крайние цифры не дойдут до 999
    {
        while (sub_str > d1d2d3)                                        // пока не дойдем до крайней левой подстроки
        {
            if (get_next_sub_str(&pandig, &pandig.str_arr[sub_str]))    // найдена следующая подстрока
                sub_str--;                                              // переходим на следующую - влево
            else                                                        // переходим на предыдущую подстроку - вправо
            {
                if (pandig.str_arr[d8d9d10].num >= 1000)                // закончен перебор
                    break;

                if (pandig.dig_arr[sub_str])                            // если текущая цифра в пан-цифровом числе не ноль
                {
                    pandig.fl_arr[pandig.dig_arr[sub_str]] = 0;         // обнуляем ее
                    pandig.dig_arr[sub_str] = 0;
                }

                sub_div_init(&pandig.str_arr[sub_str], sub_str, 0);     // обнуляем подстроку

                sub_str++;                                              // переходим на предыдущую подстроку - вправо
            }
        }

        if (pandig.str_arr[d8d9d10].num >= 1000)                        // перебраны все возможные комбинации
            break;

        for (long long i = 0, fact = 1000000000; i < PANDIG; i++, fact /= 10)
        {
            answ += pandig.dig_arr[i] * fact;                           // заносим в ответ цифры из массива пан-цифрового числа
            if (pandig.fl_arr[i] == 0)
                answ += i * 1000000000;                                 // заносим цифру числа, не занесенную в массив
        }

        sub_str++;                                                      // переходим на предыдущую подстроку - вправо
    }

    clock_t end = clock();                                              // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;               // время работы в секундах

    printf("Ответ = %llu время = %f\n", answ, time_spent);              // выводим результат и время работы программы

    return 0;
}

bool sub_div_init(sub_t *sub_div, name_t name, int num)
// Функция для задания начальных значения подстроке
// Параметры:	sub_div - структура "подстрока"
//              name    - имя подстроки
//              num     - численное значение подстроки
// return:      true    - успешная инициализация структуры
{
    int div_arr[] = {1, 2, 3, 5, 7, 11, 13, 17};    // массив с делителями

    sub_div->num = num;                             // заносим начальные данные
    sub_div->name = name;
    sub_div->div = div_arr[name];

    for (int i = 0; i < SUB_DIV; i++)
    {
        sub_div->arr[i] = num % 10;
        num /= 10;
    }

    return true;
}

bool pandig_init(pandig_t *pandig)
// Функция для задания начальных значения пан-цифровому числу
// Параметры:	pandig - структура "пан-цифровое число"
// return:      true    - успешная инициализация структуры
{
    for (int i = 0; i < PANDIG; i++)    // обнуляем начальные данные
    {
        pandig->fl_arr[i] = 0;
        pandig->dig_arr[i] = 0;
    }

    for (int name = 0; name < 8; name++)
        sub_div_init(&pandig->str_arr[name], name, 0);

    return true;
}

int get_next_sub_str(pandig_t *pandig, sub_t *sub_div)
// Функция для получения следующего значения подстроки
// Параметры:	pandig  - структура "пан-цифровое число"
//              sub_div - структура "подстрока"
// return:      0       - перебраны все возможные значения подстроки
//                      - значение подстроки
{
    sub_t past_sub_div = *sub_div;                  // сохраняем предыдущее значение
    int num = 0;

    if (sub_div->name == d8d9d10)                   // перебираем все три цифры
    {
        while (sub_div->num < 1000)
        {
            sub_div->num++;                         // перебираем значения подстроки
            int dig1 = sub_div->num / 100;          // раскладываем ее на отдельные цифры
            int dig2 = (sub_div->num % 100) / 10;
            int dig3 = sub_div->num % 10;

            if (sub_div->num % sub_div->div == 0                 // пока подстрока не поделится на делитель
                && dig1 != dig2 && dig2 != dig3 && dig1 != dig3) // и не будет одинаковых цифры в числе
                break;
        }

        if (sub_div->num >= 1000)                   // перебраны все возможные значения подстроки
            return 0;

        num = sub_div->num;

        clear_digs(pandig, &past_sub_div);         // из панцифрового числа удаляем цифры предыдущего значения подстроки
        sub_div_init(sub_div, sub_div->name, num); // обновляем текущее значение подстроки
        put_digs(pandig, sub_div);                 // заносим цифры текущего значения

        return sub_div->num;
    }

    else                                                    // перебираем только старшую цифру
    {
        int num = 0;
        int first_dig = sub_div->arr[2];                    // первая цифра числа подстроки

        for (int i = sub_div->name + 1, fact = 10; i < sub_div->name + 3; i++, fact /= 10)  // получаем число из двух цифр
            num += pandig->dig_arr[i] * fact;                                               // уже записанное в массиве

        for (int dig = first_dig; dig < PANDIG; dig++)      // перебираем цифры, еще не использованные в пан-цифровом числе
        {
            if ((pandig->fl_arr[dig] == 0) && ((dig * 100 + num)) % sub_div->div == 0)      // проверяем на делимость
            {
                num += dig * 100;

                clear_digs(pandig, &past_sub_div);          // удаляем цифры предыдущего значения подстроки
                sub_div_init(sub_div, sub_div->name, num);  // обновляем текущее значение подстроки
                put_digs(pandig, sub_div);                  // заносим цифры из текущего значения подстроки в пан-цифровое число

                if (first_dig)                              // при необходимости - обнуляем цифру в пан-цифровом числе
                    pandig->fl_arr[first_dig] = 0;

                return sub_div->num;
            }
        }
    }
    return 0;
}

bool put_digs(pandig_t *pandig, sub_t *sub_div)
// Функция для занесения значений из подстроки в пан-цифровое число
// Параметры:	pandig - структура "пан-цифровое число"
//              sub_div - структура "подстрока"
// return:      true    - успешно
{
    for (int i = 0, j = sub_div->name + 2; i < SUB_DIV; i++, j--)
    {
        pandig->fl_arr[sub_div->arr[i]] = 1;  // отмечаем цифры как занятые
        pandig->dig_arr[j] = sub_div->arr[i]; // заносим цифры в массив
    }

    return true;
}

bool clear_digs(pandig_t *pandig, sub_t *sub_div)
// Функция для удаления значений подстроки из пан-цифрового числа
// Параметры:	pandig - структура "пан-цифровое число"
//              sub_div - структура "подстрока"
// return:      true    - успешно
{
    for (int i = 0; i < SUB_DIV; i++)
    {
        pandig->fl_arr[sub_div->arr[i]] = 0;    // убираем цифры
        pandig->dig_arr[sub_div->name + i] = 0; // из пан-цифрового числа
    }

    return true;
}

// #include <stdio.h>
// #include <stdbool.h>

// bool increase_indx_num(int indx_num[])
// // функция увеличивает промежуточное число на единицу и обновляет массив
// // параметры:	indx_num    - массив c индексами
// // return:      false       - при достижении максимально возможного числа
// {
//     int max_indx_arr[] = {9,8,7,6,5,4,3,2,1,0};             // максимально возможный индекс
//     indx_num[8]++;                                          // увеличиваем число
//     for(int i = 8; i > 0; i--)
//     {
//         if(indx_num[i] > max_indx_arr[i])                   // если разряд переполняется
//         {
//             indx_num[i - 1]++;                              // увеличиваем старший разряд
//             indx_num[i]= 0;
//         }
//         else
//             break;                                          // прерываем, если не нужно дальше менять числа
//     }

//     for(int i = 0; i < 10; i++)                             // проверка достижения максимально возможного числа
//     {
//         if(indx_num[i] < max_indx_arr[i])
//             break;
//         if(i == 9)                                          // indx_num[] = {9,8,7,6,5,4,3,2,1,0}
//             return false;                                   // достигли максимально возможного числа
//     }
//     return true;
// }

// void get_pandigital_num(int pandig_num[], int indx_num[])
// // функция вычисляет пан-цифровое число по массиву с индексами перестановок
// // параметры:	indx_num        - массив c индексами
// //              pandigital_num  - массив с панцифровым числом
// {
//     int sort_arr[10] = {0,1,2,3,4,5,6,7,8,9};               // отсортированные числа
//     for(int i = 0; i < 10; i++)
//     {
//         pandig_num[i] = sort_arr[indx_num[i]];              // выбираем число из отсортированного массива
//         for(int j = indx_num[i]; j < (9 - i); j++)          // смещаем числа в массиве
//             sort_arr[j] = sort_arr[j + 1];
//     }
// }

// bool is_sub_str_div(int pandig_num[])
// // функция проверяет обладает ли пан-цифровое число свойством делимости подстрок
// // параметры:   pandigital_num  - массив с панцифровым числом
// // return:      true            - пан-цифровое число обладает свойством делимости подстрок
// {
//     int arr_div[] = {2,3,5,7,11,13,17};                     // массив с делителями

//     for(int i = 0; i < 7; i++)
//     {
//         if((pandig_num[i + 1] * 100 + pandig_num[i + 2] * 10 + pandig_num[i + 3]) % arr_div[i])
//             return false;                                   // d2d3d4 % 2 != 0 => делится на 2 c остатком и т.д.
//     }
//     return true;
// }

// long long get_num(int pandig_num[])
// // функция преобразует массив с цифрами в десятизначное число
// // параметры:   pandigital_num  - массив с панцифровым числом
// // return:                      - десятизначное число
// {
//     long long num = 0;
//     long long fact = 1000000000;
//     for(int i = 0; i < 10; i++, fact /= 10)
//         num += pandig_num[i] * fact;
//     return num;
// }

// int main(void)
// {
// 	int indx_num[10] = {0};                                 // промежуточное число-из-индексов
//     int pandigital_num[10] = {0};                           // пан-цифровое число

//     long long answ = 0;
//     bool max_num_fl = true;                                 // флаг достижения максимально возможного промежуточного числа-из-индексов

//     while(max_num_fl)
//     {
//         max_num_fl = increase_indx_num(indx_num);           // увеличиваем промежуточное число от 0000000000 -> 9876543210
//         get_pandigital_num(pandigital_num, indx_num);       // вычисляем очередное пан-цифровое число
//         if(is_sub_str_div(pandigital_num))                  // пан-цифровое число обладает свойством делимости подстрок
//             answ += get_num(pandigital_num);
//     }

//     printf("%llu", answ);

// 	return 0;
// }
