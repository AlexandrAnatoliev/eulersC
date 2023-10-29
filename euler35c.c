// euler35c - Круговые простые числа

//Число 197 называется круговым простым числом, потому что все перестановки его цифр с конца в начало являются простыми числами : 197, 719 и 971.
//
//Существует тринадцать таких простых чисел меньше 100 : 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79 и 97.
//
//Сколько существует круговых простых чисел меньше миллиона ?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>													//для работы функции sqrt()

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

int len_num(int num_arg)
//возвращает количество цифр в числе
{
	int cnt = 0;
	int num = num_arg;
	while (num)
	{
		num /= 10;
		cnt++;
	}
	return cnt;
}

int main(void)
{
	static char prime_arr[1000000] = { 0 };								//массив[простое число] = 1 - static писать обязательно!
	int num = 0;
	int num2 = 0;
	int answ = 0;
	int len = 0;

	for (int i = 2; i < 1000000; i++)									//заполняем массив простыми числами
	{
		if (is_simple(i))
			prime_arr[i] = 1;
	}

	for (int i = 2; i < 1000000; i++)
	{
		if (prime_arr[i])
		{
			num = i;													//num = 197
			bool flag = true;
			len = len_num(i) - 1;										//количество перестановок чисел
			
			for (int j = 0; j < len; j++)								//делаем 2 перестановки
			{
				num2 = (num % 10) * (int)round(pow(10,len)) + num / 10;	//(7 * 10^2) + 19 = 719
				if (prime_arr[num2])									//если 719 - простое число
					num = num2;											//num = 719
				else
				{
					flag = false;
					break;
				}
			}
			if (flag)
				answ++;				
		}
	}
	printf("%d\n", answ);												//55

	return 0;	
}
