#include <stdio.h>
#include <math.h>

int isprime(int num);
long quick_pow10(int power);

/*solve Project Euler problem 51*/
int main() 
{
    /*length of potential answer(including last digit)*/
    int l = 3; 
    long ans = -1;
    /*in binary, which digits we should change(not including 
     * last digit)*/
    unsigned int digs;

    /*loop through lengths of test numbers while ans hasn't been found*/
    while(ans < 0) {
        printf("l = %d\n", l);
        /*loop across which digits to replace(last digit is never
         * replaced because it must be odd)*/
        for(digs=1; (digs<(1 << (l-1))) && (ans < 0); digs++) {
            /*digs, but including last digit*/
            unsigned int reps = digs << 1;
            printf("    reps=%u\n", reps);
            int onecount = 0;
            int ones[l];
            int i;
            int bit;
            /* value of digits that aren't changed */
            long g;
            /*count how many digits are going to be changed and record
             * which*/
            for(i=l - 1; i >= 0; i -= 1) {
                bit = (reps >> i) & 1;
                if(bit == 1) {
                    ones[onecount++] = l - 1 - i;
                }
            }
            /*loop through the possible cumulative values for the 
             * non-replaced digits in the test number*/
            for(g = quick_pow10(l-1-onecount) + ((l-1-onecount)>0);
               (g < quick_pow10(l-onecount)) && (ans < 0);
                g+=2) {
                /* test the l-digit number testnum with the
                * substitutions at digits listed in 'ones.' 
                * non substituted digits are in g.*/
                int t;
                int primecount = 0;
                int failcount = 0;
                /*digit counter in g, from least significant*/
                int gdc = 0;
                /*location in testnum, from least significant digit*/
                int tni;
                long testnum = 0;
                long testnumt;

                /*put gdigits into correct locations in testnum*/
                for(tni=0; tni < l; tni++) {
                    if(!((reps >> tni) & 1)) {
                        testnum += 
                        ((g / quick_pow10(gdc++)) % 10) * 
                        quick_pow10(tni);
                    }
                }

                /*loop across the members of the family of 
                 * substitutions. Include 0 only if the first digit 
                 * isn't being changed*/
                for(t=9; t >= (int)((reps >> (l - 1)) & 1); t--) {
                    testnumt = testnum;
                    int k;
                    /*build the final testnum*/
                    for(k=0; k < onecount; k++){
                        testnumt += t * quick_pow10(l - 1 - ones[k]);
                    }

                    if(isprime(testnumt)) {
                        primecount += 1;
                    } 
                    else {
                        if((++failcount) >= 3) {
                            break;
                        }
                    }
                }

                if(primecount >= 8) {
                    ans = testnumt;
                } 
            }
        }
        l++;
    }
    printf("%ld\n", ans);
}


long quick_pow10(int power)
{
    static long long pow10[11] = {
        1, 10, 100, 1000, 10000, 
        100000, 1000000, 10000000, 100000000, 1000000000, 10000000000
    };

    return pow10[power];
}


int isprime(int num)
{
     if (num <= 1) return 0;
     if (num % 2 == 0 && num > 2) return 0;
     for(int i = 3; i < num / 2; i+= 2)
     {
         if (num % i == 0)
             return 0;
     }
     return 1;
}