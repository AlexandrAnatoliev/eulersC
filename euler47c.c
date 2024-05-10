// euler47c - Различные простые множители

// Первые два последовательные числа, каждое из которых имеет два отличных друг от друга простых множителя:

// 14 = 2 × 7
// 15 = 3 × 5

// Первые три последовательные числа, каждое из которых имеет три отличных друг от друга простых множителя:

// 644 = 2² × 7 × 23
// 645 = 3 × 5 × 43
// 646 = 2 × 17 × 19.

// Найдите первые четыре последовательных числа, каждое из которых имеет четыре отличных друг от друга простых множителя. 
// Каким будет первое число?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>								        // для работы функции sqrt()

#define LEN_ARR 200000                                  // длина массивов - зависит от размера искомого числа

text_t is_simple(char prime_ar[], int num)
// функция принимает число и возвращает true - если число простое
// параметры:	prime_ar[]  - массив с ранее вычисленными простыми числами
//              num         - проверяемое число    
// return:      true        - если число простое
{
	int div_max = sqrt(num) + 1;                        // выносим вычисление квадратного корня из цикла for

	for (int div = 2; div < div_max; div++)             // чтобы он не вычислялся каждую итерацию цикла
	{
		if (prime_ar[div] && !(num % div))              // пропускаем составные делители и срабатываем при num % i == 0
			return false;
	}

	return true;
}

int add_primes(char prime_ar[], int len, int value)
// функция проверяет статус чисел "простое/составное" и записывает в массив
// параметры:	prime_ar[]  - массив с ранее вычисленными простыми числами
//              len         - количество чисел в массиве для которых уже определен сатус: простое/составное
//              value       - количество чисел, статус которых нуэжно дополнительно определить
// return:      value       - количество занесенных в массив чисел
{
    for(int i = len + 1; i < (len + 1 + value); i++)    // еще ноль в массиве
        prime_ar[i] = is_simple(prime_ar, i);
    
    return value;
}


int count_prime_factor(char prime_ar[], int num, int cnt_break, int *len_prime_arr)
// функция раскладывает число на простые множители и считает их
// параметры:	prime_ar[]      - массив с ранее вычисленными простыми числами
//              num             - раскладываемое число 
//              cnt_break       - количество множителей, при котором можно прервать вычисление
//              *len_prime_arr  - указатель на количество уже определенных чисел   
// return:                      - количество простых множителей
{
    char factor_arr[LEN_ARR] ={0};                      // массив для хранения множителей по индексу
    int cnt = 0;
    int len_pr_arr = *len_prime_arr;
    int div_max;

    div_max = sqrt(num) + 1;                            // выносим вычисление квадратного корня из цикла for
	while(num != 1)
    {
        
        for (int div = 2; div <= div_max; div++)             
	    {
		    if(div >= len_pr_arr)                       // если необходимо
            {
                add_primes(prime_ar, len_pr_arr, 1000); // определяем статус еще 1000 чисел
                len_pr_arr += 1000;
                *len_prime_arr = len_pr_arr;
            }

            if (prime_ar[div] && !(num % div))          // пропускаем составные делители и срабатываем при num % i == 0
            {
                if(!factor_arr[div])                    // factor_arr[div] == 0 не было такого множителя
                {
                    factor_arr[div] = 1;
                    cnt++;  
                }
                num /= div;
                break;                               
            }
            if(div == div_max)                          // если больше не делится
                return ++cnt;	                        
	    }
    if(cnt >= cnt_break)
        return cnt_break;
    }
    return cnt;
}

text_t is_diff_numbers(char prime_ar[], char factors_arr[], int add_num)
// функция раскладывает число на множители (2^2 преобразует в 4)
// параметры:   prime_ar[]      - массив с ранее вычисленными простыми числами
//              factors_arr[]   - массив в который заносятся множители числа
//              add_num         - добавляемое в массив число 
// return:      true            - если множители не совпадают
{
    char f_arr[LEN_ARR] ={0};                           // массив для хранения множителей по индексу
    int factor;                                         // множитель (для преобразований 2^2 -> 4)

	while(add_num != 1)                                 // раскладываем число на множители
    {
        for (int div = 2; div <= add_num; div++)             
	    {
		    if (prime_ar[div] && !(add_num % div))      // пропускаем составные делители и срабатываем при num % i == 0
            {
                f_arr[div]++;                           // увеличиваем степень числа
                add_num /= div;
                break;                               
            }	
	    }
    }

    for(int fact = 0; fact < LEN_ARR; fact++)              
    {
        if(f_arr[fact])                                 // множитель из массива
        {                                               // возводим в степень, если нужно
            factor = (f_arr[fact] == 1) ? fact : pow(fact, f_arr[fact]);
            if(factors_arr[factor])                     // если такой множитель уже был
                return false;
            else
                factors_arr[factor] = 1;                // переносим множитель в общий массив с множителями
        }            
    }
    return true;
}

int main(void)
{
    int answ = 9;                                       // первое составное нечетное число
    int cnt_consecutive  = 0;
    
    static char prime_arr[LEN_ARR] = { 0 };		        // массив[простое число] = 1 - static писать обязательно!
    
    prime_arr[1] = 1;                                   
    prime_arr[2] = 1;
    int len_prime_arr = 2;                              // в массиве определен статус двух чисел

    len_prime_arr += add_primes(prime_arr, 2, 1000);    // определяем статус первых 1000 чисел в массиве

    
    while (cnt_consecutive < 4)
    {
        if(count_prime_factor(prime_arr, answ, 5, &len_prime_arr) == 4)
            cnt_consecutive++;
        else
            cnt_consecutive = 0;
        answ++;
    }

    int answ2 = answ - 4;                                   // проверка
    char factors_ar[LEN_ARR] = {0};                         // массив для хранения множителей всех 4 чисел

    for(int i = 0; i < 4; i++)
        if(is_diff_numbers(prime_arr, factors_ar, answ2))   // если в массиве таких множетелей нет
            answ2++;

    if(answ2 == answ)
        printf("%d\n", answ - 4);                           // 134043


	return 0;	
}
