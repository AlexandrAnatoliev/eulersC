// euler40c - Постоянная Чамперноуна

// Дана иррациональная десятичная дробь, образованная объединением натуральных чисел :
//
// 0.123456789101112131415161718192021...
//
// Видно, что 12 - я цифра дробной части - 1.
//
// Также дано, что dn представляет собой n - ю цифру дробной части. Найдите значение следующего выражения :
//
// d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

#include <stdio.h>
#include <stdbool.h>
#include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h> 		// русский язык в printf()

#define LEN_ARR 10

typedef struct big_num 		// структура "большое число"
{
	char arr[LEN_ARR]; 		// массив для хранения цифр числа
	int len;		   		// длина числа
} big_t;

int big_num_init(big_t *big_num, int num);
int big_num_increment(big_t *big_num);
bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
	setlocale(LC_ALL, "Rus"); 										// русский язык в printf()

	double time_spent = 0.0; 										// для хранения времени выполнения кода
	clock_t begin = clock(); 										// СТАРТ таймера

	int answ = 1;
	int serial_nums[] = {1, 10, 100, 1000, 10000, 100000, 1000000}; // порядковые номера искомых цифр
	int len_fract = 0;												// длина дроби 0.12345...
	big_t integer;													// числа из которых состоит дробь

	len_fract = big_num_init(&integer, 1); 							// инициализируем первую цифру дробной части

	for (int i = 0; i < sizeof(serial_nums) / sizeof(serial_nums[0]); i++)
	{
		while (len_fract < serial_nums[i])			  				// пока не встретим искомый номер цифры дробной части
			len_fract += big_num_increment(&integer); 				// складываем длины увеличивающихся чисел

		answ *= integer.arr[len_fract - serial_nums[i]];
	}

	clock_t end = clock();								  			// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 			// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 			// выводим результат и время работы программы
	return 0;
}

int big_num_init(big_t *big_num, int num)
// Функция для присваивания начальных значений большому числу
// Параметры:   big_num	- большое число
//              num     - число
// return:      		- количество цифр  числе (массиве)
{
	big_num->len = 0;

	for (int i = 0; i < LEN_ARR; i++) 	// обнуляем массив
		big_num->arr[i] = 0;

	while (num) 						// заносим начальные данные
	{
		big_num->arr[big_num->len++] = num % 10;
		num /= 10;
	}

	return big_num->len;
}

int big_num_increment(big_t *big_num)
// Функция для инкрементирования большого числа
// параметры:   big_num	- большое число
// return:      		- количество цифр  числе (массиве)
{
	int ptr = 0;
	int residue = 1;

	while (residue) 											// идем по массиву пока есть остаток
	{
		if (more_limit("big_num_increment()", "ptr++", ptr + 1, "LEN_ARR", LEN_ARR))
			return 0; 											// проверка на выход за пределы массива

		int dig = big_num->arr[ptr] + residue;
		residue = dig / 10; 									// переносим при необходимости остаток
		big_num->arr[ptr++] = dig % 10;
	}

	big_num->len = (big_num->len > ptr) ? big_num->len : ptr; 	// обновляем длину числа

	return big_num->len;
}

bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// Функция для определения превышения переменной своего предельного значения
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

// int get_num(int cnt_arg, int num_arg, int n_arg)
// // Определяет цифру по ее номеру
// // Параметры:	cnt_arg	- текущий номер цифры                   // 12
// //				num_arg - текущее число                         // 123
// //				n_arg	- номер искомой цифры                   // 10
// // return:		искомая цифра
// {
// 	int cnt = cnt_arg - n_arg;                                  // 12 - 10 = 2 смещение с конца числа
// 	for (int i = 0; i < cnt; i++)
// 		num_arg /= 10;
// 	return num_arg % 10;                                        // вернет -> 1 (23)
// }

// int main(void)
// {
// 	int answ = 1;
// 	int num = 0;
// 	int cnt = 0;
// 	int step = 1;
// 	int n_arr[] = { 1,10,100,1000,10000,100000,1000000 };
// 	int indx = 0;

// 	while (cnt < 1000000)
// 	{
// 		num++;                                                  // перебираем натуральные числа
// 		if (num == 10 || num == 100 || num == 1000 || num == 10000 || num == 100000 || num == 1000000)
// 			step++;                                             // увеличиваем шаг счетчика цифр
// 		cnt += step;                                            // считаем цифры

// 		if (cnt >= n_arr[indx] && cnt < n_arr[indx] + step)     // счетчик в необходимом диапазоне
// 		{
// 			answ *= get_num(cnt, num, n_arr[indx]);             // вычисляем цифру
// 			indx++;
// 		}
// 	}

// 	printf("%d", answ);
// 	return 0;
// }
