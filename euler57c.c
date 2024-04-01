// euler57c - Приближения квадратного корня

// Можно убедиться в том, что квадратный корень из двух можно выразить в виде бесконечно длинной дроби.

// √ 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...

// Приблизив это выражение для первых четырех итераций, получим:

// 1 + 1/2 = 3/2 = 1.5
// 1 + 1/(2 + 1/2) = 7/5 = 1.4
// 1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
// 1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

// Следующие три приближения: 99/70, 239/169 и 577/408, а восьмое приближение, 1393/985, является первым случаем,
// в котором количество цифр в числителе превышает количество цифр в знаменателе.

// У скольких дробей длина числителя больше длины знаменателя в первой тысяче приближений выражения?

#include <stdio.h>
#include <stdbool.h>
#include <time.h> // для clock_t, clock(), CLOCKS_PER_SEC

#define LEN_ARR 400

typedef struct big_num // структура "большое число"
{
	char arr[LEN_ARR]; // массив для хранения цифр числа
	int len;		   // длина числа
} big_t;

typedef struct fraction // структура "дробь"
{
	big_t numer; // числитель
	big_t denom; // знаменатель
} fract_t;

int fract_init(fract_t *fract, int num, int den);
int fract_mult(fract_t *fract, int num);
int fract_plus(fract_t *fract, int num);
int fract_reciprocal(fract_t *fract);

int main(void)
{
	double time_spent = 0.0;
	clock_t begin = clock(); // СТАРТ таймера

	int answ = 0;
	fract_t one_plus_fraction;
	fract_t fraction;

	fract_init(&fraction, 1, 2); // 1/2

	for (int i = 1; i < 1000; i++)
	{
		fract_plus(&fraction, 2);		   // 2 + 1/2 = 5/2
		fract_reciprocal(&fraction);	   // 1/ (5/2) = 2/5
		one_plus_fraction = fraction;	   					// сохраняем результат
		fract_plus(&one_plus_fraction, 1); 					// 1 + 2/5 = 7/5
		if (one_plus_fraction.numer.len > one_plus_fraction.denom.len)
			answ++;
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 	// выводим результат и время работы программы
	return 0;
}

int fract_init(fract_t *fract, int num, int den)
// Функция для присваиванию начальных значений дроби
// Параметры:   fract   - дробь
//              num     - числитель
//              power   - знаменатель
{
	fract->numer.len = 0;
	fract->denom.len = 0;

	// обнуляем массивы
	for (int i = 0; i < LEN_ARR; i++)
	{
		fract->denom.arr[i] = 0;
		fract->numer.arr[i] = 0;
	}

	while (num) // заносим начальные данные в дробь
	{
		fract->numer.arr[fract->numer.len++] = num % 10;
		num /= 10;
	}

	while (den) // заносим начальные данные в дробь
	{
		fract->denom.arr[fract->denom.len++] = den % 10;
		den /= 10;
	}

	return 0;
}

int fract_mult(fract_t *fract, int num)
// Функция для умножения дроби на натуральное число
// Параметры:   fract   - дробь
//              num     - натуральное число
{
	int cnt = 0;
	int residue = 0;
	while (residue || cnt < fract->numer.len) // умножаем числитель на число
	{
		residue += fract->numer.arr[cnt] * num;
		fract->numer.arr[cnt++] = residue % 10;
		residue /= 10;
	}

	fract->numer.len = (fract->numer.len > cnt) ? fract->numer.len : cnt; // обновляем длину числа
}

int fract_plus(fract_t *fract, int num)
// Функция для прибавления к дроби натурального числа
// Параметры:   fract   - дробь
//              num     - натуральное число
{
	int cnt = 0;
	fract_t fr_num;

	// имеют один тип данных big_t потому можно просто копировать
	fr_num.numer = fract->denom; // заносим в число 1 в виде приведенной к общему основанию дроби 1234/1234
	fr_num.denom = fract->denom; // можно убрать!

	fract_mult(&fr_num, num); // записываем множитель в виде приведенной к общему основанию дроби

	int number = 0;
	while (number || cnt < fract->numer.len || cnt < fr_num.numer.len) // заносим данные в дробь
	{
		number += fract->numer.arr[cnt] + fr_num.numer.arr[cnt];
		fract->numer.arr[cnt++] = number % 10;
		number /= 10;
	}

	fract->numer.len = (fract->numer.len > cnt) ? fract->numer.len : cnt; // обновляем длину числа
}

int fract_reciprocal(fract_t *fract)
// Функция для получения обратной дроби
// a / b -> b / a
// Параметры:   fract   - дробь
{
	big_t temp;
	temp = fract->numer;
	fract->numer = fract->denom; // медленно?
	fract->denom = temp;

	return 0;
}
