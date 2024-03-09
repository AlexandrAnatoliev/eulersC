#include <stdio.h>

void copy_arr(double arr[], double sour[], int n);
void copy_ptr(double arr[], double sour[], int n);
void copy_ptrs(double arr[], double sour[], double *n);

int main(void)
{
    double sourse[2][5] = {{5, 6, 7, 8, 9}, {1, 2, 3, 4, 5}};
    double arr1[2][5];
    double arr2[5];
    double arr3[5];

    for (int i = 0, j = 1; i < 1; i++)
        copy_ptrs(arr1[j], sourse[i], sourse[1]);
    // copy_arr(arr1, sourse, 5);
    // copy_ptr(arr2, sourse, 5);
    // copy_ptrS(arr3, sourse, sourse + 5);
    return 0;
}

void copy_arr(double arr[], double sour[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = sour[i];
}

void copy_ptr(double arr[], double sour[], int n)
{
    double *ptr1 = arr;
    double *prt2 = sour;
    for (int i = 0; i < n; i++)
        *(ptr1 + i) = *(sour + i);
}

void copy_ptrs(double arr[], double sour[], double *n)
{
    double *ptr1 = arr;
    double *prt2 = sour;
    while (sour != n)
        *ptr1++ = *sour++;
}