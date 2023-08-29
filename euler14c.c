//euler14c - Самая длинная последовательность Коллатца

//Следующая повторяющаяся последовательность определена для множества натуральных чисел:
// n → n/2 (n - четное)
// n → 3n + 1 (n - нечетное)

// Используя описанное выше правило и начиная с 13, сгенерируется следующая последовательность:
// 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
// Получившаяся последовательность (начиная с 13 и заканчивая 1) содержит 10 элементов. 
// Хотя это до сих пор и не доказано (проблема Коллатца (Collatz)), предполагается, 
// что все сгенерированные таким образом последовательности оканчиваются на 1.

// Какой начальный элемент меньше миллиона генерирует самую длинную последовательность?

// Примечание: Следующие за первым элементы последовательности могут быть больше миллиона.

#include <stdio.h>
int main(void)
{
    unsigned long long n = 13;                      
    // важно использовать тип unsigned long long т.к в процессе вычислений цепочки получаются огромные числа
    int first_n;                                    // 837799
    int max_count = 0;                              // 525
    for (int i = 1; i < 1000000; i++)
    {
        n = i;
        int count = 1;
        while (n != 1)
        {
            n = (n%2 == 0) ? n/2 : 3*n+1;
            count++;
        }
        if (max_count < count)
        {
            max_count = count;
            first_n = i;
        }
    }
    printf("%d",first_n);
    return 0;
}