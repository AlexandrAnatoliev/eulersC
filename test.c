#include <stdio.h>
#include <stdbool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    int *answ;
    int arr[] = {2,7,11,15};
    answ = twoSum(arr,4,18, 0);
    int x = answ[1];
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) 
{
    *returnSize = 2;
    int *answ = malloc(*returnSize * sizeof(int));
    for(int i = 0; i < numsSize - 1; i++)
    {
        for(int j = i + 1; j < numsSize; j++)
        {
            if(nums[i] + nums[j] == target)
            {
                answ[0] = i;
                answ[1] = j;
                return answ;
            }
        }
    }
}