// euler42c - Закодированные треугольные числа

// n - й член последовательности треугольных чисел задается как tn = ½n(n + 1).
// Таким образом, первые десять треугольных чисел :
//
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
//
// Преобразовывая каждую букву в число, соответствующее ее порядковому номеру в алфавите, и складывая эти значения,
// мы получим числовое значение слова. Для примера, числовое значение слова SKY равно 19 + 11 + 25 = 55 = t10.
// Если числовое значение слова является треугольным числом, то мы назовем это слово треугольным словом.
//
// Используя words.txt(щелкнуть правой кнопкой мыши и выбрать 'Save Link/Target As...'), 16 КБ текстовый файл,
// содержащий около двух тысяч часто используемых английских слов, определите, сколько в нем треугольных слов.

#include <stdio.h>
#include <stdbool.h>
#include <time.h>						// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h> 					// русский язык в printf()
#include <stdlib.h>

#define LEN_ARR 1000
#define FILE_NAME "euler42c.txt"

typedef struct text
{
	char *arr;							// ссылка на массив
	int lenght; 						// длина массива
} text_t;

text_t open_file_malloc_ar(const char *name_file);

int main(void)
{
	setlocale(LC_ALL, "Rus"); 			// русский язык в printf()

	double time_spent = 0.0; 			// для хранения времени выполнения кода
	clock_t begin = clock(); 			// СТАРТ таймера

	text_t text; 						// структура для хранения имен
	int answ = 0;
	int word_value = 0; 				// закодированное значение слова

	int triangle = 1;				 	// треугольное число
	int n = 1;						 	// порядковый номер треугольного числа
	char is_triangle[LEN_ARR] = {0}; 	// массив[треугольное число] = 1

	while (triangle < LEN_ARR) 			// заполняем массив треугольными числами
	{
		is_triangle[triangle] = 1;
		triangle += ++n;
	}

	text = open_file_malloc_ar(FILE_NAME);

	text_t start_word_fl = false; 							// флаг начала слова
	for (int i = 0; i < text.lenght; i++)
	{
		if (text.arr[i] == '\"')
			start_word_fl = !start_word_fl; 				// меняем флаг начала/конца слова

		if (start_word_fl && text.arr[i] != '\"') 			// читаем слово и складываем числовые значения
			word_value += (text.arr[i] - 64);	  			// 'A' = 65

		if (!start_word_fl) 								// окончание слова
		{
			if (is_triangle[word_value]) 					// числовое значение слова является треугольным числом
				answ++;
			word_value = 0; 								// обнуляем значение слова
		}
	}

	free(text.arr); 										// не забыть освободить место в памяти, выделяемое под массив

	clock_t end = clock();								  	// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); 	// выводим результат и время работы программы

	return 0;
}

text_t open_file_malloc_ar(const char *name_file)
// Функция, которая открывает файл, выделяет место под массив и копирует содержимое в него
// параметры:   *name_file  - название / путь к файлу строкой "euler22text.txt"
// return:      text      	- структура, содержащая ссылку на массив и длину массива
{
	text_t text;

	FILE *file;
	file = fopen(name_file, "r"); 						// открываем файл на чтение

	if (file == NULL)
		printf("file_open_malloc_ar(): ошибка при открытии файла \"%s\".\n", name_file);

	fseek(file, 0, SEEK_END);							// устанавливаем файловую позицию в конец файла
	text.lenght = ftell(file);							// получаем значение файловой позиции (конец = длина файла)
	text.arr = malloc(text.lenght); 					// выделяем место под массив
	fseek(file, 0, SEEK_SET);							// устанавливаем файловую позицию в начало файла

	while (fgets(text.arr, text.lenght, file) != NULL) 	// до конца файла
		fputs(text.arr, file);						   	// копируем содержимое файла в массив

	fclose(file); 										// закрываем файл

	return text;
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <time.h>											// for clock_t, clock(), CLOCKS_PER_SEC
// #include <locale.h> 										// русский язык в printf()

// int get_triangle_num(int num_arg)
// // возвращает треугольное число по номеру
// // параметры:	num_arg		- номер числа
// // return:		    		- треугольное число
// {
// 	return (num_arg * (num_arg + 1)) / 2;                   // скобки для ясности (чтобы избежать ситуаций -> 3/2 = 1)
// }

// int main(void)
// {
// 	setlocale(LC_ALL, "Rus"); 								// русский язык в printf()

// 	double time_spent = 0.0; 								// для хранения времени выполнения кода
// 	clock_t begin = clock(); 								// СТАРТ таймера

// 	int answ = 0;
// 	int word_value = 0;
// 	char triangle_arr[1000] = { 0 };				        // массив[треугольное число] = 1

//     for(int i = 1; i < 45; i++)
//         triangle_arr[get_triangle_num(i)] = 1;             	// заполняем массив треугольными числами

// 	FILE *file;
//     char ch;

// 	bool start_fin_fl = false;								// флаг чтения слова "начало"/"конец"

//     file = fopen("euler42c.txt", "r");           			// открываем файл на чтение

//     if (file == NULL) 										// если файл не открылся
//     {
//         printf("Failed to open file.\n");
//         return 1;
//     }

//     while ((ch = fgetc(file)) != EOF)               		// пока не достигли конца файла
//     {
//         if(ch == '\"')                               		// start->"ABILITY"<-finish
// 			start_fin_fl = !start_fin_fl;

// 		if(start_fin_fl && ch != '\"')						// читаем слово и складываем числовые значения
// 			word_value += (ch - 64);						// 'A' = 65

// 		if(!start_fin_fl)									// окончание слова
// 		{
// 			if(triangle_arr[word_value])					// числовое значение слова является треугольным числом
// 				answ++;
// 			word_value = 0;
// 		}
//     }

//     fclose(file);

// 	clock_t end = clock();								  	// СТОП таймера
// 	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; 	// время работы в секундах

// 	printf("Ответ = %d время = %f\n", answ, time_spent); 	// выводим результат и время работы программы

// 	return 0;
// }