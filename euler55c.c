// euler55c - Числа Личрэла

// Если взять число 47, перевернуть его и прибавить к исходному, т.е. найти 47 + 74 = 121, получится палиндром.

// Не из всех чисел таким образом сразу получается палиндром. К примеру,

// 349 + 943 = 1292
// 1292 + 2921 = 4213
// 4213 + 3124 = 7337

// Т.е., понадобилось 3 итерации для того, чтобы превратить число 349 в палиндром.

// Хотя никто еще этого не доказал, считается, что из некоторых чисел, таких как 196, невозможно получить палиндром.
// Такое число, которое не образует палиндром путем переворачивания и сложения с самим собой, называется числом Личрэла.
// Ввиду теоретической природы таких чисел, а также цели этой задачи, мы будем считать, что число является числом Личрэла до тех пор,
// пока не будет доказано обратное. Помимо этого дано, что любое число меньше десяти тысяч либо (1) станет палиндромом меньше, чем за 50 итераций,
// либо (2) никто, с какой бы-то ни было вычислительной мощностью, не смог получить из него палиндром.
// Между прочим, 10677 является первым числом, для которого необходимо более 50 итераций,
// чтобы получить палиндром: 4668731596684224866951378664 (53 итерации, 28-значное число).

// На удивление, есть такие палиндромы, которые одновременно являются и числами Личрэла; первое такое число - 4994.

// Сколько существует чисел Личрэла меньше десяти тысяч?

// ПРИМЕЧАНИЕ: Формулировка задачи была немного изменена 24 апреля 2007 года, чтобы подчеркнуть теоретическую природу чисел Личрэла.

#include <stdio.h>
#include <stdbool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

#define MAX_NUM 10000
#define MAX_ITER 50
#define LEN_NUM 30

int num_increment(char start_num[]);
bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);
int get_next_num(const char num[], char next_num[]);
bool is_palindrom(const char num[]);

int main(void)
{
	double time_spent = 0.0; // для хранения времени выполнения кода
	clock_t begin = clock(); // СТАРТ таймера

	char arr[MAX_ITER + 1][LEN_NUM] = {2, 0, 1}; // 51 число, получаемое за 50 итераций (плюс сразу заносим стартовое число)

	int cnt = 0; // счетчик занесенных чисел

	for (int num = 10; num < MAX_NUM; num++)
	{
		num_increment(arr[0]);
		for (int iter = 0; iter < MAX_ITER; iter++)
		{
			get_next_num(arr[iter], arr[iter + 1]); // записываем следующее число
			if (is_palindrom(arr[iter + 1]))
				break;
			if (iter == 49)
				cnt++;
		}
	}

	clock_t end = clock();								  // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

	printf("Ответ = %d время = %f\n", cnt, time_spent); // выводим результат и время работы программы
	return 0;
}

int num_increment(char start_num[])
// Функция для инкрементирования числа, записанного в виде массива
// параметры:   start_num[]	- число, записанное в виде массива
// return:      			- количество цифр  числе (массиве)
{
	int ptr = 0;
	int residue = 1;

	while (residue)
	{
		if (input_more_limit("num_increment()", "++ptr", ptr + 1, "LEN_NUM", LEN_NUM))
			return 0;

		int num = start_num[++ptr] + residue;
		residue = num / 10;
		start_num[ptr] = num % 10;
	}

	start_num[0] = (start_num[0] > ptr) ? start_num[0] : ptr;

	return start_num[0];
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
		printf("%s: %s = %d больше %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
		return true;
	}

	return false;
}

int get_next_num(const char num[], char next_num[])
// функция берет число, переворачивает его и прибавляет к исходному
// параметры:   num[]  		- исходноое число
//              next_num[]	- получившееся число
// return:      			- количество цифр в получившемся числе (массиве)
{

	int ptr = 0;		  // указатель на начало массива
	int rev_ptr = num[0]; // на конец массива
	int residue = 0;

	while (residue || ptr < num[0])
	{
		if (input_more_limit("num_increment()", "++ptr", ptr + 1, "LEN_NUM", LEN_NUM))
			return 0;

		int rev_num = (rev_ptr > 0) ? num[rev_ptr--] : 0; // в нулевой ячейке записана не очередная цифра, а их количество в числе
		int number = num[++ptr] + rev_num + residue;	  // складываем цифры, перебирая их от начала концу и наоборот
		residue = number / 10;
		next_num[ptr] = number % 10; // переносим мостаток
	}

	next_num[ptr + 1] = 0; // обнуляем цифру за числом, чтобы затереть следы старого числа
	next_num[0] = ptr;

	return ptr;
}

bool is_palindrom(const char num[])
// Функция проверяет равенство цифр в массиве, сравнивая их от конца к ачалу и наоборот между собой
// параметры:   num[]	- число (массив)
// return:      true	- число - палиндром
{
	int ptr = 1;		  // указатель на начало массива
	int rev_ptr = num[0]; // на конец массива

	while (rev_ptr > ptr) // перемещаемся по массиву с двух сторон
	{
		if (num[ptr++] != num[rev_ptr--]) // если цифры не совпали - это не палиндром
			return false;
	}

	return true;
}