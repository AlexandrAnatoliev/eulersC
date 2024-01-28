// euler18c - Максимальная сумма пути 1

// Начиная в вершине треугольника (см. пример ниже) и перемещаясь вниз на смежные числа,
// максимальная сумма до основания составляет 23.

//    3
//   7 4
//  2 4 6
// 8 5 9 3

// То есть, 3 + 7 + 4 + 9 = 23.

// Найдите максимальную сумму пути от вершины до основания следующего треугольника:

// 75
// 95 64
// 17 47 82
// 18 35 87 10
// 20 04 82 47 65
// 19 01 23 75 03 34
// 88 02 77 73 07 63 67
// 99 65 04 28 06 16 70 92
// 41 41 26 56 83 40 80 70 33
// 41 48 72 33 47 32 37 16 94 29
// 53 71 44 65 25 43 91 52 97 51 14
// 70 11 33 28 77 73 17 78 39 68 17 57
// 91 71 52 38 17 14 91 43 58 50 27 29 48
// 63 66 04 68 89 53 67 30 73 16 69 87 40 31
// 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

// Примечание: Так как в данном треугольнике всего 16384 возможных маршрута от вершины до основания,
// эту задачу можно решить проверяя каждый из маршрутов. Однако похожая Задача 67 с треугольником,
// состоящим из сотни строк, не решается перебором (brute force) и требует более умного подхода! ;o)

// продвинутый вариант
//  #include <stdio.h>
//  void get_path(const int arr[], int *indx, int *num1, int *num2, int * sum_num)
//  //принимает проверяемый массив, индекс первого числа в массиве, два числа из передыдущего массива,
//  //сумма пути от вершины
//  //выбирает число по которому пойдет путь по развилке
//  {
//      //из трех чисел текущего массива выбираются два максимальные
//      int max_num1 = (arr[*indx] > arr[*indx + 1]) ? arr[*indx] : arr[*indx + 1];
//      int max_num2 = (arr[*indx + 1] > arr[*indx + 2]) ? arr[*indx + 1] : arr[*indx + 2];
//      //проверяются два пути: число1/число2 -> числа текущего массива
//      int max_num = ((*num1 + max_num1) > (*num2 + max_num2)) ? *num1 : *num2;
//      *indx = (max_num == *num1) ? *indx : *indx + 1;
//      //новая развилка (текущий массив)
//      *num1 = arr[*indx];
//      *num2 = arr[*indx + 1];
//      *sum_num += max_num;                                //+выбранное число из предыдущего массива
//  }

// int main (void)
// {
//     int max_num = 75;                                   //вершина
//     int st2[] = {95,64};
//     int st3[] = {17,47,82};
//     int st4[] = {18,35,87,10};
//     int st5[] = {20,04,82,47,65};
//     int st6[] = {19,01,23,75,03,34};
//     int st7[] = {88,02,77,73,07,63,67};
//     int st8[] = {99,65,04,28,06,16,70,92};
//     int st9[] = {41,41,26,56,83,40,80,70,33};
//     int st10[] = {41,48,72,33,47,32,37,16,94,29};
//     int st11[] = {53,71,44,65,25,43,91,52,97,51,14};
//     int st12[] = {70,11,33,28,77,73,17,78,39,68,17,57};
//     int st13[] = {91,71,52,38,17,14,91,43,58,50,27,29,48};
//     int st14[] = {63,66,04,68,89,53,67,30,73,16,69,87,40,31};
//     int st15[] = {04,62,98,27,23,9,70,98,73,93,38,53,60,04,23};

//     int sum_num = 0;                                    //сумма чисел на пути от вершины
//     int num1 = st2[0];                                  //проверяемые числа на развилке
//     int num2 = st2[1];
//     int indx = 0;                                       //индекс первого числа развилки

//     sum_num += max_num;                                 //+вершина
//     //определяем путь, +выбранные числа на развилках
//     get_path(st3, &indx, &num1, &num2, &sum_num);
//     get_path(st4, &indx, &num1, &num2, &sum_num);
//     get_path(st5, &indx, &num1, &num2, &sum_num);
//     get_path(st6, &indx, &num1, &num2, &sum_num);
//     get_path(st7, &indx, &num1, &num2, &sum_num);
//     get_path(st8, &indx, &num1, &num2, &sum_num);
//     get_path(st9, &indx, &num1, &num2, &sum_num);
//     get_path(st10, &indx, &num1, &num2, &sum_num);
//     get_path(st11, &indx, &num1, &num2, &sum_num);
//     get_path(st12, &indx, &num1, &num2, &sum_num);
//     get_path(st13, &indx, &num1, &num2, &sum_num);
//     get_path(st14, &indx, &num1, &num2, &sum_num);
//     get_path(st15, &indx, &num1, &num2, &sum_num);
//     //прверяем последнюю развилку
//     max_num = (num1 > num1) ? num1 : num2;
//     sum_num += max_num;
//     printf("%d",sum_num);
//     return 0;
// }

#include <stdio.h>
#include <time.h>                                           // for clock_t, clock(), CLOCKS_PER_SEC

int main(void)
{   
    double time_spent = 0.0;                                // для хранения времени выполнения кода
    clock_t begin = clock();                                // СТАРТ таймера

    int arr[15][16] = {
        {75},
        {95, 64},
        {17, 47, 82},
        {18, 35, 87, 10},
        {20, 04, 82, 47, 65},
        {19, 01, 23, 75, 03, 34},
        {88, 02, 77, 73, 07, 63, 67},
        {99, 65, 04, 28, 06, 16, 70, 92},
        {41, 41, 26, 56, 83, 40, 80, 70, 33},
        {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
        {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
        {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
        {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
        {63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
        {04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23}};

    int answ;

    for (int row = 13; row >= 0; row--)                     // перебираем ряды снизу вверх
    {
        int indx = 0;
        while (arr[row][indx])                              // проходим по ряду пока в клетке есть число
        {
            // прибавляем к клетке большее из значений двух смежных клеток нижнего ряда
            arr[row][indx] += (arr[row + 1][indx] > arr[row + 1][indx + 1]) ? arr[row + 1][indx] : arr[row + 1][indx + 1];
            indx++;
        }
    }

    answ = arr[0][0];                                       // после перебора вершина хранит максимальную сумму пути

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("answer = %d runtime = %f\n", answ, time_spent); // выводим результат и время работы программы
    return 0;
}