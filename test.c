#include <stdio.h>


int fact_div(int n1, int n2, int n3)
{
    double f = 1.0;
    int m1 = 2;
    int m2 = 2;
    int m3 = 2;
    while (m1 <= n1) {
        f *= m1;
        m1++;
        while (f >= 1000000.0 && m2 <= n2) {
            f /= m2;
            m2++;
        }
        while (f >= 1000000.0 && m3 <= n3) {
            f /= m3;
            m3++;
        }
    }
    return f >= 1000000.0;
}

void main()
{
    int cnt = 0;
    for (int n = 63; n <= 63; n++) {
        for (int r = 30; r <= 30; r++) {
            if (fact_div(n, r, n - r)) {
                cnt++;
            }
        }
    }
    
    printf("%d\n", cnt);
}