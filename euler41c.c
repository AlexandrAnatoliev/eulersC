// euler41c - Пан-цифровое простое число

// Будем считать n-значное число пан-цифровым, если каждая из цифр от 1 до n используется в нем ровно один раз.
// К примеру, 2143 является 4-значным пан-цифровым числом, а также простым числом.
// 7652413
// Какое существует наибольшее n-значное пан-цифровое простое число ?

// euler41c - Пан-цифровое простое число

// Будем считать n-значное число пан-цифровым, если каждая из цифр от 1 до n используется в нем ровно один раз.
// К примеру, 2143 является 4-значным пан-цифровым числом, а также простым числом.
// 7652413
// Какое существует наибольшее n-значное пан-цифровое простое число ?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>											// для работы функции sqrt()
#include <time.h>											// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h> 										// русский язык в printf()

#define LEN_ARR 10 											// длина массива цифрами - берем с запасом

typedef struct pandig 										// структура "пан-цифровое число"
{
	int indx_ar[LEN_ARR]; 									// массив для хранения "числа-из-индексов"
	int len;			  									// длина числа
	int num;			  									// пан-цифровое число
} pandig_t;

text_t pandig_init(pandig_t *pandig, int num);
int pandig_decrement(pandig_t *pandig);
text_t is_simple(int num);

int main(void)
{
	setlocale(LC_ALL, "Rus"); 								// русский язык в printf()

	double time_spent = 0.0; 								// для хранения времени выполнения кода
	clock_t begin = clock(); 								// СТАРТ таймера

	int num_init = 987654321; 								// максимально возможное пан-цифровое число
	int answ, div;
	text_t answ_fl = false;

	pandig_t pandig;

	while (num_init)
	{
		pandig_init(&pandig, num_init); 					// инициализируем пан-цифровое число в структуру
		answ = pandig_decrement(&pandig);

		while (answ && answ_fl == false)
		{
			answ = pandig_decrement(&pandig); 				// при достижении последнего числа вернет 0
			answ_fl = is_simple(answ);
		}

		if (answ_fl) 										// если найден ответ
			break;

		div = 1;
		while (num_init > div * 10) 						// определям длину числа
			div *= 10;

		num_init %= div; 									// отрезаем старшую цифру
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 	// выводим результат и время работы программы

	return 0;
}

text_t pandig_init(pandig_t *pandig, int num)
// Функция для инициализации пан-цифрового числа
// Параметры:	pandig	- пан-цифровое число (структура)
//              num		- вносимое пан-цифровое число
// return:      false	- вносимое число не пан-цифровое
{
	int ptr, div = 1;
	int sort_ar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 		// отсортированный массив
	char fl_ar[LEN_ARR] = {0};					 		// массив для контроля занесенных цифр

	pandig->len = 1; 									// заносим начальные данные в структуру
	pandig->num = num;

	for (int i = 0; i < LEN_ARR; i++)
		pandig->indx_ar[i] = 0; 						// обнуляем массив

	while (num > div * 10) 								// подбираем делитель
	{
		div *= 10;	   									
		pandig->len++; 									// считаем длину числа
	}

	ptr = LEN_ARR - pandig->len; 						// индекс первой цифры числа
	while (num)
	{
		for (int i = 0; i < LEN_ARR; i++)
		{
			if (num / div == sort_ar[i]) 				// ищем старшую цифру в отсортированном массиве
			{
				pandig->indx_ar[ptr++] = i; 			// заносим индекс цифры в массив

				for (int j = i; j < LEN_ARR - 1; j++) 	// смещаем цифры в отсортированном массиве
					sort_ar[j] = sort_ar[j + 1];
				break;
			}
		}

		fl_ar[num / div] = 1; 							// помечаем цифру как занятую
		num %= div;		   								// отрезаем старшую цифру
		div /= 10;
	}

	for (int i = 1; i < pandig->len + 1; i++) 			// проверяем, что число пан-цифровое
		if (fl_ar[i] == 0)					  			// нет цифры
			return false;

	return true;
}

int pandig_decrement(pandig_t *pandig)
// Функция для получения следующего меньшего пан-цифрового числа из данных цифр
// Параметры:	pandig	- пан-цифровое число (структура)
// return:				- следующее меньшее пан-цифровое число
//				0		- при достижении минимально возможного числа
{
	int max_indx_ar[] = {0, 8, 7, 6, 5, 4, 3, 2, 1, 0}; 		// максимально возможный индекс
	int sort_ar[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};				// отсортированный массив
	int num, past_zero = 0;

	for (int i = 0; i < LEN_ARR; i++) 							// отмечаем индекс последнего ноля перед цифрой
	{
		if (pandig->indx_ar[i] == 0) 							// [0,0,0,->0<-,1,2,3,4,5]
			past_zero = i;
		else
			break;
	}

	if (past_zero >= LEN_ARR - 2) 								// достигнуто минимально возможное пан-цифровое число
		return 0;

	for (int i = LEN_ARR - 2; i > past_zero; i--) 				// [0,0,0,0,->1,2,3,4,5<-]
	{
		if (pandig->indx_ar[i])									// уменьшаем число
		{
			pandig->indx_ar[i]--;
			break;
		}
		else
			pandig->indx_ar[i] = max_indx_ar[i];
	}

	num = 0;
	for (int i = LEN_ARR - pandig->len; i < LEN_ARR; i++)
	{
		num *= 10;											   	// смещаем цифры на разряд
		num += sort_ar[pandig->indx_ar[i]];					   	// заносим следующую цифру
		for (int j = pandig->indx_ar[i]; j < LEN_ARR - 2; j++)	// смещаем цифры в отсортированном массиве
			sort_ar[j] = sort_ar[j + 1];
	}

	pandig->num = num;
	return num;
}

text_t is_simple(int num)
// Функция для определения простого числа
// Параметры:	num		- число
// return:		true	- если число простое
{
	int max_div = sqrt(num) + 1; 			// выносим вычисление квадратного корня из цикла for

	for (int div = 2; div < max_div; div++) // чтобы он не вычислялся каждую итерацию цикла
	{
		if (num % div == 0) 				// делим только на простые числа (ar_arg[i] == 1)
			return false;
	}

	if (num < 2) 							// 0 и 1 не являются простыми числами
		return false;

	return true;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <math.h>											// для работы функции sqrt()
// #include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
// #include <locale.h> 		// русский язык в printf()

// bool is_simple(char ar_arg[], int num_arg)
// // функция определяет простое ли число
// // параметры:	num_arg		- число
// //				ar_arg[]	- массив, уже вычисленных простых чисел
// // return:		true		- если число простое
// {
// 	int i_arg = sqrt(num_arg) + 1;							// выносим вычисление квадратного корня из цикла for

// 	for (int i = 2; i < i_arg; i++)							// чтобы он не вычислялся каждую итерацию цикла
// 	{
// 		if (ar_arg[i] && num_arg % i == 0)					// делим только на простые числа (ar_arg[i] == 1)
// 			return false;
// 	}
// 	return true;
// }

// int put_number(char ar_arg[], int num_arg)
// // сохраняет в массив цифры по индексу
// // параметры:	num_arg		- число
// //				ar_arg[]	- массив, для хранения чисел
// // return:					- длина числа

// {
// 	int cnt = 0;
// 	while (num_arg)
// 	{
// 		ar_arg[num_arg % 10] = 1;							// заносим цифру в массив
// 		num_arg /= 10;
// 		cnt++;												// считаем длину числа
// 	}
// 	return cnt;
// }

// bool is_pandigital(int num_arg)
// // функция для определения пан-цифрового числа
// // параметры:	num_arg		- число
// // return:		true		- пан-цифровое число
// {
// 	char arr[10] = { 0 };									// массив сохраняющий содержащиеся цифры
// 	int cnt_num = 0;
// 	int len_num = put_number(arr, num_arg);					// длина числа

// 	if (arr[0])												// если был ноль
// 		return false;

// 	for (int i = 1; i <= len_num; i++)						// считаем фактически занесенные цифры
// 		if (arr[i])
// 			cnt_num++;
// 	return cnt_num == len_num;								// совпадет, если все цифры занесены один раз
// }

// int main(void)
// {
// 	setlocale(LC_ALL, "Rus"); 										// русский язык в printf()

// 	double time_spent = 0.0; 										// для хранения времени выполнения кода
// 	clock_t begin = clock(); 										// СТАРТ таймера

// 	int answ;
// 	static char prime_arr[10000000] = { 0 };				// массив[простое число] = 1 - static писать обязательно!

// 	for (int i = 2; i < 10000000; i++)						// заполняем массив простыми числами
// 	{
// 		if (is_simple(prime_arr, i))
// 			prime_arr[i] = 1;
// 	}

// 	for (int i = 10000000; i > 10; i--)
// 		if (prime_arr[i] && is_pandigital(i))
// 		{
// 			answ = i;
// 			break;
// 		}

// 	clock_t end = clock();								  			// СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 			// время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent); 			// выводим результат и время работы программы

// 	return 0;
// }
