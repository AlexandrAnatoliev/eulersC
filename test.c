#include <stdio.h>
#include <math.h>

int main()
{
    float x;
    for (x = 36; x > 0; x /= 2)
        printf("%f\n", x);
    return 0;
}