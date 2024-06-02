// euler60c - Объединение пары в простое число

//Простые числа 3, 7, 109 и 673 достаточно замечательны.Если взять любые два из них и объединить их в произвольном порядке, 
//в результате всегда получится простое число.Например, взяв 7 и 109, получатся простые числа 7109 и 1097. 
//Сумма этих четырех простых чисел, 792, представляет собой наименьшую сумму элементов множества из четырех простых чисел, 
//обладающих данным свойством.
//
//Найдите наименьшую сумму элементов множества из 5 простых чисел, для которых объединение любых двух даст новое простое число.
// 26033: 13 - 5197 - 5701 - 6733 - 8389

#include <stdio.h>
#include <time.h>                   // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>                 // русский язык в printf()
#include <stdbool.h> 																// для красоты кода использую bool
#include <math.h>

#define LEN_ARR 1500

typedef struct list		// список чисел
{
	int arr[LEN_ARR];	// массив для хранения чисел
	int nums;			// количество чисел 
	int indx;			// индекс текущего числа
} list_t;

bool is_prime(list_t* prime_list, int num);
int get_concat_list(list_t* concat_list, list_t* prime_list, const list_t* num_list, int num);

int main(void)
{
	setlocale(LC_ALL, "Rus");                                   // русский язык в printf()

	double time_spent = 0.0;                                    // для хранения времени выполнения кода
	clock_t begin = clock();                                    // СТАРТ таймера

	int answ = 0;

	list_t zero_list = { .arr[0] = 0, .nums = 0, .indx = 0 };
	list_t lists[5];

	for (int i = 0; i < 5; i++)
		lists[i] = zero_list; // обнуляем массивы



	for (int num1 = 2; num1 < 10000; num1++)
	{
		if (is_prime(&lists[0], num1))			// составляем список num1 - простые числа до 10000
			lists[0].arr[lists[0].nums++] = num1;
	}

	int numb_list = 0; // текущий номер списка
	int max_numbs = 3; // количество подходящих чисел в списке

	while (numb_list < 4)
	{
		lists[numb_list + 1] = zero_list; // обнуляем следующий массив ? нужно ли, можно скинуть только количество чисел в нем
		if (get_concat_list(&lists[numb_list + 1], &lists[0], &lists[numb_list], lists[numb_list].arr[lists[numb_list].indx]) > max_numbs)
		{
			numb_list++; // переходим к следующему массиву
			max_numbs--;
			continue;
		}

		if (lists[numb_list].indx >= lists[numb_list].nums) // массив кончился
		{
			numb_list--;// переходим к предыдущему массиву
			max_numbs++;
		}

		lists[numb_list].indx++; // переходим к следующему числу массива
	}

	for (int i = 0; i < 5; i++)
		answ += lists[i].arr[lists[i].indx];


	clock_t end = clock();                                      // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;       // время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent);        // выводим результат и время работы программы
	return 0;
}

bool is_prime(list_t* prime_list, int num)
// Функция для определения простого числа
// Параметры:	prime_arr[]       	- массив с ранее вычисленными простыми числами
//              num                 - проверяемое число
// return:      true                - если число простое!
{
	int div_max = sqrt(num) + 1; 				// выносим вычисление квадратного корня из цикла for
	int indx = 0;

	while (prime_list->arr[indx] && prime_list->arr[indx] < div_max) // перебираем уже вычисленные простые (!) делители
	{
		if (num % prime_list->arr[indx] == 0) 	// если делится
			return false;
		indx++;
	}

	int div = 2;
	if (indx) // indx > 0
		div = (prime_list->arr[indx - 1] > 2) ? prime_list->arr[indx - 1] : 2; // продолжаем с последнего делителя

	for (div += 1; div < div_max; div++)
	{
		if (num % div == 0) 	// если делится, то число составное
			return false;
	}

	return true;
}


int get_concat_list(list_t* concat_list, list_t* prime_list, const list_t* num_list, int num)
{
	int fact = 10;

	for (int i = num / 10; i > 0; i /= 10)	// num = 123
		fact *= 10;							// fact = 1000

	int indx = 0;
	int num2;
	while ((num2 = num_list->arr[indx]) < num && indx < num_list->nums)
	{
		int fact2 = 10;
		for (int i = num2 / 10; i > 0; i /= 10) // num2 = 4
			fact2 *= 10;						// fact2 = 10

		if (is_prime(prime_list, num * fact2 + num2) && // если является простым числом 123 * 10 + 4 = 1234
			is_prime(prime_list, num2 * fact + num))	// и является простым числом 4 * 1000 + 123 = 4123
			concat_list->arr[concat_list->nums++] = num2;			// заносим число в массив с объединениями
		indx++;
	}

	return concat_list->nums;
}
