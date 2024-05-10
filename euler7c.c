//euler7c - 10001-е простое число
//Выписав первые шесть простых чисел, получим 2, 3, 5, 7, 11 и 13. Очевидно, что 6-е простое число - 13.
//Какое число является 10001-м простым числом?

// #include <stdio.h>
// #include <stdbool.h>
// #include <math.h>
// #include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

// #define LEN_ARR 200000                                      // длина массивов - зависит от размера искомого числа

// bool is_prime(char prime_ar[], int num)
// // функция принимает число и возвращает true - если число простое
// // параметры:	prime_ar[]  - массив с ранее вычисленными простыми числами
// //              num         - проверяемое число    
// // return:      true        - если число простое
// {
// 	int div_max = sqrt(num) + 1;                            // выносим вычисление квадратного корня из цикла for

// 	for (int div = 2; div < div_max; div++)                 // чтобы он не вычислялся каждую итерацию цикла
// 	{
// 		if (prime_ar[div] && !(num % div))                  // пропускаем составные делители и срабатываем при num % i == 0
// 			return false;
// 	}
// 	return true;
// }

// int main(void)
// {                           
//     double time_spent = 0.0;                                // для хранения времени выполнения кода
//     clock_t begin = clock();                                // СТАРТ таймера

//     static char prime_arr[LEN_ARR] = { 0 };		            // массив[простое число] = 1 - static писать обязательно!                                  
//     prime_arr[2] = 1;
//     int count = 1;                                          // определили одно простое число в массиве - 2
//     int num = 2;

//     while (count < 10001)    
//     {
//         num++;                                              // перебираем числа
//         if (is_prime(prime_arr, num))
//         {                               
//             prime_arr[num] = 1;                             // отмечаем число как простое в массиве
//             count++;
//         }
//     }
    
//     clock_t end = clock();                                  // СТОП таймера
//     time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

//     printf("answer = %d runtime = %f\n", num, time_spent);  // выводим результат и время работы программы
//     return 0;  
// }

// вариант через Решето Эрастосфена

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>                                               // for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 200000                                          // длина массивов - зависит от размера искомого числа

text_t is_composite(char comp_arr[], int num)
// функция принимает число и возвращает true - если число составное
// параметры:	comp_arr[]          - массив с ранее вычисленными составными числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              num                 - проверяемое число    
// return:      true                - если число составное!
{
	int div_max = sqrt(num) + 1;                                // выносим вычисление квадратного корня из цикла for

	for (int div = 2; div < div_max; div++)                     // чтобы он не вычислялся каждую итерацию цикла
	{
		// пропускаем составные делители и срабатываем при num % i == 0, пропускаем число 2
        if (!comp_arr[div] && !(num % div) && (num != 2))   
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
    int cnt = 0;
    int shift = (start % step == 0) ? 0 : step - (start % step);// смещение индекса start
    start += shift;                                             // первое составное число

    for(int i = start; i < finish; i += step)
    {
        if(!comp_arr[i])                                        // если еще не отмечено
        {
            comp_arr[i] = 1;                                    // отмечаем составные числа
            cnt++;                                              // и считаем их
        }
    }
                                               
    return cnt;
}

int get_prime(char comp_arr[], int number, int start, int finish)
// функция считает количество простых чисел и возвращает значение простого числа из отрезка массива по его номеру
// параметры:	comp_arr[]          - массив с ранее вычисленными простыми числами
//              comp_arr[num] = 0   - число простое!
//              comp_arr[num] = 1   - число составное!
//              number              - порядковый номер простого числа
//              start               - начальное место в массиве
//              finish              - конечное место в массиве    
// return:                          - значение простого числа
{
    int answ = 0;
    int cnt = 0;

    for(int i = start; i < finish; i++)                         // перебираем массив
    {
        if(!comp_arr[i])                        
            cnt++;                                              // считаем простые числа
        if(cnt == number)                                       // когда дошли до искомого счета
        {
            answ = i;                                           // индекс в массиве является искомым числом
            break;
        }    
    }
    return answ;
}

int main(void)
{                           
    double time_spent = 0.0;                                    // для хранения времени выполнения кода
    clock_t begin = clock();                                    // СТАРТ таймера

    static char composit_arr[LEN_ARR] = { 0 };		            // массив[состаное число] = 1 - static писать!                                  
    int cnt_prime = 0;                                          // счетчик количества простых чисел в массиве
    int past_cnt_prime;                                         // сохраняем значение счетчика предыдущей итерации
    int cnt_comp = 0;                                           // счетчик количества составных чисел
    int answ;
    int start = 0;                                              // добавляем значения в массиве по 1000
    int finish = 1000;
    int step_max;

    for(int num = 2; num < 1000; num++)                         // определяем статус первых 1000 чисел
    {
        if(is_composite(composit_arr, num))
        {
            composit_arr[num] = 1;
            cnt_comp++;
        }
    }

    cnt_prime = 998 - cnt_comp;                                 // от 2 до 999 -> 998 чисел
    
    while(cnt_prime < 10001)
    {
        past_cnt_prime = cnt_prime;                             // сохраняем значение счетчика предыдущей итерации
        start += 1000;                                          // добавляем значения в массиве по 1000
        finish += 1000;
        cnt_comp = 0;
        step_max = finish / 2;                                  // максимальное значение шага
        
        for(int step = 2; step < step_max; step++)
        {
            if(!composit_arr[step])                             // числа, делимые на step, в массиве как составные
                cnt_comp += note_composite(composit_arr, step, start, finish);
        }
        
        cnt_prime += (1000 - cnt_comp);                         // вычитаем составные числа, остальные - простые
    }
    
    // 10001 - предыдущее значение счетчика = порядковый номер искомого числа в отрезке массива                                                  
    answ = get_prime(composit_arr, 10001 - past_cnt_prime, start, finish);
    
    clock_t end = clock();                                      // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

    printf("answer = %d runtime = %f\n", answ, time_spent);     // выводим результат и время работы программы
    return 0;  
}