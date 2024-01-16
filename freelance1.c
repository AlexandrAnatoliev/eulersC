// freelance1.c
// программа для решения кубических уравнений вида:
// 1.81 * x^3 + 7.32 * x^2 - 11.5 * x + 340 = 0

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define LEN_ARR 1000

long long get_NOD(long long num1, long long num2)
// функция определяющая наибольший общий делитель двух чисел
// параметры:	num1    - число 1
//              num2    - число 2
// return:      наибольший общий делитель двух чисел
{
    if (num1 < 0)                                               // обработка отрицательных чисел
        num1 *= -1;
    if (num2 < 0)
        num2 *= -1;

    while (num1 && num2)                                        // пока ни одно из чисел не равно нулю
    {
        if (num1 >= num2)
            num1 %= num2;
        else
            num2 %= num1;
    }
    return (num1 > num2) ? num1 : num2;                         // возвращает максимальное
}

int get_divs(int arr[], int num)
// функция для определения делителей числа
// параметры:	arr[]           - массив для хранения делителей числа
//              num             - раскладываемое число
{
    if (num < 0)                                                // обработка отрицательных чисел
        num *= -1;

    int div_max = sqrt(num) + 1;
    int cnt = 0;
    int div = 1;

    while (cnt < LEN_ARR - 2 && div < div_max + 1)
    {
        if (num % div == 0)
        {
            arr[cnt++] = div;
            arr[cnt++] = num / div;
        }
        div++;
    }

    return 0;
}

bool is_answer(int arr[], long long D, long long A)
// функция для определения наличия ответа методом подстановки
// параметры:	arr[]   - массив с коэффициентами функции
//              d       - подставляемое значение делителя свободного коэффициента d
//              a       - подставляемое значение делителя старшего коэффициента a
// return:      true    - есть ответ
{
    return (arr[0] * D * D * D) / (A * A * A) + (arr[1] * D * D) / (A * A) + arr[2] * D / A + arr[3] == 0;
}

int print_answ(int answ_ar[], bool *answ_fl, long long D, long long A)
// функция для вывода ответа на экран
// параметры:	answ_ar[]   - массив для хранения дробных ответов
//              answ_ar[0]  - число сохраненых чисел
//              answ_ar[1]  - числитель дроби ответа
//              answ_ar[2]  - знаменатель дроби ответа
//              answ_fl     - флаг наличия ответа
//              D           - подставляемое значение делителя свободного коэффициента d
//              A           - подставляемое значение делителя старшего коэффициента a
// return:                  - количество вычисленных ответов
{
    int cnt = answ_ar[0];
    int nod = get_NOD(D, A);

    D /= nod;                                                   // сокращаем дробь
    A /= nod;

    for (int i = 1; i < cnt; i += 2)
        if (D == answ_ar[i] && A == answ_ar[i + 1])
            return cnt;                                         // такой ответ уже был

    answ_ar[cnt + 1] = D;                                       // заносим ответ в массив: числитель и знаменатель
    answ_ar[cnt + 2] = A;
    cnt += 2;
    answ_ar[0] = cnt;

    if (*answ_fl == false)
    {
        printf("\nAnswers:\n\n");                               // шапка перед первым ответом
        *answ_fl = true;
    }

    printf("x%d = %lld/%lld\n", (cnt - 1) / 2, D, A);           // выводим ответы как дроби
    return cnt;
}

int main(void)
{
    int d_arr[LEN_ARR] = {0};                                   // массив для хранения делителей свободного члена D
    int a_arr[LEN_ARR] = {0};                                   // массив для хранения делителей старшего коэффициента A
    char simb[] = {'A', 'B', 'C', 'D'};                         // названия коэффициентов
    float fl_arr[4] = {0};                                      // коэффициенты уравнения A*x^3 + B*x^2 + C*x + D = 0
    int int_arr[4] = {0};
    bool answ_fl = false;                                       // флаг наличия ответа
    int answ_arr[LEN_ARR] = {0};                                // массив для хранения ответов
    long long nod = 1;

    printf("\nInput coefficients the math equation: A*x^3 + B*x^2 + C*x + D = 0\n\n");

    for (int i = 0; i < 4; i++)                                 // ввод коэффициентов
    {
        printf("%c: ", simb[i]);
        scanf("%f", &fl_arr[i]);
    }

    for (int i = 0; i < 4; i++)                                 // изменяем коэффициенты float -> int: 1.81 -> 1810
        int_arr[i] = round(fl_arr[i] * 1000);

    nod = get_NOD(int_arr[0], int_arr[1]);                      // находим наибольший общий делитель
    nod = get_NOD(nod, int_arr[2]);
    nod = get_NOD(nod, int_arr[3]);

    for (int i = 0; i < 4; i++)                                 // сокращаем коэффициенты
        int_arr[i] /= nod;

    get_divs(a_arr, int_arr[0]);                                // делители старшего коэффициента
    get_divs(d_arr, int_arr[3]);                                // делители свободного члена

    if (is_answer(int_arr, 0, 1))                               // проверяем ноль
        print_answ(answ_arr, &answ_fl, 0, 1);

    int i = 0;
    while (d_arr[i] != 0)                                       // перебираем числители
    {
        int j = 0;
        while (a_arr[j] != 0)                                   // и знаменатели
        {
            if (is_answer(int_arr, d_arr[i], a_arr[j]))         // подставляем положительные дроби
                print_answ(answ_arr, &answ_fl, d_arr[i], a_arr[j]);

            if (is_answer(int_arr, d_arr[i] * (-1), a_arr[j]))  // и отрицательные
                print_answ(answ_arr, &answ_fl, d_arr[i] * (-1), a_arr[j]);
            j++;
        }
        i++;
    }

    if (!answ_fl)
        printf("\nNot answers");

    printf("\n");

    return 0;
}