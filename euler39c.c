// euler39c - Целые прямоугольные треугольники

// Если p - периметр прямоугольного треугольника с целочисленными длинами сторон{ a,b,c }, то существует ровно три решения для p = 120:
//
// {20, 48, 52}, { 24,45,51 }, { 30,40,50 }
//
// Какое значение p ≤ 1000 дает максимальное число решений ?

#include <stdio.h>
#include <stdbool.h>

bool is_right_angle(int a_arg, int b_arg, int c_arg)
// Определяет, является ли треугольник прямогугольным
// если a^2 + b^2 = c^2, то a, b, c - Пифагоровы числа
// return:	true - треугольник прямогугольный
{
	return a_arg * a_arg + b_arg * b_arg == c_arg * c_arg;
}


int main(void)
{
	int answ = 0;
	int cnt_max = 0;
	int cnt = 0;

	for (int p = 3; p <= 1000; p++)
	{
		cnt = 0;
		for (int c = p / 2; c > 0; c--)							// p = a + b + c => т.к. a + b > c => c < p/2
		{
			int a_plus_b = p - c;								// a_plus_b = a + b > c
			for (int a = a_plus_b; a >= a_plus_b / 2; a--)		// a и b равнозначны, после ab/2 решения будут повторяться
				if (is_right_angle(a, a_plus_b - a, c))
					cnt++;		
		}

		if (cnt_max < cnt)
		{
			cnt_max = cnt;
			answ = p;
		}
	}
	printf("%d", answ);											// 840
	return 0;	
}
