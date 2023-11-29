// euler42c - Закодированные треугольные числа

// Будем считать n-значное число пан-цифровым, если каждая из цифр от 1 до n используется в нем ровно один раз.
// К примеру, 2143 является 4-значным пан-цифровым числом, а также простым числом.
//
// Какое существует наибольшее n-значное пан-цифровое простое число ?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>											// для работы функции sqrt()

bool is_simple(char ar_arg[], int num_arg)
// функция определяет простое ли число
// параметры:	num_arg		- число
//				ar_arg[]	- массив, уже вычисленных простых чисел
// return:		true		- если число простое
{
	int i_arg = sqrt(num_arg) + 1;							// выносим вычисление квадратного корня из цикла for

	for (int i = 2; i < i_arg; i++)							// чтобы он не вычислялся каждую итерацию цикла
	{
		if (ar_arg[i] && num_arg % i == 0)					// делим только на простые числа (ar_arg[i] == 1)
			return false;
	}
	return true;
}

int put_number(char ar_arg[], int num_arg)
// сохраняет в массив цифры по индексу
// параметры:	num_arg		- число
//				ar_arg[]	- массив, для хранения чисел
// return:					- длина числа

{
	int cnt = 0;
	while (num_arg)
	{
		ar_arg[num_arg % 10] = 1;							// заносим цифру в массив
		num_arg /= 10;
		cnt++;												// считаем длину числа
	}
	return cnt;
}

bool is_pandigital(int num_arg)
// функция для определения пан-цифрового числа
// параметры:	num_arg		- число
// return:		true		- пан-цифровое число
{
	char arr[10] = { 0 };									// массив сохраняющий содержащиеся цифры
	int cnt_num = 0;
	int len_num = put_number(arr, num_arg);					// длина числа
	
	if (arr[0])												// если был ноль 
		return false;

	for (int i = 1; i <= len_num; i++)						// считаем фактически занесенные цифры
		if (arr[i])
			cnt_num++;
	return cnt_num == len_num;								// совпадет, если все цифры занесены один раз
}

int main(void)
{
	int answ;
	static char prime_arr[10000000] = { 0 };				// массив[простое число] = 1 - static писать обязательно!
	
	for (int i = 2; i < 10000000; i++)						// заполняем массив простыми числами
	{
		if (is_simple(prime_arr, i))
			prime_arr[i] = 1;
	}
	
	for (int i = 10000000; i > 10; i--)
		if (prime_arr[i] && is_pandigital(i))
		{
			answ = i;
			break;
		}
			
	printf("%d", answ);										// 7652413

	return 0;
}