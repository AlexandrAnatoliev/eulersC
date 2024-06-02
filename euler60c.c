// euler60c - Объединение пары в простое число

// Простые числа 3, 7, 109 и 673 достаточно замечательны.Если взять любые два из них и объединить их в произвольном порядке,
// в результате всегда получится простое число.Например, взяв 7 и 109, получатся простые числа 7109 и 1097.
// Сумма этих четырех простых чисел, 792, представляет собой наименьшую сумму элементов множества из четырех простых чисел,
// обладающих данным свойством.
//
// Найдите наименьшую сумму элементов множества из 5 простых чисел, для которых объединение любых двух даст новое простое число.
//  26033: 13 - 5197 - 5701 - 6733 - 8389

#include <stdio.h>
#include <time.h>	 // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>	 // русский язык в printf()
#include <stdbool.h> // для красоты кода использую bool
#include <math.h>
#include <stdlib.h>

// enum primes_concat // сколько простых чисел объединено
// {
// 	one,
// 	two,
// 	three,
// 	four,
// 	five
// };

typedef struct list // список чисел
{
	int *arr; // указатель на массив для хранения простых чисел
	int nums; // количество чисел = длина массива
	int indx; // индекс текущего числа
} list_t;

#define MAX_CONCAT 5 // искомое количество объединений

bool list_calloc(list_t *list, int lenght);
bool is_prime(list_t *prime_list, int num);
int get_concat_list(list_t *prime_list, const list_t *num_list, list_t *concat_list, int num);

int main(void)
{
	setlocale(LC_ALL, "Rus"); // русский язык в printf()

	double time_spent = 0.0; // для хранения времени выполнения кода
	clock_t begin = clock(); // СТАРТ таймера

	int answ = 0;

	int max_primes = 1500;
	printf("ввод: ");
	scanf("%d", &max_primes);

	list_t lists[MAX_CONCAT]; // массив списков простых чисел

	for (int primes = 0; primes < MAX_CONCAT; primes++) // создаем 5 списков чисел
		list_calloc(&lists[primes], max_primes);

	int num = 2;
	while (lists[0].indx < lists[0].nums) // ищем первые max_primes = 1500 простых чисел
	{
		if (is_prime(&lists[0], num))
			lists[0].arr[lists[0].indx++] = num;
		num++;
	}

	lists[0].indx = 0;	   // переходим к началу первого списка
	int numb_list = 0;	   // текущий номер списка
	int search_primes = 3; // количество чисел в списке, объединение с которыми даст новое простое число

	while (numb_list < 4 && lists[0].indx < max_primes)
	{
		lists[numb_list + 1].nums = 0; // обнуляем следующий массив - с результатами вычислений
		lists[numb_list + 1].indx = 0;

		if (lists[numb_list].indx < lists[numb_list].nums && get_concat_list(&lists[0], &lists[numb_list], &lists[numb_list + 1], lists[numb_list].arr[lists[numb_list].indx]) > search_primes)
		{
			numb_list++; // переходим к следующему массиву
			search_primes--;
			continue;
		}

		if (lists[numb_list].indx >= lists[numb_list].nums) // массив кончился
		{
			numb_list--; // переходим к предыдущему массиву
			search_primes++;
		}

		lists[numb_list].indx++; // переходим к следующему числу массива
	}

	for (int i = 0; i < 5; i++)
	{
		printf("%d ", lists[i].arr[lists[i].indx]);
		answ += lists[i].arr[lists[i].indx];
	}

	for (int primes = 0; primes < MAX_CONCAT; primes++) // стираем 5 списов чисел
		free(lists[primes].arr);

	clock_t end = clock();								  // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы
	return 0;
}

bool list_calloc(list_t *list, int lenght)
{
	list->arr = calloc(1, lenght * sizeof(int));
	list->indx = 0;
	list->nums = lenght;

	return true;
}

bool is_prime(list_t *prime_list, int num)
// Функция для определения простого числа
// Параметры:	prime_arr[]       	- массив с ранее вычисленными простыми числами
//              num                 - проверяемое число
// return:      true                - если число простое!
{
	int div_max = sqrt(num) + 1; // выносим вычисление квадратного корня из цикла for
	int indx = 0;

	while (prime_list->arr[indx] && prime_list->arr[indx] < div_max) // перебираем уже вычисленные простые (!) делители
	{
		if (num % prime_list->arr[indx] == 0) // если делится
			return false;
		indx++;
	}

	int div = ((indx - 1 > 0) && (prime_list->arr[indx - 1] > 2)) ? prime_list->arr[indx - 1] : 2; // начинаем с последнего делителя, если он есть

	for (int i = div; i < div_max; i++)
	{
		if (num % i == 0) // если делится, то число составное
			return false;
	}

	return true;
}

int get_concat_list(list_t *prime_list, const list_t *num_list, list_t *concat_list, int num)
{
	int fact = 10;

	for (int i = num / 10; i > 0; i /= 10) // num = 123
		fact *= 10;						   // fact = 1000

	int indx = 0;
	int num2;
	while ((num2 = num_list->arr[indx]) < num && indx < num_list->nums)
	{
		int fact2 = 10;
		for (int i = num2 / 10; i > 0; i /= 10) // num2 = 4
			fact2 *= 10;						// fact2 = 10

		if (is_prime(prime_list, num * fact2 + num2) &&	  // если является простым числом 123 * 10 + 4 = 1234
			is_prime(prime_list, num2 * fact + num))	  // и является простым числом 4 * 1000 + 123 = 4123
			concat_list->arr[concat_list->nums++] = num2; // заносим число в массив с объединениями
		indx++;
	}

	return concat_list->nums;
}
