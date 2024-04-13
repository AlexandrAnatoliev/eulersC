// euler37c - Укорачиваемые простые числа

// Число 3797 обладает интересным свойством. Будучи само по себе простым числом, из него можно последовательно выбрасывать цифры слева направо,
// число же при этом остается простым на каждом этапе: 3797, 379, 37, 3.
// Найдите сумму единственных (первых?) одиннадцати простых чисел, из которых можно выбрасывать числа как справа налево, так и слева направо,
// но числа при этом останутся простыми.
// ПРИМЕЧАНИЕ: числа 2, 3, 5, 7 таковыми не считаются.

#include <stdio.h>
#include <stdbool.h> 																// для красоты кода использую bool
#include <math.h>	 																// для использовании функции sqrt()
#include <time.h>	 																// for clock_t, clock(), CLOCKS_PER_SEC
#include <stdlib.h>	 																// для calloc() и free()

#define STEP_ARR 100000

void *my_realloc(char *arr, int *len_arr, int len_add);
int note_prime_arr(char prime_arr[], int len_arr, int start, int finish);
bool is_composite(char prime_arr[], int len_arr, int num);
int note_composite(char prime_arr[], int len_arr, int prime, int start, int finish);
bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);
bool del_right_num(char prime_arr[], int num);
bool del_left_num(char prime_arr[], int num);

int main(void)
{
	double time_spent = 0.0; 														// для хранения времени выполнения кода
	clock_t begin = clock(); 														// СТАРТ таймера

	int len_arr = STEP_ARR; 														// первоначальная длина массива
	int answ = 0, cnt = 0, num = 10;

	char *prime_arr = calloc(len_arr, sizeof(char)); 								// массив для хранения простых и составных чисел

	note_prime_arr(prime_arr, len_arr, 2, len_arr); 								// заполняем массив простыми и составными числами

	while (cnt < 11)
	{
		if (num >= len_arr) 														// увеличиваем при необходимости массив с простыми числами
		{
			int past_len = len_arr;												 	// сохраняем изначальную длину массива
			prime_arr = my_realloc(prime_arr, &len_arr, num - len_arr + STEP_ARR);	// увеличиваем массив (len_arr  увеличивается в функции!)
			note_prime_arr(prime_arr, len_arr, past_len, len_arr);					// отмечаем в добавленной части массива составные числа
		}

		if (prime_arr[num]) 								// пропускаем составные числа
		{
			num++;
			continue;
		}

		else 												// проверяем простые на соответствие условиям задания
		{
			if (del_right_num(prime_arr, num) && del_left_num(prime_arr, num))
			{
				answ += num;
				cnt++;
			}
			num++;
		}
	}

	free(prime_arr);										// освобождаем место

	clock_t end = clock();									// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 	// выводим результат и время работы программы
	return 0;
}

void *my_realloc(char *arr, int *len_arr, int len_add)
// Функция увеличивает размер массива
// Параметры:	arr[]   - массив с ранее вычисленными составными числами
//              len_arr - старая длина массива
//              len_add - на сколько увеличиваем массив
// return:      указатель на увеличенный массив
{
	char *new_arr = calloc(*len_arr + len_add, sizeof(char));	// создаем увеличенный массив

	if (new_arr == NULL)
	{
		printf("my_realloc: функция не смогла выделить место под массив");
		return arr;
	}

	for (int i = 0; i < *len_arr; i++)
		new_arr[i] = arr[i]; 									// копируем данные в новый массив из старого

	free(arr); 													// освобождаем память От старого массива

	arr = new_arr;		 										// присваиваем адрес нового массива
	*len_arr += len_add; 										// перезаписываем длину массива

	return arr;
}

int note_prime_arr(char prime_arr[], int len_arr, int start, int finish)
// Функция, которая отмечает простые и составные числа в массиве
// Параметры:	prime_arr[]	- массив с ранее вычисленными простыми и составными числами
//              len_arr     - длина массива
//              start       - начальное число
//              finish      - конечное число
{
	prime_arr[0] = 1; 													// числа 0 и 1 не считаются простыми
	prime_arr[1] = 1;

	// отмечаем составные числа на основе ранее найденных простых
	for (int num = 2; num < start; num++)
		if (!prime_arr[num])											// если число не отмечено составным (простое)
			note_composite(prime_arr, len_arr, num, start, finish); 	// отмечаем составные числа, кратные простому

	// ищем новые простые числа и отмечаем составные
	for (int num = start; num < finish; num++)
	{
		// если число не отмечено составным -> проверяем число -> если число простое
		if (!prime_arr[num] && !is_composite(prime_arr, len_arr, num))
			note_composite(prime_arr, len_arr, num, start, finish); 	// отмечаем составные числа, кратные простому
	}

	return 0;
}

bool is_composite(char prime_arr[], int len_arr, int num)
// Функция для определения составного числа
// Параметры:	prime_arr[]       	- массив с ранее вычисленными составными числами
//              prime_arr[num] = 0	- число простое!
//              prime_arr[num] = 1	- число составное!
//              len_arr             - длина массива
//              num                 - проверяемое число
// return:      true                - если число составное!
{
	if (more_limit("is_composite()", "num", num, "len_arr", len_arr)) 
		return false;							// проверяем выход за пределы массива

	int div_max = sqrt(num) + 1; 				// выносим вычисление квадратного корня из цикла for

	for (int div = 2; div < div_max; div++) 	// чтобы он не вычислялся каждую итерацию цикла
	{
		if (!prime_arr[div] && !(num % div)) 	// пропускаем составные делители и срабатываем при num % i == 0
			return true;
	}

	return false;
}

int note_composite(char prime_arr[], int len_arr, int prime, int start, int finish)
// Функция, которая отмечает составные числа в массиве
// параметры:	prime_arr[]			- массив с ранее вычисленными составными числами
//              prime_arr[num] = 0	- число простое!
//              prime_arr[num] = 1	- число составное!
//              prime               - простое число, служит шагом
//              finish              - конечный индекс в массиве
{
	if (more_limit("note_composite()", "prime", prime, "len_arr", len_arr)) 
		return 0;															// проверка на выход числа за пределы массива

	if (more_limit("note_composite()", "start", start, "len_arr", len_arr))
		return 0;

	if (more_limit("note_composite()", "finish", finish, "len_arr", len_arr))
		return 0;

	if (more_limit("note_composite()", "start", start, "finish", finish))
		return 0;

	start = (start > prime) ? start + (prime - start % prime) : 2 * prime; 	// первое число - простое, не отмечаем его

	for (int i = start; i < finish; i += prime)
		prime_arr[i] = 1; 													// отмечаем составные числа

	return 0;
}

bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция, которая определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
	if (input_value > limit_value) 											// обрабатываем превышение
	{
		printf("%s: %s = %d больше %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
		return true;
	}

	return false;
}

bool del_right_num(char prime_arr[], int num)
// Функция, которая откидывает числа справа по одному, проверяет простые ли они
// Параметры:	prime_arr[]	- массив простых чисел (0 - простое)
//				num 		- проверяемое число
// return:		true 		- если все числа простые, иначе - false
{
	while (num)
	{
		if (prime_arr[num])		// составное число
			return false;

		num /= 10;
	}

	return true;
}

bool del_left_num(char prime_arr[], int num)
// Функция, которая откидывает числа слева по одному, проверяет простые ли они
// Параметры:	prime_arr[]	- массив простых чисел (0 - простое)
//				num 		- проверяемое числоо
// return:		true 		- если все числа простые, иначе - false
{
	int div = 1;
	while (num > 10 * div) 	// определяем порядок числа
		div *= 10;

	for (num, div; div > 0; num %= div, div /= 10)
		if (prime_arr[num]) 	// составное число
			return false;

	return true;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <math.h>									//для работы функции sqrt()
// #include <time.h> 											// for clock_t, clock(), CLOCKS_PER_SEC

// bool is_simple(int num_arg)
// //функция принимает число и возвращает true - если число простое
// {
// 	int i_arg = sqrt(num_arg) + 1;                  //выносим вычисление квадратного корня из цикла for

// 	for (int i = 2; i < i_arg; i++)                 //чтобы он не вычислялся каждую итерацию цикла
// 	{
// 		if (num_arg % i == 0)
// 			return false;
// 	}
// 	return true;
// }

// bool del_right_num(char arr_arg[], int num_arg)
// // откидывает числа справа по одному, проверяет простые ли они
// // параметры:	char arr_arg[]: массив простых чисел
// //				int num_arg: проверяемое число
// // return:		true - если все числа простые, иначе - false
// {
// 	while (num_arg)
// 	{
// 		if (arr_arg[num_arg])
// 			num_arg /= 10;
// 		else
// 			return false;
// 	}
// 	return true;
// }

// char get_dec(char arr_arg[], int num_arg)
// //раскладывает число на цифры в десятичном формате и заносит их в массив, возвращает количество цифр в числе
// {
// 	char cnt = 0;
// 	while (num_arg)											//раскладываем число на цифры и заносим в массив
// 	{
// 		arr_arg[++cnt] = num_arg % 10;
// 		num_arg /= 10;
// 	}
// 	arr_arg[0] = cnt;										//заносим количество цифр в числе
// 	return cnt;
// }

// bool del_left_num(char arr_arg[], int num_arg)
// // откидывает числа слева по одному, проверяет простые ли они
// // параметры:	char arr_arg[]: массив простых чисел
// //				int num_arg: проверяемое число
// // return:		true - если все числа простые, иначе - false
// {
// 	char arr[7] = { 0 };									//пока проверяю цифры до 1000000
// 	get_dec(arr, num_arg);
// 	int cnt = arr[0];
// 	int num;
// 	int pow_ten[] = {1,10,100,1000,10000,100000,100000};	//массив значений 10^i
// 	for (int i = cnt; i >= 1; i--)
// 	{
// 		num = 0;
// 		for (int j = i; j >= 1; j--)
// 			//num += arr[j] * pow_ten[j-1];
// 			num += arr[j] * (int)round(pow((float)10, (float)(j - 1)));

// 		if (!arr_arg[num])									//arr[num] == 0 - число не является простым
// 			return false;
// 	}
// 	return true;
// }

// int main(void)
// {
// 	double time_spent = 0.0; 								// для хранения времени выполнения кода
// 	clock_t begin = clock(); 								// СТАРТ таймера

// 	static char prime_arr[1000000] = { 0 };					//массив[простое число] = 1 - static писать обязательно!
// 	int answ = 0;
// 	int cnt = 0;
// 	for (int i = 2; i < 1000000; i++)						//заполняем массив простыми числами
// 	{
// 		if (is_simple(i))
// 			prime_arr[i] = 1;
// 	}

// 	while (cnt < 11)
// 	{
// 		for (int num = 11; num < 1000000; num++)
// 		{
// 			if (del_right_num(prime_arr, num) && del_left_num(prime_arr, num))
// 			{
// 				answ += num;
// 				cnt++;
// 			}
// 		}
// 	}

// 	clock_t end = clock();								  	// СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent);	// выводим результат и время работы программы

// 	return 0;
// }
