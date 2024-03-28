// euler36c - Двухосновные палиндромы

// Десятичное число 585 = 1001001001 (в двоичной системе), является палиндромом по обоим основаниям.
//
// Найдите сумму всех чисел меньше миллиона, являющихся палиндромами по основаниям 10 и 2.
//
//(Пожалуйста, обратите внимание на то, что палиндромы не могут начинаться с нуля ни в одном из оснований).

#include <stdio.h>
#include <stdbool.h>
#include <time.h> 											// for clock_t, clock(), CLOCKS_PER_SEC

int get_even_len_palindrome(int num);
int get_uneven_len_palindrome(int ones, int decs);
bool is_bin_palindrome(int num);

int main(void)
{
	double time_spent = 0.0; 								// для хранения времени выполнения кода
	clock_t begin = clock(); 								// СТАРТ таймера

	int answ = 0;
	for (int num = 1; num < 1000; num++) 					// перебираем десятичные палиндромы с четной длиной
	{
		int dec_pal = get_even_len_palindrome(num);

		if (is_bin_palindrome(dec_pal)) 					// складываем палиндромы по основанию 2
			answ += dec_pal;
	}

	for (int ones = 0; ones < 10; ones++) 					// перебираем десятичные палиндромы с нечетной длиной
	{
		for (int decs = 1; decs < 100; decs++)
		{
			int dec_pal = get_uneven_len_palindrome(ones, decs);

			if (is_bin_palindrome(dec_pal))
				answ += dec_pal;
		}
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent);	// выводим результат и время работы программы
	return 0;
}

int get_even_len_palindrome(int num)
// Функция для получения палиндрома (с четной длиной числа) из числа
// Параметры:   num	- число (123)
// return:      	- палиндром (123321)
{
	int palindrome = 0;
	int fact = 1;

	while (num > fact * 10) 				// определяем порядок числа (123 -> fact = 100)
		fact *= 10;

	for (int f_less = fact, f_more = fact * 10; f_less >= 1; f_less /= 10, f_more *= 10, num /= 10)
	{
		palindrome += num % 10 * f_more; 	// 123 -> 123000
		palindrome += num % 10 * f_less; 	// 123 -> 321
	}

	return palindrome;
}

int get_uneven_len_palindrome(int ones, int decs)
// Функция для получения палиндрома (с нечетной длиной числа) из двух чисел
// Параметры:   ones	- число в середине (4)
//				decs	- числа по краям (20)
// return:      		- палиндром (20402)
{

	int fact = 1;

	while (decs > fact) 					// определяем порядок числа в середине палиндрома
		fact *= 10;

	int palindrome = ones * fact; 			// 400

	for (int f_less = fact / 10, f_more = fact * 10; f_less >= 1; f_less /= 10, f_more *= 10, decs /= 10)
	{
		palindrome += decs % 10 * f_more; 	// 20 -> 20000
		palindrome += decs % 10 * f_less; 	// 20 -> 02
	}

	return palindrome; 						// 20402
}

bool is_bin_palindrome(int num)
// Функция для проверки, является ли палиндромом число по основанию 2
// Параметры:   num		- число (123321)
// return:      true	- является
{
	int palindrome = 0;
	int number = num;

	while (number)
	{
		palindrome = (palindrome << 1) + (number & 1); 	// добаляем по одной двоичной цифре и смещаем число влево
		number >>= 1;								   	// смещаем число вправо и сохраняем
	}

	return palindrome == num;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h> 													// for clock_t, clock(), CLOCKS_PER_SEC

// char get_arr(char arr_arg[], int num_arg, int div_arg)
// // раскладывает число на цифры по заданному основанию и заносит их в массив
// // параметры:
// // char arr_arg[]: массив, в который будет сохраняться разложенное число;
// // int num_arg: раскладываемое число;
// // int div_arg: основание, по которому раскладывается число
// // return: количество цифр в числе
// {
// 	char cnt = 0;
// 	while (num_arg)									//раскладываем число на цифры и заносим в массив
// 	{
// 		arr_arg[++cnt] = num_arg % div_arg;
// 		num_arg /= div_arg;
// 	}
// 	arr_arg[0] = cnt;								//заносим количество цифр в числе
// 	return cnt;
// }

// bool is_palindrom(char arr_arg[])
// //true - если число палиндром
// {
// 	char ptr1 = 1;									//указатель(индекс) на первое число
// 	char ptr2 = arr_arg[0];							//указатель(индекс) на последнее число
// 	while (ptr1 < ptr2)
// 	{
// 		if (arr_arg[ptr1] == arr_arg[ptr2])
// 		{
// 			ptr1++;
// 			ptr2--;
// 		}
// 		else
// 			return false;
// 	}
// 	return true;
// }

// int main(void)
// {
// 	double time_spent = 0.0; 										// для хранения времени выполнения кода
// 	clock_t begin = clock(); 										// СТАРТ таймера

// 	char arr_bin[22] = { 0 };						//массив для хранения цифр числа в 2-ичном виде
// 	//первая цифра - количество цифр в занесенном числе, 1000000 -> 21-значное число в 2-ичной системе
// 	char arr_dec[7] = { 0 };						//массив для хранения цифр числа в 10-тичном виде
// 	int answ = 0;

// 	for (int num = 1; num < 1000000; num++)
// 	{
// 		get_arr(arr_dec, num, 10);
//         get_arr(arr_bin, num, 2);
// 		if (is_palindrom(arr_dec) && is_palindrom(arr_bin))
// 			answ += num;
// 	}

// 	clock_t end = clock();								  	// СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent);	// выводим результат и время работы программы
// 	return 0;
// }
