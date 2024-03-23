// euler32c - Пан-цифровые произведения

// Каждое n - значное число, которое содержит каждую цифру от 1 до n ровно один раз, будем считать пан - цифровым;
//  к примеру, 5 - значное число 15234 является пан - цифровым, т.к.содержит цифры от 1 до 5.
//
// Произведение 7254 является необычным, поскольку равенство 39 × 186 = 7254, состоящее из множимого, множителя и произведения
//  является пан - цифровым, т.е.содержит цифры от 1 до 9.
//
// Найдите сумму всех пан - цифровых произведений, для которых равенство "множимое × множитель = произведение"
//  можно записать цифрами от 1 до 9, используя каждую цифру только один раз.
//
// ПОДСКАЗКА: Некоторые произведения можно получить несколькими способами, поэтому убедитесь, что включили их в сумму лишь единожды.

#include <stdio.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC
#include <stdbool.h>

#define LEN_ARR 10 // берем с запасом

bool increase_indx_num(int indx_num[]);
bool get_pandigital_num(int pandig_num[], int indx_num[]);
bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
	double time_spent = 0.0; // для хранения времени выполнения кода
	clock_t begin = clock(); // СТАРТ таймера

	int indx_num[LEN_ARR] = {0};	   // промежуточное число-из-индексов
	int pandigital_num[LEN_ARR] = {0}; // пан-цифровое число
	char cash[10000] = {0};

	int answer = 0;

	while (increase_indx_num(indx_num)) // перебираем возможные перестановки цифр
	{
		get_pandigital_num(pandigital_num, indx_num);
		int fact = 1;
		int num1 = 0;
		bool fl = false;

		for (int ptr1 = 1; ptr1 < LEN_ARR - 1; ptr1++) // ноль не используем
		{
			if (fl)
				break;
			// int pandigital_num[] = {0, 8, 3, 7, 1, 4, 2, 5, 9, 6};
			// int pandigital_num[] = {0, 2, 1, 3, 4, 5, 7, 8, 6, 9};

			int ptr1_1 = ptr1;
			int ptr2 = ptr1 + 1;
			while (ptr1_1 < ptr2)
			{
				num1 += pandigital_num[ptr1_1++] * fact;
				fact *= 10;
			}

			for (ptr2 = ptr1 + 1; ptr2 < LEN_ARR; ptr2++)
			{
				if (fl)
					break;
				int fact = 1;
				int num2 = 0;
				int ptr2_1 = ptr1 + 1;
				while (ptr2_1 < LEN_ARR)
				{
					num2 += pandigital_num[ptr2_1++] * fact;
					fact *= 10;
					int answ = num1 * num2;
					int ptr3 = ptr2_1;
					while (answ)
					{
						if (ptr3 >= LEN_ARR)
							break;
						if (answ % 10 != pandigital_num[ptr3++])
							break;
						answ /= 10;
					}

					if (answ == 0 && ptr3 == LEN_ARR && cash[num1 * num2] == 0)
					{
						answer += num1 * num2;
						fl = true;
						printf("%d * %d = %d\n", num1, num2, num1 * num2);
						// for (int i = 0; i < LEN_ARR; i++)
						// 	printf("%d", pandigital_num[i]);

						// return 0;
						cash[num1 * num2] = 1;
					}

					if (fl || ptr3 >= LEN_ARR)
						break;
				}
			}
		}
	}

	clock_t end = clock();								  // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

	printf("Ответ = %d время = %f\n", answer, time_spent); // выводим результат и время работы программы
	return 0;
}

bool increase_indx_num(int indx_num[])
// Функция для увеличения промежуточного числа на единицу
// Параметры:	indx_num    - массив c индексами
// return:      false       - при достижении максимально возможного числа
{
	int max_indx_arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; // максимально возможный индекс (берем с запасом)
	indx_num[LEN_ARR - 2]++;							 // увеличиваем число

	for (int i = LEN_ARR - 2; i > 0; i--)
	{
		if (indx_num[i] > max_indx_arr[i]) // если разряд переполняется
		{
			indx_num[i - 1]++; // увеличиваем старший разряд
			indx_num[i] = 0;
		}

		else
			break; // прерываем, если не нужно дальше менять числа
	}

	if (indx_num[0])
		return false; // достигли максимально возможного (9-значного) числа

	return true;
}

bool get_pandigital_num(int pandig_num[], int indx_num[])
// Функция для вычисления пан-цифрового числа по массиву с индексами перестановок
// Параметры:	indx_num        - массив c индексами
//              pandigital_num  - массив с панцифровым числом
// return:      false       	- при достижении максимально возможного числа
{
	int sort_arr[LEN_ARR] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // отсортированные числа

	for (int i = 0; i < LEN_ARR; i++)
	{
		pandig_num[i] = sort_arr[indx_num[i]];				  // выбираем число из отсортированного массива
		for (int j = indx_num[i]; j < (LEN_ARR - 1 - i); j++) // смещаем числа в массиве
			sort_arr[j] = sort_arr[j + 1];
	}

	if (pandig_num[0]) // если вместо ноля число
		return false;  // достигли максимально возможного (9-значного) числа

	return true;
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
	if (input_value > limit_value) // обрабатываем превышение
	{
		printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
		return true;
	}

	return false;
}

// int get_permutation(int sort_arr[], int indx_arr[])
// // Функция выводит на экран искомую перестановку
// // параметры:	indx_arr[]  - массив, в котором хранится промежуточный ответ из индексов
// //              sort_arr[]  - массив отсортированных по возрастанию чисел (из которых формируется перестановка)
// {
//     printf("answer = ");

//     for (int indx = 0; indx < LEN_ARR; indx++)
//     {
//         if (input_more_limit("show_permutation()", "indx_arr[indx]", indx_arr[indx], "LEN_ARR - 1", LEN_ARR - 1))
//             return 1;                                   // обрабатываем некорректные индексы в массиве

//         printf("%d", sort_arr[indx_arr[indx]]);         // выводим число по индексу из отсортированного массива

//         for (int i = indx_arr[indx]; i < LEN_ARR; i++)  // изымаем число из массива
//             sort_arr[i] = sort_arr[i + 1];
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h> 															// for clock_t, clock(), CLOCKS_PER_SEC

// bool put_numbers(char arr_arg[], int num_arg)
// //сохраняет в массив цифры по индексу
// //возвращает false, если в массиве такие цифры уже есть
// {
// 	while (num_arg)
// 	{
// 		if (arr_arg[num_arg % 10] == 0)
// 		{
// 			arr_arg[num_arg % 10] = 1;
// 			num_arg /= 10;
// 		}
// 		else
// 			return false;
// 	}
// 	return true;
// }

// bool is_pandigital(int mult_arg1, int mult_arg2, int prod_arg)
// //принимает два множителя и произведение, возвращает true если равенство является пан-цифровым
// {
// 	char arr[10] = { 0 };										//массив сохраняющий уже содержащиеся цифры

// 	if (put_numbers(arr, mult_arg1) == false)					//заносим в массив цифры первого множителя
// 		return false;
// 	if (put_numbers(arr, mult_arg2) == false)					//заносим в массив цифры второго множителя
// 		return false;
// 	if (put_numbers(arr, prod_arg) == false)					//заносим в массив цифры произведение
// 		return false;

// 	if (arr[0])													//если был ноль
// 		return false;

// 	for (int i = 1; i < 10; i++)								//проверяем что были все цифры
// 		if (arr[i] == 0)
// 			return false;
// 	return true;
// }

// bool is_possible(int mult_arg1, int mult_arg2)
// //true - возможно есть пан-цифровое равенство, т.е сумма цифр будет равня 9
// //счистает количество цифр множителей, варианты: a * bbbb = cccc; aaaa * b = cccc; aa * bbb = cccc; aaa * bb = cccc
// {
// 	if ((mult_arg1 < 10) && (mult_arg2 > 999) || (mult_arg2 < 10) && (mult_arg1 > 999))		//a * bbbb = cccc || aaaa * b = cccc
// 		return true;
// 	if ((mult_arg1 > 9) && (mult_arg1 < 100) && (mult_arg2 > 100) && (mult_arg2 < 1000))	//aa * bbb = cccc
// 		return true;
// 	if ((mult_arg2 > 9) && (mult_arg2 < 100) && (mult_arg1 > 100) && (mult_arg1 < 1000))	//aaa * bb = cccc
// 		return true;
// 	return false;
// }

// int main(void)
// {
// 	double time_spent = 0.0; 																// для хранения времени выполнения кода
// 	clock_t begin = clock(); 																// СТАРТ таймера

// 	int arr[20] = { 0 };
// 	int cnt = 0;
// 	int answ = 0;

// 	for (int mult1 = 0; mult1 < 10000; mult1++)
// 	{
// 		for (int mult2 = 0; mult2 < 10000; mult2++)
// 		{
// 			if (is_possible(mult1, mult2) && is_pandigital(mult1, mult2, mult1 * mult2))
// 			{
// 				bool flag = true;								//проверяем осутствие в массиве такого множителя
// 				for (int i = 0; i < cnt; i++)
// 				{
// 					if (arr[i] == mult1 * mult2)
// 					{
// 						flag = false;
// 						break;
// 					}
// 				}
// 				if (flag)
// 				{
// 					answ += mult1 * mult2;						//заносим множитель в массив
// 					arr[cnt++] = mult1 * mult2;
// 				}
// 			}
// 		}
// 	}
// 	// printf("%d", answ);

// 	clock_t end = clock();								  									// СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 									// время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent); 						// выводим результат и время работы программы

// 	return 0;
// }
