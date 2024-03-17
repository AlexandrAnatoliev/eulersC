#include <stdio.h>
#include <stdbool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

int split_number(unsigned char arr_arg[], int num_arg)
// принимает указатель на массив и число
// раскладывает число на отдельные цифры и заносит в массив
// возвращает число занесенных символов в массив
{
	int cnt = 1;
	while (num_arg)
	{
		if (num_arg % 10 == 0) // заносим нули
		{
			arr_arg[cnt++] = 0;
			num_arg /= 10;
		}
		else
		{
			arr_arg[cnt++] = num_arg % 10; // заносим цифры
			num_arg /= 10;
		}
	}
	arr_arg[0] = cnt; // длина массива - в первой ячейке
	return cnt;
}

int mult_num(unsigned char arr_num1_arg[], int num_arg)
// перемножает числа 1 и 2
{
	int cnt1 = arr_num1_arg[0]; // длина массива1 (первого числа)

	unsigned char num2_arr[5] = {0}; // число-массив2 - второе число
	split_number(num2_arr, num_arg);
	int cnt2 = num2_arr[0];

	unsigned char num3_arr[3][255] = {0}; // промежуточный массив для умножения столбиком

	unsigned char num = 0;		// переменные для разложения числа 23 -> 3
	unsigned char next_num = 0; //									 -> 2

	for (int j = 1; j < cnt2; j++)
	// перемножаем цифры в числах и заносим в промежуточный массив
	{
		next_num = 0;
		if (j > 1)	// если второй множитель двузначный
			cnt1++; // увеличиваем длину числа
		for (int i = 1 + j - 1; i < cnt1; i++)
		{
			// перемножаем цифры
			num = arr_num1_arg[i + 1 - j] * num2_arr[j] + next_num;
			next_num = num / 10;		   // выделяем десятки
			num3_arr[j - 1][i] = num % 10; // и записываем остаток в массив
		}

		if (next_num)							// если осталось незанесенная цифра
			num3_arr[j - 1][cnt1++] = next_num; // заносим ее в массив и увеличиваем длину числа
	}

	next_num = 0;
	for (int i = 1; i < cnt1; i++)
	// складываем цифры в промежуточном массиве
	{
		num = num3_arr[0][i] + num3_arr[1][i] + num3_arr[2][i] + next_num;
		arr_num1_arg[i] = num % 10;
		next_num = num / 10;
	}
	if (next_num)
		arr_num1_arg[cnt1++] = next_num;

	int cnt_check; // уточняем длину массива
	for (int i = cnt1 - 2; i < cnt1 + 2; i++)
	{
		if (arr_num1_arg[i])
			cnt_check = i + 1;
	}
	arr_num1_arg[0] = cnt_check;
	return cnt1;
}

bool compare_nums(const unsigned char arr_num1_arg[], const unsigned char arr_num2_arg[])
// сравнивает массивы -> true - одинаковые
// первый элемент массива - длина, если длины не совпадут, то дальше не проверяется
{
	for (int i = 0; i < 255; i++)
		if (arr_num1_arg[i] != arr_num2_arg[i])
			return false;
	return true;
}

int copy_arr(unsigned char arr_num1_arg[], unsigned char arr_num2_arg[])
// копирует массив 2 в 1
{
	int len_arr = arr_num2_arg[0];
	for (int i = 0; i < len_arr; i++)
		arr_num1_arg[i] = arr_num2_arg[i];
	return 0;
}

void nullify_arr(unsigned char arr_num1_arg[], int len_arr_arg)
// обнуляем массив
{
	for (int i = 0; i < len_arr_arg; i++)
		arr_num1_arg[i] = 0;
}

int main(void)
{
	double time_spent = 0.0; // для хранения времени выполнения кода
	clock_t begin = clock(); // СТАРТ таймера

	static unsigned char arr[10000][255] = {0}; // без static - ошибка, первый символ - длина массива
	unsigned char num1_arr[255] = {0};			// число-массив1 для вычислений

	int a = 100;
	int b = 100;
	int cnt = 0; // счетчик занесенных чисел

	for (int base = 2; base <= a; base++) // перебираем числа основания
	{
		nullify_arr(num1_arr, 255); // обнуляем массив перед использованием
		split_number(num1_arr, base);
		for (int pow = 2; pow <= b; pow++) // перебираем степени
		{
			mult_num(num1_arr, base); // возводим в степень - умножаем число на само себя несколько раз

			bool flag = true;
			for (int j = 0; j <= cnt; j++)
			// проверяем нет ли уже такого числа
			{
				if (compare_nums(arr[j], num1_arr)) // если нашли такое число
				{
					flag = false; // не заносим число в массив
					break;
				}
			}
			if (flag)
				copy_arr(arr[cnt++], num1_arr); // иначе - заносим в массив
		}
	}

	// printf("%d", cnt);
	clock_t end = clock();								  // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

	printf("Ответ = %d время = %f\n", cnt, time_spent); // выводим результат и время работы программы
	return 0;
}
