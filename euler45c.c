// euler45c - Треугольные, пятиугольные и шестиугольные

// Треугольные, пятиугольные и шестиугольные числа вычисляются по нижеследующим формулам:

// Треугольные	 	Tn=n(n+1)/2	 	    1, 3, 6, 10, 15, ...
// Пятиугольные	 	Pn=n(3n−1)/2	 	1, 5, 12, 22, 35, ...
// Шестиугольные	Hn=n(2n−1)	 	    1, 6, 15, 28, 45, ...
// Можно убедиться в том, что T285 = P165 = H143 = 40755.

// Найдите следующее треугольное число, являющееся также пятиугольным и шестиугольным.

#include <stdio.h>

typedef struct number                   // создаем структуру для хранения числа
{
    int value;                          // текущее значение 
    int step;                           // текущий шаг для получения следующего числа
} NUMBER;                               // меняем название типа данных для красоты struct number -> NUMBER

int next_num(NUMBER *num, int change_step)
// функция увеличивает число
// параметры:	num         - указатель структуру - число
//              change_step - величина, на которую нужно изменить шаг
{
    num -> value += num -> step;        // value += step получаем следующее число
    num -> step += change_step;         // меняем текущий шаг
    return 0;
}

int main(void)
{  
    NUMBER triangle = {1,2};            // треугольное число {значение = 1, шаг = 2}
    NUMBER pentagonal = {1,4};          // пятиугольное число {значение = 1, шаг = 4}
    NUMBER hexagonal = {1,5};           // шестиугольное число {значение = 1, шаг = 5}

    for(int i = 0; i < 2; i++)
    {
        next_num(&triangle, 1);         // увеличиваем значения чтобы пройти числа 1 и 40755
        next_num(&pentagonal, 3);
        next_num(&hexagonal, 4);

                                        // пока значения всех трех чисел не совпали
        while( triangle.value != pentagonal.value || pentagonal.value != hexagonal.value)
                                                        
        {
            if(triangle.value < pentagonal.value)
            {
                                        // определяем минимальное число
                if(triangle.value < hexagonal.value)
                                        // и увеличиваем его    
                    next_num(&triangle, 1);             
                else
                    next_num(&hexagonal, 4);
            }
            else
            {
                if(pentagonal.value < hexagonal.value)
                    next_num(&pentagonal, 3);
                else
                    next_num(&hexagonal, 4);
            }
        }
    }

    printf("%d", triangle.value);       // 1533776805   
    return 0;
}
