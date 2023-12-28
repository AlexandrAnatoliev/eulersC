#include <stdio.h>
#include <stdbool.h>
#include <math.h>	                                            //для работы функции pow()

int main(void)
{
    int div_max;
    int num = 134043;                       // 134043
    num = (double)num;
    double sq_num = sqrt((double)num);
    div_max = (int)sq_num + 1;
	
    return 0;
}									
