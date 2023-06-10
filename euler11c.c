// Euler11c - Наибольшее произведение в таблице

// В таблице 20×20 (внизу) четыре числа на одной диагонали выделены красным.

// 08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
// 49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
// 81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
// 52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
// 22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
// 24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
// 32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
// 67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
// 24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
// 21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
// 78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
// 16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
// 86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
// 19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
// 04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
// 88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
// 04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
// 20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
// 20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
// 01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48

// Произведение этих чисел 26 × 63 × 78 × 14 = 1788696.

// Каково наибольшее произведение четырех подряд идущих чисел в таблице 20×20, расположенных в любом направлении
// (вверх, вниз, вправо, влево или по диагонали)?

#include <stdio.h>

int st1[] = {8,02,22,97,38,15,00,40,00,75,04,05,07,78,52,12,50,77,91,8};    //08 воспринимаются как 8-ричная запись
int st2[] = {49,49,99,40,17,81,18,57,60,87,17,40,98,43,69,48,04,56,62,00};
int st3[] = {81,49,31,73,55,79,14,29,93,71,40,67,53,88,30,03,49,13,36,65};
int st4[] = {52,70,95,23,04,60,11,42,69,24,68,56,01,32,56,71,37,02,36,91};
int st5[] = {22,31,16,71,51,67,63,89,41,92,36,54,22,40,40,28,66,33,13,80};
int st6[] = {24,47,32,60,99,03,45,02,44,75,33,53,78,36,84,20,35,17,12,50};
int st7[] = {32,98,81,28,64,23,67,10,26,38,40,67,59,54,70,66,18,38,64,70};
int st8[] = {67,26,20,68,02,62,12,20,95,63,94,39,63,8,40,91,66,49,94,21};
int st9[] = {24,55,58,05,66,73,99,26,97,17,78,78,96,83,14,88,34,89,63,72};
int st10[] = {21,36,23,9,75,00,76,44,20,45,35,14,00,61,33,97,34,31,33,95};
int st11[] = {78,17,53,28,22,75,31,67,15,94,03,80,04,62,16,14,9,53,56,92};
int st12[] = {16,39,05,42,96,35,31,47,55,58,88,24,00,17,54,24,36,29,85,57};
int st13[] = {86,56,00,48,35,71,89,07,05,44,44,37,44,60,21,58,51,54,17,58};
int st14[] = {19,80,81,68,05,94,47,69,28,73,92,13,86,52,17,77,04,89,55,40};
int st15[] = {04,52,8,83,97,35,99,16,07,97,57,32,16,26,26,79,33,27,98,66};
int st16[] = {88,36,68,87,57,62,20,72,03,46,33,67,46,55,12,32,63,93,53,69};
int st17[] = {04,42,16,73,38,25,39,11,24,94,72,18,8,46,29,32,40,62,76,36};
int st18[] = {20,69,36,41,72,30,23,88,34,62,99,69,82,67,59,85,74,04,36,16};
int st19[] = {20,73,35,29,78,31,90,01,74,31,49,71,48,86,81,16,23,57,05,54};
int st20[] = {01,70,54,71,83,51,54,69,16,92,33,48,61,43,52,01,89,19,67,48};

int main(void)
{
    int answ = 1;
    int prod = 1;
    for (int i = 0; i < 20; i++)
    {
        prod = st1[i] * st2[i] * st3[i] * st4[i];
        if (answ < prod) answ = prod;
        prod = st2[i] * st3[i] * st4[i] * st5[i];
        if (answ < prod) answ = prod; 
        prod = st3[i] * st4[i] * st5[i] * st6[i];
        if (answ < prod) answ = prod;
        prod = st4[i] * st5[i] * st6[i] * st7[i];
        if (answ < prod) answ = prod; 
        prod = st5[i] * st6[i] * st7[i] * st8[i];
        if (answ < prod) answ = prod; 
        prod = st6[i] * st7[i] * st8[i] * st9[i];
        if (answ < prod) answ = prod; 
        prod = st7[i] * st8[i] * st9[i] * st10[i];
        if (answ < prod) answ = prod; 
        prod = st8[i] * st9[i] * st10[i] * st11[i];
        if (answ < prod) answ = prod; 
        prod = st9[i] * st10[i] * st11[i] * st12[i];
        if (answ < prod) answ = prod; 
        prod = st10[i] * st11[i] * st12[i] * st13[i];
        if (answ < prod) answ = prod;
        prod = st11[i] * st12[i] * st13[i] * st14[i];
        if (answ < prod) answ = prod; 
        prod = st12[i] * st13[i] * st14[i] * st15[i];
        if (answ < prod) answ = prod; 
        prod = st13[i] * st14[i] * st15[i] * st16[i];
        if (answ < prod) answ = prod; 
        prod = st14[i] * st15[i] * st16[i] * st17[i];
        if (answ < prod) answ = prod; 
        prod = st15[i] * st16[i] * st17[i] * st18[i];
        if (answ < prod) answ = prod; 
        prod = st16[i] * st17[i] * st18[i] * st19[i];
        if (answ < prod) answ = prod; 
        prod = st17[i] * st18[i] * st19[i] * st20[i];
        if (answ < prod) answ = prod; 
    }
    
    for (int i = 0; i < 17; i++)
    {
        prod = st4[i] * st3[i + 1] * st2[i + 2] * st1[i + 3];
        if (answ < prod) answ = prod;
        prod = st5[i] * st4[i + 1] * st3[i + 2] * st2[i + 3];
        if (answ < prod) answ = prod;
        prod = st6[i] * st5[i + 1] * st4[i + 2] * st3[i + 3];
        if (answ < prod) answ = prod;
        prod = st7[i] * st6[i + 1] * st5[i + 2] * st4[i + 3];
        if (answ < prod) answ = prod;
        prod = st8[i] * st7[i + 1] * st6[i + 2] * st5[i + 3];
        if (answ < prod) answ = prod;
        prod = st9[i] * st8[i + 1] * st7[i + 2] * st6[i + 3];
        if (answ < prod) answ = prod;
        prod = st10[i] * st9[i + 1] * st8[i + 2] * st7[i + 3];
        if (answ < prod) answ = prod;
        prod = st11[i] * st10[i + 1] * st9[i + 2] * st8[i + 3];
        if (answ < prod) answ = prod;
        prod = st12[i] * st11[i + 1] * st10[i + 2] * st9[i + 3];
        if (answ < prod) answ = prod;
        prod = st13[i] * st12[i + 1] * st11[i + 2] * st10[i + 3];
        if (answ < prod) answ = prod;
        prod = st14[i] * st13[i + 1] * st12[i + 2] * st11[i + 3];
        if (answ < prod) answ = prod;
        prod = st15[i] * st14[i + 1] * st13[i + 2] * st12[i + 3];
        if (answ < prod) answ = prod;
        prod = st16[i] * st15[i + 1] * st14[i + 2] * st13[i + 3];
        if (answ < prod) answ = prod;
        prod = st17[i] * st16[i + 1] * st15[i + 2] * st14[i + 3];
        if (answ < prod) answ = prod;
        prod = st18[i] * st17[i + 1] * st16[i + 2] * st15[i + 3];
        if (answ < prod) answ = prod;
        prod = st19[i] * st18[i + 1] * st17[i + 2] * st16[i + 3];
        if (answ < prod) answ = prod;
        prod = st20[i] * st19[i + 1] * st18[i + 2] * st17[i + 3];
        if (answ < prod) answ = prod;
    }

    for (int i = 0; i < 17; i++)
    {
        prod = st1[i] * st2[i + 1] * st3[i + 2] * st4[i + 3];
        if (answ < prod) answ = prod;
        prod = st2[i] * st3[i + 1] * st4[i + 2] * st5[i + 3];
        if (answ < prod) answ = prod;
        prod = st3[i] * st4[i + 1] * st5[i + 2] * st6[i + 3];
        if (answ < prod) answ = prod;
        prod = st4[i] * st5[i + 1] * st6[i + 2] * st7[i + 3];
        if (answ < prod) answ = prod;
        prod = st5[i] * st6[i + 1] * st7[i + 2] * st8[i + 3];
        if (answ < prod) answ = prod;
        prod = st6[i] * st7[i + 1] * st8[i + 2] * st9[i + 3];
        if (answ < prod) answ = prod;
        prod = st7[i] * st8[i + 1] * st9[i + 2] * st10[i + 3];
        if (answ < prod) answ = prod;
        prod = st8[i] * st9[i + 1] * st10[i + 2] * st11[i + 3];
        if (answ < prod) answ = prod;
        prod = st9[i] * st10[i + 1] * st11[i + 2] * st12[i + 3];
        if (answ < prod) answ = prod;
        prod = st10[i] * st11[i + 1] * st12[i + 2] * st13[i + 3];
        if (answ < prod) answ = prod;
        prod = st11[i] * st12[i + 1] * st13[i + 2] * st14[i + 3];
        if (answ < prod) answ = prod;
        prod = st12[i] * st13[i + 1] * st14[i + 2] * st15[i + 3];
        if (answ < prod) answ = prod;
        prod = st13[i] * st14[i + 1] * st15[i + 2] * st16[i + 3];
        if (answ < prod) answ = prod;
        prod = st14[i] * st15[i + 1] * st16[i + 2] * st17[i + 3];
        if (answ < prod) answ = prod;
        prod = st15[i] * st16[i + 1] * st17[i + 2] * st18[i + 3];
        if (answ < prod) answ = prod;
        prod = st16[i] * st17[i + 1] * st18[i + 2] * st19[i + 3];
        if (answ < prod) answ = prod;
        prod = st17[i] * st18[i + 1] * st19[i + 2] * st20[i + 3];
        if (answ < prod) answ = prod;        
    }

    for (int i = 0; i < 17; i++)
    {
        prod = st1[i] * st1[i + 1] * st1[i + 2] * st1[i + 3];
        if (answ < prod) answ = prod;
        prod = st2[i] * st2[i + 1] * st2[i + 2] * st2[i + 3];
        if (answ < prod) answ = prod;
        prod = st3[i] * st3[i + 1] * st3[i + 2] * st3[i + 3];
        if (answ < prod) answ = prod;
        prod = st4[i] * st4[i + 1] * st4[i + 2] * st4[i + 3];
        if (answ < prod) answ = prod;
        prod = st5[i] * st4[i + 1] * st5[i + 2] * st5[i + 3];
        if (answ < prod) answ = prod;
        prod = st6[i] * st5[i + 1] * st6[i + 2] * st6[i + 3];
        if (answ < prod) answ = prod;
        prod = st7[i] * st6[i + 1] * st7[i + 2] * st7[i + 3];
        if (answ < prod) answ = prod;
        prod = st8[i] * st7[i + 1] * st8[i + 2] * st8[i + 3];
        if (answ < prod) answ = prod;
        prod = st9[i] * st8[i + 1] * st9[i + 2] * st9[i + 3];
        if (answ < prod) answ = prod;
        prod = st10[i] * st9[i + 1] * st10[i + 2] * st10[i + 3];
        if (answ < prod) answ = prod;
        prod = st11[i] * st10[i + 1] * st11[i + 2] * st11[i + 3];
        if (answ < prod) answ = prod;
        prod = st12[i] * st12[i + 1] * st12[i + 2] * st12[i + 3];
        if (answ < prod) answ = prod;
        prod = st13[i] * st13[i + 1] * st13[i + 2] * st13[i + 3];
        if (answ < prod) answ = prod;
        prod = st14[i] * st14[i + 1] * st14[i + 2] * st14[i + 3];
        if (answ < prod) answ = prod;
        prod = st15[i] * st15[i + 1] * st15[i + 2] * st15[i + 3];
        if (answ < prod) answ = prod;
        prod = st16[i] * st16[i + 1] * st16[i + 2] * st16[i + 3];
        if (answ < prod) answ = prod;
        prod = st17[i] * st17[i + 1] * st17[i + 2] * st17[i + 3];
        if (answ < prod) answ = prod;
        prod = st18[i] * st18[i + 1] * st18[i + 2] * st18[i + 3];
        if (answ < prod) answ = prod;
        prod = st19[i] * st19[i + 1] * st19[i + 2] * st19[i + 3];
        if (answ < prod) answ = prod;
        prod = st20[i] * st20[i + 1] * st20[i + 2] * st20[i + 3];
        if (answ < prod) answ = prod;
    }

    return 0;
}