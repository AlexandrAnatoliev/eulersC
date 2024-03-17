// euler29c - Различные степени

// Рассмотрим все целочисленные комбинации a^b для 2 ≤ a ≤ 5 и 2 ≤ b ≤ 5:
//
// 22 = 4, 23 = 8, 24 = 16, 25 = 32
// 32 = 9, 33 = 27, 34 = 81, 35 = 243
// 42 = 16, 43 = 64, 44 = 256, 45 = 1024
// 52 = 25, 53 = 125, 54 = 625, 55 = 3125
// Если их расположить в порядке возрастания, исключив повторения, мы получим следующую последовательность из 15 различных членов :
//
// 4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125
//
// Сколько различных членов имеет последовательность a^b для 2 ≤ a ≤ 100 и 2 ≤ b ≤ 100 ?

#include <stdio.h>
#include <stdbool.h>
#include <time.h> 																// for clock_t, clock(), CLOCKS_PER_SEC

#define BASE 100
#define POW 100

int get_fact(int num);
int pow_num(int arr[], int num, int pow);
int summ_fact(int arr[]);
bool compare_nums(const int arr1[], const int arr2[]);
int nullify_arr(int arr[], int len_arr);
bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
	double time_spent = 0.0; 													// для хранения времени выполнения кода
	clock_t begin = clock(); 													// СТАРТ таймера

	static int arr[BASE * POW][BASE + 1] = {0};																																																										 // без static - ошибка
	const char prime_arr[] = {[2] = 1, [3] = 1, [5] = 1, [7] = 1, [11] = 1, 
							[13] = 1, [17] = 1, [19] = 1, [23] = 1, [29] = 1, 
							[31] = 1, [37] = 1, [41] = 1, [43] = 1, [47] = 1, 
							[53] = 1, [59] = 1, [61] = 1, [67] = 1, [71] = 1, 
							[73] = 1, [79] = 1, [83] = 1, [89] = 1, [97] = 1};	// массив с простыми числами
	int cnt = 0;																																																																	 // счетчик занесенных чисел

	for (int base = 2; base <= BASE; base++) 				// перебираем числа основания
	{
		for (int pow = 2; pow <= POW; pow++) 				// перебираем степени
		{
			int num = base;
			while (num > 1)
			{
				int fact = get_fact(num);	  				// раскладываем число на множители
				pow_num(arr[cnt], fact, pow); 				// и заносим их в массив
				num /= fact;
			}

			summ_fact(arr[cnt]); 							// суммируем номиналы множителей

			bool flag = true;
			for (int j = 0; j < cnt; j++) 					// проверяем нет ли уже такого числа
			{
				if (prime_arr[base]) 						// степени простых чисел - уникальны, пропускаем их
					break;

				if (compare_nums(arr[j], arr[cnt]))			// если такое число уже есть
				{
					nullify_arr(arr[cnt], POW + 1);			// обнуляем массив для дальнейшей перезаписи
					flag = false;							// не заносим число в массив
					break;
				}
			}

			if (flag)
			{
				if (input_more_limit("main()", "cnt", cnt, "BASE * POW", BASE * POW))
					return 1; 								// проверка на невыход за пределы массива
				cnt++;		  								// иначе - заносим в массив
			}
		}
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;	// время работы в секундах

	printf("Ответ = %d время = %f\n", cnt, time_spent); 	// выводим результат и время работы программы
	return 0;
}

int get_fact(int num)
// Функция, которая возвращает множитель числа
// Параметры:	num	- раскладываемое число
// return:			- первый множитель - минимальный делитель числа
{
	for (int fact = 2; fact < num; fact++)
		if (num % fact == 0)
			return fact;	// возвращаем первый делитель числа - минимальный

	return num;				// иначе - само число
}

int pow_num(int arr[], int num, int pow)
// Функция, которая возводит число в степень
// Параметры:	arr - число в виде массива множителей
//				num	- возводимое число (2)
//				pow	- степень (4)
//				arr[2] = 4 - т.е.число является произведением 2 * 2 * 2 * 2
{
	if (input_more_limit("pow_num()", "num", num, "BASE + 1", BASE + 1))	
		return 1;					// проверка на невыход за пределы массива

	arr[num] += pow; 				// количество множителей num
	arr[0] += pow;	 				// общее количество всех множителей
	return 0;
}

int summ_fact(int arr[])
// Функция для подсчета суммы номиналов множителей
// Параметры:	arr[]	- массив
// return:				- сумму индексов массива, в которых есть числа
{
	int cnt = arr[0]; 	// количество множителей в проверяемом массиве
	for (int i = 2; i < POW + 1; i++)
	{
		if (arr[i])
		{
			arr[1] += i;
			cnt -= arr[i];
		}
		if (cnt == 0) 	// все множители учтены
			break;
	}
	return arr[1];
}

bool compare_nums(const int arr1[], const int arr2[])
// Функция для сравнения  массивов
// первый элемент массива - длина, если длины не совпадут, то дальше не проверяется
// Параметры:	arr1	- первый массив
//				arr2	- второй массив
// return:		true 	- одинаковые
{
	int cnt = arr2[0]; 				// количество множителей в проверяемом массиве

	for (int i = 0; i < POW + 1; i++)
	{
		if (arr1[i] != arr2[i])
			return false;

		else if (i > 1) 			// в первой ячейке хранится количество множителей
			cnt -= arr1[i];			// во второй сумма номиналов

		if (cnt == 0) 				// если все множители уже найдены
			break;
	}

	return true;
}

int nullify_arr(int arr[], int len_arr)
// Функция для обнуления массива
// Параметры:	arr[]	- обнуляемый массив
//				len_arr	- длина массива
{
	if (input_more_limit("nullify_arr()", "len_arr", len_arr, "BASE + 1", BASE + 1))
		return 1;							// проверка на невыход за пределы массива

	for (int i = 0; i < len_arr; i++)
		arr[i] = 0;

	return 0;
}

bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
	if (input_value > limit_value) 													// обрабатываем превышение
	{
		printf("%s: %s = %d больше %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
		return true;
	}

	return false;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

// int split_number(unsigned char arr_arg[], int num_arg)
// // принимает указатель на массив и число
// // раскладывает число на отдельные цифры и заносит в массив
// // возвращает число занесенных символов в массив
// {
// 	int cnt = 1;
// 	while (num_arg)
// 	{
// 		if (num_arg % 10 == 0) // заносим нули
// 		{
// 			arr_arg[cnt++] = 0;
// 			num_arg /= 10;
// 		}
// 		else
// 		{
// 			arr_arg[cnt++] = num_arg % 10; // заносим цифры
// 			num_arg /= 10;
// 		}
// 	}
// 	arr_arg[0] = cnt; // длина массива - в первой ячейке
// 	return cnt;
// }

// int mult_num(unsigned char arr_num1_arg[], int num_arg)
// // перемножает числа 1 и 2
// {
// 	int cnt1 = arr_num1_arg[0]; // длина массива1 (первого числа)

// 	unsigned char num2_arr[5] = {0}; // число-массив2 - второе число
// 	split_number(num2_arr, num_arg);
// 	int cnt2 = num2_arr[0];

// 	unsigned char num3_arr[3][255] = {0}; // промежуточный массив для умножения столбиком

// 	unsigned char num = 0;		// переменные для разложения числа 23 -> 3
// 	unsigned char next_num = 0; //									 -> 2

// 	for (int j = 1; j < cnt2; j++)
// 	// перемножаем цифры в числах и заносим в промежуточный массив
// 	{
// 		next_num = 0;
// 		if (j > 1)	// если второй множитель двузначный
// 			cnt1++; // увеличиваем длину числа
// 		for (int i = 1 + j - 1; i < cnt1; i++)
// 		{
// 			// перемножаем цифры
// 			num = arr_num1_arg[i + 1 - j] * num2_arr[j] + next_num;
// 			next_num = num / 10;		   // выделяем десятки
// 			num3_arr[j - 1][i] = num % 10; // и записываем остаток в массив
// 		}

// 		if (next_num)							// если осталось незанесенная цифра
// 			num3_arr[j - 1][cnt1++] = next_num; // заносим ее в массив и увеличиваем длину числа
// 	}

// 	next_num = 0;
// 	for (int i = 1; i < cnt1; i++)
// 	// складываем цифры в промежуточном массиве
// 	{
// 		num = num3_arr[0][i] + num3_arr[1][i] + num3_arr[2][i] + next_num;
// 		arr_num1_arg[i] = num % 10;
// 		next_num = num / 10;
// 	}
// 	if (next_num)
// 		arr_num1_arg[cnt1++] = next_num;

// 	int cnt_check; // уточняем длину массива
// 	for (int i = cnt1 - 2; i < cnt1 + 2; i++)
// 	{
// 		if (arr_num1_arg[i])
// 			cnt_check = i + 1;
// 	}
// 	arr_num1_arg[0] = cnt_check;
// 	return cnt1;
// }

// bool compare_nums(const unsigned char arr_num1_arg[], const unsigned char arr_num2_arg[])
// // сравнивает массивы -> true - одинаковые
// // первый элемент массива - длина, если длины не совпадут, то дальше не проверяется
// {
// 	for (int i = 0; i < 255; i++)
// 		if (arr_num1_arg[i] != arr_num2_arg[i])
// 			return false;
// 	return true;
// }

// int copy_arr(unsigned char arr_num1_arg[], unsigned char arr_num2_arg[])
// // копирует массив 2 в 1
// {
// 	int len_arr = arr_num2_arg[0];
// 	for (int i = 0; i < len_arr; i++)
// 		arr_num1_arg[i] = arr_num2_arg[i];
// 	return 0;
// }

// void nullify_arr(unsigned char arr_num1_arg[], int len_arr_arg)
// // обнуляем массив
// {
// 	for (int i = 0; i < len_arr_arg; i++)
// 		arr_num1_arg[i] = 0;
// }

// int main(void)
// {
// 	double time_spent = 0.0; // для хранения времени выполнения кода
// 	clock_t begin = clock(); // СТАРТ таймера

// 	static unsigned char arr[10000][255] = {0}; // без static - ошибка, первый символ - длина массива
// 	unsigned char num1_arr[255] = {0};			// число-массив1 для вычислений

// 	int a = 100;
// 	int b = 100;
// 	int cnt = 0; // счетчик занесенных чисел

// 	for (int base = 2; base <= a; base++) // перебираем числа основания
// 	{
// 		nullify_arr(num1_arr, 255); // обнуляем массив перед использованием
// 		split_number(num1_arr, base);
// 		for (int pow = 2; pow <= b; pow++) // перебираем степени
// 		{
// 			mult_num(num1_arr, base); // возводим в степень - умножаем число на само себя несколько раз

// 			bool flag = true;
// 			for (int j = 0; j <= cnt; j++)
// 			// проверяем нет ли уже такого числа
// 			{
// 				if (compare_nums(arr[j], num1_arr)) // если нашли такое число
// 				{
// 					flag = false; // не заносим число в массив
// 					break;
// 				}
// 			}
// 			if (flag)
// 				copy_arr(arr[cnt++], num1_arr); // иначе - заносим в массив
// 		}
// 	}

// 	// printf("%d", cnt);
// 	clock_t end = clock();								  // СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

// 	printf("Ответ = %d время = %f\n", cnt, time_spent); // выводим результат и время работы программы
// 	return 0;
// }
