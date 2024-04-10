// euler39c - Целые прямоугольные треугольники

// Если p - периметр прямоугольного треугольника с целочисленными длинами сторон{ a,b,c }, то существует ровно три решения для p = 120:
//
// {20, 48, 52}, { 24,45,51 }, { 30,40,50 }
//// 840
// Какое значение p ≤ 1000 дает максимальное число решений ?

// euler39c - Целые прямоугольные треугольники

// Если p - периметр прямоугольного треугольника с целочисленными длинами сторон{ a,b,c }, то существует ровно три решения для p = 120:
//
// {20, 48, 52}, { 24,45,51 }, { 30,40,50 }
//// 840
// Какое значение p ≤ 1000 дает максимальное число решений ?

#include <stdio.h>
#include <time.h> 											// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>

#define MAX_PER 1000 										// максимальный периметр треугольника

int main(void)
{
	setlocale(LC_ALL, "Rus"); 								// русский язык в printf()

	double time_spent = 0.0; 								// для хранения времени выполнения кода
	clock_t begin = clock(); 								// СТАРТ таймера

	int answ = 0;
	int answ_arr[MAX_PER + 1] = {0}; 						// для каждого периметра считаем решения

	static int sqrt_arr[MAX_PER * MAX_PER] = {0};
	for (int i = 1; i < MAX_PER; i++) 						// заносим в массив квадратные корни натуральных чисел
		sqrt_arr[i * i] = i;

	for (int a = 1; a < MAX_PER; a++) 						// перебираем катеты a и b
	{
		for (int b = a; b < (MAX_PER - a); b++) 			// b > a чтобы катеты не повторялись
		{
			int c = sqrt_arr[a * a + b * b]; 				// гипотенуза треугольника

			if (c && (a + b + c) < MAX_PER) 				// если целочисленная и сумма сторон не превышает максимальный периметр
				answ_arr[a + b + c]++;						// учитываем это решение для данного периметра
		}
	}

	for (int perim = 0; perim < MAX_PER + 1; perim++) 		// ищем ответ в массиве
		answ = (answ_arr[answ] > answ_arr[perim]) ? answ : perim;

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 	// выводим результат и время работы программы
	return 0;
}

// #include <stdio.h>
// #include <stdbool.h>

// bool is_right_angle(int a_arg, int b_arg, int c_arg)
// // Определяет, является ли треугольник прямогугольным
// // если a^2 + b^2 = c^2, то a, b, c - Пифагоровы числа
// // return:	true - треугольник прямогугольный
// {
// 	return a_arg * a_arg + b_arg * b_arg == c_arg * c_arg;
// }

// int main(void)
// {
// 	int answ = 0;
// 	int cnt_max = 0;
// 	int cnt = 0;

// 	for (int p = 3; p <= 1000; p++)
// 	{
// 		cnt = 0;
// 		for (int c = p / 2; c > 0; c--)							// p = a + b + c => т.к. a + b > c => c < p/2
// 		{
// 			int a_plus_b = p - c;								// a_plus_b = a + b > c
// 			for (int a = a_plus_b; a >= a_plus_b / 2; a--)		// a и b равнозначны, после ab/2 решения будут повторяться
// 				if (is_right_angle(a, a_plus_b - a, c))
// 					cnt++;
// 		}

// 		if (cnt_max < cnt)
// 		{
// 			cnt_max = cnt;
// 			answ = p;
// 		}
// 	}
// 	printf("%d", answ);
// 	return 0;
// }
