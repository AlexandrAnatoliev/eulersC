// euler35c - Круговые простые числа

// Число 197 называется круговым простым числом, потому что все перестановки его цифр с конца в начало являются простыми числами : 197, 719 и 971.
//
// Существует тринадцать таких простых чисел меньше 100 : 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79 и 97.
//
// Сколько существует круговых простых чисел меньше миллиона ?

#include <stdio.h>
#include <stdbool.h>
#include <math.h> 													//для работы функции sqrt()
#include <time.h> 													// for clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 1000000

int note_prime_arr(char *prime_arr, int finish);
bool is_composite(char prime_arr[], int num);
int note_composite(char prime_arr[], int prime, int finish);
bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
	double time_spent = 0.0; 										// для хранения времени выполнения кода
	clock_t begin = clock(); 										// СТАРТ таймера

	static char prime_arr[LEN_ARR] = {0}; 							// массив[простое число] = 0 - static писать обязательно!
	int answ = 0;

	note_prime_arr(prime_arr, LEN_ARR); 							// заносим в массив простые числа

	for (int num = 2; num < LEN_ARR; num++) 						// перебираем цифры
	{
		if (prime_arr[num] == 0) 									// если простое число
		{
			int circ_num = num;
			bool is_answ_fl = true;
			int fact = 1;

			// отсекаем числа имеющие в своем составе четные цифры
			for (int number = num / 10; number > 0; number /= 10) 	// раскладываем простое число на цифры
			{													  	// последнюю цифру проверять не нужно - т.к. числа простые
				int ones = number % 10;							  	// младшая цифра числа

				if (ones % 2 == 0) 									// четные цифры в числе дадут четные круговые числа
				{
					is_answ_fl = false; 							// не подходит условиям задачи
					break;
				}
			}

			if (is_answ_fl)    								// простое число без четных цифр
			{
				while (num > fact * 10) 					// определяем множитель для младшей цифры
					fact *= 10;

				for (int cnt = fact; cnt > 1; cnt /= 10) 	// перебираем круговые числа
				{
					int ones = circ_num % 10;				// младшая цифра числа
					circ_num = ones * fact + circ_num / 10; // перествляем младшую цифру в начало числа
					if (prime_arr[circ_num])				// если встретилось составное число - прерываем
					{
						is_answ_fl = false; 				// не подходит условиям задачи
						break;
					}
				}
			}

			if (is_answ_fl)
				answ++;
		}
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent);	// выводим результат и время работы программы

	return 0;
}

int note_prime_arr(char *prime_arr, int finish)
// Функция отмечает простые и составные числа в массиве
// Параметры:	prime_arr[]	- массив с ранее вычисленными составными числами
//              finish      - конечное число
{
	for (int num = 2; num < finish; num++) 				// ищем  простые числа и отмечаем составные
	{
		// если число не отмечено составным -> проверяем число -> если число простое
		if (!prime_arr[num] && !is_composite(prime_arr, num))
			note_composite(prime_arr, num, finish); 	// отмечаем составные числа, кратные простому
	}

	return 0;
}

bool is_composite(char prime_arr[], int num)
// функция принимает число и возвращает true - если число составное
// параметры:	prime_arr[]      	- массив с вычисленными простыми и составными числами
//              prime_arr[num] = 0	- число простое!
//              prime_arr[num] = 1	- число составное!
//              num                 - проверяемое число
// return:      true                - если число составное!
{
	if (more_limit("is_composite()", "num", num, "LEN_ARR", LEN_ARR)) // проверяем выход за пределы массива
		return false;

	int div_max = sqrt(num) + 1; 				// выносим вычисление квадратного корня из цикла for

	for (int div = 2; div < div_max; div++) 	// чтобы он не вычислялся каждую итерацию цикла
	{
		if (!prime_arr[div] && !(num % div)) 	// пропускаем уже отмеченные составные делители
			return true;						// если есть делитель числа - отмечаем как составное
	}

	return false;
}

int note_composite(char prime_arr[], int prime, int finish)
// функция отмечает составные числа в массиве
// параметры:	prime_arr[]        	- массив с ранее вычисленными составными числами
//              prime_arr[num] = 0	- число простое!
//              prime_arr[num] = 1	- число составное!
//              prime               - простое число, служит шагом
//              finish              - конечный индекс в массиве
// return:                          - количество отмеченных составных чисел
{
	if (more_limit("note_composite()", "prime", prime, "LEN_ARR", LEN_ARR)) 
		return 0;									// проверка на выход числа за пределы массива

	if (more_limit("note_composite()", "finish", finish, "LEN_ARR", LEN_ARR))
		return 0;

	for (int i = 2 * prime; i < finish; i += prime) // первое число - простое, не отмечаем его
		prime_arr[i] = 1;							// отмечаем составные числа

	return 0;
}

bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
	if (input_value > limit_value) // обрабатываем превышение
	{
		printf("%s: %s = %d больше %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
		return true;
	}

	return false;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <math.h> //для работы функции sqrt()
// #include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

// bool is_simple(int num_arg)
// // функция принимает число и возвращает true - если число простое
// {
// 	int i_arg = sqrt(num_arg) + 1; // выносим вычисление квадратного корня из цикла for

// 	for (int i = 2; i < i_arg; i++) // чтобы он не вычислялся каждую итерацию цикла
// 	{
// 		if (num_arg % i == 0)
// 			return false;
// 	}
// 	return true;
// }

// int len_num(int num_arg)
// // возвращает количество цифр в числе
// {
// 	int cnt = 0;
// 	int num = num_arg;
// 	while (num)
// 	{
// 		num /= 10;
// 		cnt++;
// 	}
// 	return cnt;
// }

// int main(void)
// {
// 	double time_spent = 0.0; // для хранения времени выполнения кода
// 	clock_t begin = clock(); // СТАРТ таймера

// 	static char prime_arr[1000000] = {0}; // массив[простое число] = 1 - static писать обязательно!
// 	int num = 0;
// 	int num2 = 0;
// 	int answ = 0;
// 	int len = 0;

// 	for (int i = 2; i < 1000000; i++) // заполняем массив простыми числами
// 	{
// 		if (is_simple(i))
// 			prime_arr[i] = 1;
// 	}

// 	for (int i = 2; i < 1000000; i++)
// 	{
// 		if (prime_arr[i])
// 		{
// 			num = i; // num = 197
// 			bool flag = true;
// 			len = len_num(i) - 1; // количество перестановок чисел

// 			for (int j = 0; j < len; j++) // делаем 2 перестановки
// 			{
// 				num2 = (num % 10) * (int)round(pow(10, len)) + num / 10; //(7 * 10^2) + 19 = 719
// 				if (prime_arr[num2])									 // если 719 - простое число
// 					num = num2;											 // num = 719
// 				else
// 				{
// 					flag = false;
// 					break;
// 				}
// 			}
// 			if (flag)
// 				answ++;
// 		}
// 	}

// 	clock_t end = clock();								  // СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы

// 	return 0;
// }
