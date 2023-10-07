// euler24c - Словарные перестановки

// Перестановка - это упорядоченная выборка объектов. 
// К примеру, 3124 является одной из возможных перестановок из цифр 1, 2, 3 и 4. 
// Если все перестановки приведены в порядке возрастания или алфавитном порядке, 
// то такой порядок будем называть словарным. Словарные перестановки из цифр 0, 1 и 2 представлены ниже:

// 012   021   102   120   201   210

// Какова миллионная словарная перестановка из цифр 0, 1, 2, 3, 4, 5, 6, 7, 8 и 9?

#include <stdio.h>

int main(void)
{    
    // искомый номер перестановки чисел (первоначальное положение тоже считается)
    int num = 999999;                           
    long long answ = 0;
    int inter_answ[10] = {0};                   // промежуточный ответ
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};        // отсортированные числа
    int arr_fact[10] = {1,1,1,1,1,1,1,1,1,1};   // факториалы до 9!
    
    for(int i = 7, j = 1; i >= 0; i--)          //вычисляем факториалы
        arr_fact[i] = (++j)*arr_fact[i+1];

    //вычисляем 1000000-ное промежуточное число -> 2662512110  
    for (int i = 0; i < 10; i++)
    {
        inter_answ[i] = num/arr_fact[i];
        num = num%arr_fact[i];
    }

    //переводим промежуточное число в ответ - искомую перестановку чисел
    long long place = 1000000000;               //разряд числа
    for(int i = 0; i < 10; i++, place /= 10)
    {
        //берем число по индексу из отсортированного массива
        answ += place*arr[inter_answ[i]];
        //изымаем число из массива           
        for(int j = inter_answ[i]; j < 9; j++)
            arr[j] = arr[j + 1];
    }
    
    printf("%lld", answ);                       //2783915460

    return 0;
}