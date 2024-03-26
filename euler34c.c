// euler34c - Факториалы цифр

// 145 является любопытным числом, поскольку 1!+ 4!+ 5!= 1 + 24 + 120 = 145.
//
// Найдите сумму всех чисел, каждое из которых равно сумме факториалов своих цифр.
//
// Примечание: поскольку 1!= 1 и 2!= 2 не являются суммами, учитывать их не следует.

#include <stdio.h>
#include <time.h> 											// for clock_t, clock(), CLOCKS_PER_SEC

#define MAX_NUM 7 * (1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9) 	// 7 * 9!

int main(void)
{
	double time_spent = 0.0; 								// для хранения времени выполнения кода
	clock_t begin = clock(); 								// СТАРТ таймера

	int fact[10] = {1}; 									// факториал числа = массив[число], 0! = 1
	int answ = 0;

	for (int num = 1; num < 10; num++) 						// заполняем массив значениями факториалов
		fact[num] = fact[num - 1] * num;

	for (int number = 10; number < MAX_NUM; number++) 		// 9! = 362880 - 6-значное число =>
	{												  		// сумма факториалов 10 чисел - максимум 7-значное число
		int sum_fact = 0;
		int num = number;

		while (num) 										// раскладываем число на цифры
		{
			sum_fact += fact[num % 10];						// суммируем факториалы цифр
			num /= 10;
		}

		if (number == sum_fact)								// искомое число
			answ += number;
	}

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent);	// выводим результат и время работы программы
	return 0;
}

// #include <stdio.h>
// #include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

// int main(void)
// {
// 	double time_spent = 0.0; // для хранения времени выполнения кода
// 	clock_t begin = clock(); // СТАРТ таймера

// 	int fact_arr[10] = {0}; // факториал числа = массив[число]
// 	fact_arr[0] = 1;		// 0! = 1
// 	int fact = 1;
// 	int answ = 0;
// 	int sum_fact = 0;
// 	int num = 0;

// 	for (int i = 1; i < 10; i++) // заполняем массив значениями факториалов
// 	{
// 		fact *= i;
// 		fact_arr[i] = fact;
// 	}

// 	for (int i = 10; i < 10000000; i++) // 9! = 362880 - 6-значное число =>
// 	{									// сумма факториалов 10 чисел - максимум 7-значное число
// 		sum_fact = 0;
// 		num = i;

// 		while (num) // раскладываем число на цифры
// 		{
// 			sum_fact += fact_arr[num % 10];
// 			num /= 10;
// 		}

// 		if (i == sum_fact)
// 			answ += i;
// 	}

// 	clock_t end = clock();								  // СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы
// 	return 0;
// }
