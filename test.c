#include <stdio.h>
#include <stdbool.h>
#include <time.h> 													// for clock_t, clock(), CLOCKS_PER_SEC

char get_arr(char arr_arg[], int num_arg, int div_arg)
// раскладывает число на цифры по заданному основанию и заносит их в массив
// параметры:
// char arr_arg[]: массив, в который будет сохраняться разложенное число;
// int num_arg: раскладываемое число;
// int div_arg: основание, по которому раскладывается число
// return: количество цифр в числе
{
	char cnt = 0;
	while (num_arg)									//раскладываем число на цифры и заносим в массив
	{
		arr_arg[++cnt] = num_arg % div_arg;
		num_arg /= div_arg;
	}
	arr_arg[0] = cnt;								//заносим количество цифр в числе
	return cnt;
}

bool is_palindrom(char arr_arg[])
//true - если число палиндром
{
	char ptr1 = 1;									//указатель(индекс) на первое число
	char ptr2 = arr_arg[0];							//указатель(индекс) на последнее число
	while (ptr1 < ptr2)
	{
		if (arr_arg[ptr1] == arr_arg[ptr2])
		{
			ptr1++;
			ptr2--;
		}
		else
			return false;
	}
	return true;
}

int main(void)
{
	double time_spent = 0.0; 										// для хранения времени выполнения кода
	clock_t begin = clock(); 										// СТАРТ таймера

	char arr_bin[22] = { 0 };						//массив для хранения цифр числа в 2-ичном виде
	//первая цифра - количество цифр в занесенном числе, 1000000 -> 21-значное число в 2-ичной системе
	char arr_dec[7] = { 0 };						//массив для хранения цифр числа в 10-тичном виде
	int answ = 0;

	for (int num = 1; num < 1000000; num++)
	{
		get_arr(arr_dec, num, 10);
        get_arr(arr_bin, num, 2);
		if (is_palindrom(arr_dec) && is_palindrom(arr_bin))
		{
			answ += num;
			printf("%d\n", num);
		}
			
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent);	// выводим результат и время работы программы
	return 0;
}
