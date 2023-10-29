// euler37c - Укорачиваемые простые числа

// Число 3797 обладает интересным свойством. Будучи само по себе простым числом, из него можно последовательно выбрасывать цифры слева направо,
// число же при этом остается простым на каждом этапе: 3797, 379, 37, 3.
// Найдите сумму единственных (первых?) одиннадцати простых чисел, из которых можно выбрасывать числа как справа налево, так и слева направо, 
// но числа при этом останутся простыми.
// ПРИМЕЧАНИЕ: числа 2, 3, 5, 7 таковыми не считаются. 


#include <stdio.h>
#include <stdbool.h>
#include <math.h>									//для работы функции sqrt()

bool is_simple(int num_arg)
//функция принимает число и возвращает true - если число простое
{
	int i_arg = sqrt(num_arg) + 1;                  //выносим вычисление квадратного корня из цикла for

	for (int i = 2; i < i_arg; i++)                 //чтобы он не вычислялся каждую итерацию цикла
	{
		if (num_arg % i == 0)
			return false;
	}
	return true;
}

bool del_right_num(char arr_arg[], int num_arg)
// откидывает числа справа по одному, проверяет простые ли они
// параметры:	char arr_arg[]: массив простых чисел
//				int num_arg: проверяемое число
// return:		true - если все числа простые, иначе - false
{
	while (num_arg)
	{
		if (arr_arg[num_arg])
			num_arg /= 10;
		else
			return false;
	}
	return true;
}

char get_dec(char arr_arg[], int num_arg)
//раскладывает число на цифры в десятичном формате и заносит их в массив, возвращает количество цифр в числе
{
	char cnt = 0;
	while (num_arg)											//раскладываем число на цифры и заносим в массив
	{
		arr_arg[++cnt] = num_arg % 10;
		num_arg /= 10;
	}
	arr_arg[0] = cnt;										//заносим количество цифр в числе
	return cnt;
}

bool del_left_num(char arr_arg[], int num_arg)
// откидывает числа слева по одному, проверяет простые ли они
// параметры:	char arr_arg[]: массив простых чисел
//				int num_arg: проверяемое число
// return:		true - если все числа простые, иначе - false
{
	char arr[7] = { 0 };									//пока проверяю цифры до 1000000
	get_dec(arr, num_arg);
	int cnt = arr[0];
	int num;
	int pow_ten[] = {1,10,100,1000,10000,100000,100000};	//массив значений 10^i
	for (int i = cnt; i >= 1; i--)
	{
		num = 0;
		for (int j = i; j >= 1; j--)
			num += arr[j] * pow_ten[j-1];

		if (!arr_arg[num])									//arr[num] == 0 - число не является простым
			return false;
	}
	return true;
}

int main(void)
{
	static char prime_arr[1000000] = { 0 };					//массив[простое число] = 1 - static писать обязательно!
	int answ = 0;
	int cnt = 0;
	for (int i = 2; i < 1000000; i++)						//заполняем массив простыми числами
	{
		if (is_simple(i))
			prime_arr[i] = 1;
	}
	
	while (cnt < 11)
	{
		for (int num = 11; num < 1000000; num++)
		{
			if (del_right_num(prime_arr, num) && del_left_num(prime_arr, num))
			{
				answ += num;
				cnt++;
			}
		}
	}
	printf("%d", answ);										//748317

	return 0;	
}
