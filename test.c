#include <stdio.h>
#include <stdbool.h>
#include <time.h> 															// for clock_t, clock(), CLOCKS_PER_SEC

bool put_numbers(char arr_arg[], int num_arg)
//сохраняет в массив цифры по индексу
//возвращает false, если в массиве такие цифры уже есть
{
	while (num_arg)
	{
		if (arr_arg[num_arg % 10] == 0)
		{
			arr_arg[num_arg % 10] = 1;
			num_arg /= 10;
		}
		else
			return false;
	}
	return true;
}

bool is_pandigital(int mult_arg1, int mult_arg2, int prod_arg)
//принимает два множителя и произведение, возвращает true если равенство является пан-цифровым
{
	char arr[10] = { 0 };										//массив сохраняющий уже содержащиеся цифры

	if (put_numbers(arr, mult_arg1) == false)					//заносим в массив цифры первого множителя
		return false;
	if (put_numbers(arr, mult_arg2) == false)					//заносим в массив цифры второго множителя
		return false;
	if (put_numbers(arr, prod_arg) == false)					//заносим в массив цифры произведение
		return false;

	if (arr[0])													//если был ноль
		return false;

	for (int i = 1; i < 10; i++)								//проверяем что были все цифры
		if (arr[i] == 0)
			return false;
	return true;
}

bool is_possible(int mult_arg1, int mult_arg2)
//true - возможно есть пан-цифровое равенство, т.е сумма цифр будет равня 9
//счистает количество цифр множителей, варианты: a * bbbb = cccc; aaaa * b = cccc; aa * bbb = cccc; aaa * bb = cccc
{
	if ((mult_arg1 < 10) && (mult_arg2 > 999) || (mult_arg2 < 10) && (mult_arg1 > 999))		//a * bbbb = cccc || aaaa * b = cccc
		return true;
	if ((mult_arg1 > 9) && (mult_arg1 < 100) && (mult_arg2 > 100) && (mult_arg2 < 1000))	//aa * bbb = cccc
		return true;
	if ((mult_arg2 > 9) && (mult_arg2 < 100) && (mult_arg1 > 100) && (mult_arg1 < 1000))	//aaa * bb = cccc
		return true;
	return false;
}

int main(void)
{
	double time_spent = 0.0; 																// для хранения времени выполнения кода
	clock_t begin = clock(); 																// СТАРТ таймера

	int arr[20] = { 0 };
	int cnt = 0;
	int answ = 0;

	for (int mult1 = 0; mult1 < 10000; mult1++)
	{
		for (int mult2 = 0; mult2 < 10000; mult2++)
		{
			if (is_possible(mult1, mult2) && is_pandigital(mult1, mult2, mult1 * mult2))
			{
				bool flag = true;								//проверяем осутствие в массиве такого множителя
				for (int i = 0; i < cnt; i++)
				{
					if (arr[i] == mult1 * mult2)
					{
						flag = false;
						break;
					}
				}
				if (flag)
				{
					answ += mult1 * mult2;						//заносим множитель в массив
					arr[cnt++] = mult1 * mult2;
					printf("%d %d\n", mult1, mult2);
				}
			}
		}
	}
	// printf("%d", answ);

	clock_t end = clock();								  									// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 									// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 						// выводим результат и время работы программы

	return 0;
}
