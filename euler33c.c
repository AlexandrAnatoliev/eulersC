// euler33c - Дроби, сократимые по цифрам

// Дробь 49 / 98 является любопытной, поскольку неопытный математик, пытаясь сократить ее, будет ошибочно полагать,
// что 49 / 98 = 4 / 8, являющееся истиной, получено вычеркиванием девяток.
//
// Дроби вида 30 / 50 = 3 / 5 будем считать тривиальными примерами.
//
// Существует ровно 4 нетривиальных примера дробей подобного типа,
// которые меньше единицы и содержат двухзначные числа как в числителе, так и в знаменателе.
//
// Пусть произведение этих четырех дробей дано в виде несократимой дроби(числитель и знаменатель дроби не имеют общих сомножителей).
// Найдите знаменатель этой дроби.

#include <stdio.h>
#include <stdbool.h>
#include <time.h> 		// for clock_t, clock(), CLOCKS_PER_SEC

typedef struct fraction // тип данных - дробь	(12 / 34)
{
	int numerator;	 	// числитель			(12)
	int num_tens;	 	// десятки 				(1)
	int num_ones;	 	// единицы 				(2)
	int denominator; 	// знаменатель 			(34)
	int den_tens;	 	// десятки 				(3)
	int den_ones;		// единицы 				(4)
} fract_t;

int fraction_init(fract_t *fraction, int num_tens, int num_ones, int den_tens, int den_ones);
int siplify(int *numer, int *denom);
bool is_non_trivial(fract_t *fraction, int numer, int denom);

int main(void)
{
	double time_spent = 0.0; 												// для хранения времени выполнения кода
	clock_t begin = clock(); 												// СТАРТ таймера

	fract_t fraction;		 												// дробь для расчетов
	int answ_numer = 1;														// числитель дроби ответа
	int answ_denom = 1;														// знаменатель

	// числитель дроби aB / Bc не должен быть больше знаменателя => aB < Bc => a < B
	for (int diagonal = 1; diagonal < 10; diagonal++) 						// перебираем цифры в диагонали (aB / Bc)
	{	
		for (int numer = 1; numer < diagonal; numer++)						// в числителе
		{
			for (int denom = 1; denom < 10; denom++) 						// и знаменателе
			{										 	
				fraction_init(&fraction, numer, diagonal, diagonal, denom);	// дробь (aB / Bc)
				if (is_non_trivial(&fraction, numer, denom))				// проверка условия задания
				{
					answ_numer *= numer;									// заносим ответ
					answ_denom *= denom;
				}
			}
		}
	}

	// числитель дроби Ab / cA не должен быть больше знаменателя => Ab < cA => A < c
	for(int diagonal = 1; diagonal < 10; diagonal++) 						// перебираем цифры в диагонали (Ab / cA)
	{
		for (int numer = 1; numer < 10; numer++) 							// в числителе
		{
			for (int denom = diagonal; denom < 10; denom++) 				// знаменателе
			{
				fraction_init(&fraction, diagonal, numer, denom, diagonal);	// дробь (Ab / cA)
				if (is_non_trivial(&fraction, numer, denom))				// проверка условия задания
				{
					answ_numer *= numer;									// заносим ответ
					answ_denom *= denom;
				}
			}
		}
	}

	siplify(&answ_numer, &answ_denom); 										// упрощаем дробь ответа

	clock_t end = clock();								  					// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 					// время работы в секундах

	printf("Ответ = %d время = %f\n", answ_denom, time_spent); 				// выводим результат и время работы программы
	return 0;
}

int fraction_init(fract_t *fraction, int num_tens, int num_ones, int den_tens, int den_ones)
// Функция для присваивания дроби начальных значений
// Параметры:	fraction	- дробь					(12/34)
//				num_tens	- десятки числителя		(1)
//				num_ones	- единицы числителя		(2)
//				den_tens	- десятки знаменателя	(3)
//				den_ones	- единицы знаменателя	(4)
{
	fraction->num_tens = num_tens;
	fraction->num_ones = num_ones;
	fraction->numerator = num_tens * 10 + num_ones;
	fraction->den_tens = den_tens;
	fraction->den_ones = den_ones;
	fraction->denominator = den_tens * 10 + den_ones;

	return 0;
}

int siplify(int *numer, int *denom)
// Функция для упрощения дроби (11/33)
// Параметры:	num_dig	- числитель		(11)
//				num_den	- знаменатель	(33)
{
	for (int dev = *numer; dev > 0; dev--)
	{
		if (*numer % dev == 0 && *denom % dev == 0) // перый общий делитель - максимальный
		{
			*numer /= dev;
			*denom /= dev;
			return 0;
		}
	}
	return 0;
}

bool is_non_trivial(fract_t *fraction, int numer, int denom)
// Функция для проверки не является ли дробь тривиальной
// Параметры:	fraction	- дробь									(12/24)
//				num_dig		- числитель	без повторяющейся цифры		(1)
//				num_den		- знаменатель без повторяющейся цифры	(4)
// return:		false		- не является тривиальной дробью
{
	int numerator = fraction->numerator;	 // числитель
	int denominator = fraction->denominator; // знаменатель

	siplify(&numerator, &denominator);		// упрощаем дробь 		12/24
	siplify(&numer, &denom);				// упрощаем дробь 		1/4
	if (numerator == numer && denominator == denom)
		return true;

	return false;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h> 											// for clock_t, clock(), CLOCKS_PER_SEC

// bool simplify(int arr_arg[])
// //принимает дробь в виде массива и сокращает ее
// //возвращает false если не сократима
// {
// 	for (int i = arr_arg[0]; i > 1; i--)
// 	{
// 		if ((arr_arg[0] % i == 0) && (arr_arg[1] % i == 0)) //если есть общий делитель
// 		{
// 			arr_arg[0] /= i;                                //сокращаем обе части дроби
// 			arr_arg[1] /= i;
// 			return true;
// 		}
// 	}
// 	return false;
// }

// bool is_possible(int arr_arg[])
// //проверяет возможность найти искомую дробь - наличие одинаковых цифр в числителе и знаменателе по диагонали
// {
// 	return (arr_arg[0]/10 == arr_arg[1]%10) || (arr_arg[1] / 10 == arr_arg[0] % 10);
// }

// int del_nums(int arr_arg[])
// //удаляет одинаковые цифры в числителе и знаменателе
// {
// 	if (arr_arg[0] / 10 == arr_arg[1] % 10)
// 	{
// 		arr_arg[0] %= 10;
// 		arr_arg[1] /= 10;
// 	}

// 	else if (arr_arg[1] / 10 == arr_arg[0] % 10)
// 	{
// 		arr_arg[1] %= 10;
// 		arr_arg[0] /= 10;
// 	}
// 	return 0;
// }

// int main(void)
// {
// 	double time_spent = 0.0; 								// для хранения времени выполнения кода
// 	clock_t begin = clock(); 								// СТАРТ таймера

// 	int arr1[2] = { 0 };										//массив для записи дроби
// 	int arr2[2] = { 0 };										//дополнительный массив для записи нетривиальной дроби
// 	int answ[2] = { 1, 1 };										//массив для записи ответа

// 	for (int num = 10; num < 100; num++)						//числа в числителе и знаменателе - двузначные
// 	{
// 		for (int den = num + 1; den < 100; den++)				//дробь < 1
// 		{
// 			arr1[0] = num;
// 			arr1[1] = den;
// 			if (is_possible(arr1))                              //если есть одинаковые цифры в числителе и знаменателе
// 			{
// 				arr2[0] = arr1[0];
// 				arr2[1] = arr1[1];
// 				del_nums(arr2);                                 //удаляем одинаковые цифры из числителя и знаменателя
// 				simplify(arr1);                                 //сокращаем дробь
// 				simplify(arr2);                                 //сокращаем дробь, из которой удалены повторяющиеся цифры

// 				if (arr1[0] == arr2[0] && arr1[1] == arr2[1])	//если сокращенные дроби равны
// 				{
// 					answ[0] *= arr1[0];							//перемножаем числители
// 					answ[1] *= arr1[1];							//перемножаем знаменатели
// 				}
// 			}
// 		}
// 	}
// 	simplify(answ);												//сокращаем дробь ответа
// 	// printf("%d", answ[1]);
// 	clock_t end = clock();								  	// СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ[1], time_spent);	// выводим результат и время работы программы
// 	return 0;
// }
