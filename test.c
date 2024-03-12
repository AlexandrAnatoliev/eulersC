#include <stdio.h>
#include <stdbool.h>                                                //для красоты кода использую bool
#include <math.h>                                                   //для использовании функции sqrt()
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 15000                                               //принял длину масиива опытным путем

bool is_simple(int num_arg)
//функция принимает число и возвращает true - если число простое
{
    int i_arg = sqrt(num_arg) + 1;                                  //выносим вычисление квадратного корня из цикла for

    for (int i = 2; i < i_arg; i++)                                 //чтобы он не вычислялся каждую итерацию цикла
    {
        if (num_arg % i == 0)
            return false;
    }
    return true;
}
int main(void)
{
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера
    char arr[LEN_ARR] = {0};                                        //массив для записи простых чисел
    int n, answ_a, answ_b, a, b, cnt, answ = 1, cnt_max = 0;

    //вычисляю простые числа до 15000 один раз и заношу их массив по индексу
    for (int i = 1; i < LEN_ARR; i++)                               //если arr[indx] = 1 => indx - простое число
        arr[i] = is_simple(i);

    //в цикле перебираю все возможные коэффициенты
    for (a = -1000; a < 1000; a++)
    {
        for (b = -1000; b < 1000; b++)
        {
            cnt = 0;
            n = 0;
            for(n = 0; n < 100; n++)                                //предположил, что простых чисел будет не более ста
            {
                answ = (n * n) + (a * n) + b;                       //проверяем формулу
                if (answ < 0 || arr[answ] == 0)                     //простое число не может быть отрицательным
                    break;                                          //прервем проверку формулы если встретилось число не являющееся простым

                cnt++;
            }

            if (cnt > cnt_max)                                      //обновляем значения коэффициентов
            {
                cnt_max = cnt;
                answ_a = a;
                answ_b = b;
            }
        }
    }

    // printf("cnt = %d\na*b = %d", cnt_max - 1, answ_a*answ_b);
    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("Ответ = %d время = %f\n", answ_a*answ_b, time_spent);    // выводим результат и время работы программы
    return 0;
}