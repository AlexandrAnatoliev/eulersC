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

#include <stdio.h>

int main(void)
{
    //    3
    //   7 4
    //  2 4 6
    // 8 5 9 3
    
    // int st1[]= {3};
    // int st2[]= {7,4};
    // int st3[]= {2,4,6};
    // int st4[]= {8,5,9,3};
    // int sum_num = 3;                                         //23
    // int max_num = 0;
    // int i_num = 0;

    // max_num = (st2[i_num] > st2[i_num + 1]) ? st2[i_num] : st2[i_num + 1];
    // i_num = (max_num == st2[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st3[i_num] > st3[i_num + 1]) ? st3[i_num] : st3[i_num + 1];
    // i_num = (max_num == st3[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st4[i_num] > st4[i_num + 1]) ? st4[i_num] : st4[i_num + 1];
    // i_num = (max_num == st4[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // int sum_num = 75;                                           //1064
    // int st2[] = {95,64}; 
    // int st3[] = {17,47,82}; 
    // int st4[] = {18,35,87,10}; 
    // int st5[] = {20,04,82,47,65};
    // int st6[] = {19,01,23,75,03,34}; 
    // int st7[] = {88,02,77,73,07,63,67}; 
    // int st8[] = {99,65,04,28,06,16,70,92};
    // int st9[] = {41,41,26,56,83,40,80,70,33}; 
    // int st10[] = {41,48,72,33,47,32,37,16,94,29}; 
    // int st11[] = {53,71,44,65,25,43,91,52,97,51,14};
    // int st12[] = {70,11,33,28,77,73,17,78,39,68,17,57};
    // int st13[] = {91,71,52,38,17,14,91,43,58,50,27,29,48};
    // int st14[] = {63,66,04,68,89,53,67,30,73,16,69,87,40,31}; 
    // int st15[] = {04,62,98,27,23,9,70,98,73,93,38,53,60,04,23};
    // int max_num = 0;
    // int i_num = 0;

    // max_num = (st2[i_num] > st2[i_num + 1]) ? st2[i_num] : st2[i_num + 1];
    // i_num = (max_num == st2[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st3[i_num] > st3[i_num + 1]) ? st3[i_num] : st3[i_num + 1];
    // i_num = (max_num == st3[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st4[i_num] > st4[i_num + 1]) ? st4[i_num] : st4[i_num + 1];
    // i_num = (max_num == st4[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st5[i_num] > st5[i_num + 1]) ? st5[i_num] : st5[i_num + 1];
    // i_num = (max_num == st5[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st6[i_num] > st6[i_num + 1]) ? st6[i_num] : st6[i_num + 1];
    // i_num = (max_num == st6[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st7[i_num] > st7[i_num + 1]) ? st7[i_num] : st7[i_num + 1];
    // i_num = (max_num == st7[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st8[i_num] > st8[i_num + 1]) ? st8[i_num] : st8[i_num + 1];
    // i_num = (max_num == st8[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st9[i_num] > st9[i_num + 1]) ? st9[i_num] : st9[i_num + 1];
    // i_num = (max_num == st9[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st10[i_num] > st10[i_num + 1]) ? st10[i_num] : st10[i_num + 1];
    // i_num = (max_num == st10[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st11[i_num] > st11[i_num + 1]) ? st11[i_num] : st11[i_num + 1];
    // i_num = (max_num == st11[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st12[i_num] > st12[i_num + 1]) ? st12[i_num] : st12[i_num + 1];
    // i_num = (max_num == st12[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st13[i_num] > st13[i_num + 1]) ? st13[i_num] : st13[i_num + 1];
    // i_num = (max_num == st13[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st14[i_num] > st14[i_num + 1]) ? st14[i_num] : st14[i_num + 1];
    // i_num = (max_num == st14[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    // max_num = (st15[i_num] > st15[i_num + 1]) ? st15[i_num] : st15[i_num + 1];
    // i_num = (max_num == st15[i_num]) ? i_num : i_num + 1;
    // sum_num += max_num;

    int max_num = 75;                                              //1074
    int st2[] = {95,64}; 
    int st3[] = {17,47,82}; 
    int st4[] = {18,35,87,10}; 
    int st5[] = {20,04,82,47,65};
    int st6[] = {19,01,23,75,03,34}; 
    int st7[] = {88,02,77,73,07,63,67}; 
    int st8[] = {99,65,04,28,06,16,70,92};
    int st9[] = {41,41,26,56,83,40,80,70,33}; 
    int st10[] = {41,48,72,33,47,32,37,16,94,29}; 
    int st11[] = {53,71,44,65,25,43,91,52,97,51,14};
    int st12[] = {70,11,33,28,77,73,17,78,39,68,17,57};
    int st13[] = {91,71,52,38,17,14,91,43,58,50,27,29,48};
    int st14[] = {63,66,04,68,89,53,67,30,73,16,69,87,40,31}; 
    int st15[] = {04,62,98,27,23,9,70,98,73,93,38,53,60,04,23};

    int sum_num = 0; 
    sum_num += max_num;

    int num1 = st2[0];
    int num2 = st2[1];

    int i_num1 = 0;
    int i_num2 = 1;
    int i_num3 = 2;
    int max_num1 = 0;
    int max_num2 = 0;

    max_num1 = (st3[i_num1] > st3[i_num2]) ? st3[i_num1] : st3[i_num2];
    max_num2 = (st3[i_num2] > st3[i_num3]) ? st3[i_num2] : st3[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st3[i_num1];
    num2 = st3[i_num2];
    sum_num += max_num;

    max_num1 = (st4[i_num1] > st4[i_num2]) ? st4[i_num1] : st4[i_num2];
    max_num2 = (st4[i_num2] > st4[i_num3]) ? st4[i_num2] : st4[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st4[i_num1];
    num2 = st4[i_num2];
    sum_num += max_num;

    max_num1 = (st5[i_num1] > st5[i_num2]) ? st5[i_num1] : st5[i_num2];
    max_num2 = (st5[i_num2] > st5[i_num3]) ? st5[i_num2] : st5[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st5[i_num1];
    num2 = st5[i_num2];
    sum_num += max_num;

    max_num1 = (st6[i_num1] > st6[i_num2]) ? st6[i_num1] : st6[i_num2];
    max_num2 = (st6[i_num2] > st6[i_num3]) ? st6[i_num2] : st6[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st6[i_num1];
    num2 = st6[i_num2];
    sum_num += max_num;

    max_num1 = (st7[i_num1] > st7[i_num2]) ? st7[i_num1] : st7[i_num2];
    max_num2 = (st7[i_num2] > st7[i_num3]) ? st7[i_num2] : st7[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st7[i_num1];
    num2 = st7[i_num2];
    sum_num += max_num;
 
    max_num1 = (st8[i_num1] > st8[i_num2]) ? st8[i_num1] : st8[i_num2];
    max_num2 = (st8[i_num2] > st8[i_num3]) ? st8[i_num2] : st8[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st8[i_num1];
    num2 = st8[i_num2];
    sum_num += max_num;

    max_num1 = (st9[i_num1] > st9[i_num2]) ? st9[i_num1] : st9[i_num2];
    max_num2 = (st9[i_num2] > st9[i_num3]) ? st9[i_num2] : st9[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st9[i_num1];
    num2 = st9[i_num2];
    sum_num += max_num;

    max_num1 = (st10[i_num1] > st10[i_num2]) ? st10[i_num1] : st10[i_num2];
    max_num2 = (st10[i_num2] > st10[i_num3]) ? st10[i_num2] : st10[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st10[i_num1];
    num2 = st10[i_num2];
    sum_num += max_num;

    max_num1 = (st11[i_num1] > st11[i_num2]) ? st11[i_num1] : st11[i_num2];
    max_num2 = (st11[i_num2] > st11[i_num3]) ? st11[i_num2] : st11[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st11[i_num1];
    num2 = st11[i_num2];
    sum_num += max_num;

    max_num1 = (st12[i_num1] > st12[i_num2]) ? st12[i_num1] : st12[i_num2];
    max_num2 = (st12[i_num2] > st12[i_num3]) ? st12[i_num2] : st12[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st12[i_num1];
    num2 = st12[i_num2];
    sum_num += max_num;

    max_num1 = (st13[i_num1] > st13[i_num2]) ? st13[i_num1] : st13[i_num2];
    max_num2 = (st13[i_num2] > st13[i_num3]) ? st13[i_num2] : st13[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st13[i_num1];
    num2 = st13[i_num2];
    sum_num += max_num;

    max_num1 = (st14[i_num1] > st14[i_num2]) ? st14[i_num1] : st14[i_num2];
    max_num2 = (st14[i_num2] > st14[i_num3]) ? st14[i_num2] : st14[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st14[i_num1];
    num2 = st14[i_num2];
    sum_num += max_num;

    max_num1 = (st15[i_num1] > st15[i_num2]) ? st15[i_num1] : st15[i_num2];
    max_num2 = (st15[i_num2] > st15[i_num3]) ? st15[i_num2] : st15[i_num3];
    max_num = ((num1 + max_num1) > (num2 + max_num2)) ? num1 : num2;
    i_num1 = (max_num == num1) ? i_num1 : i_num2;
    i_num2 = i_num1 + 1;
    i_num3 = i_num1 + 2;
    num1 = st15[i_num1];
    num2 = st15[i_num2];
    sum_num += max_num;

    max_num = (num1 > num1) ? num1 : num2;
    sum_num += max_num;                                                                                                                   
    return 0;
}