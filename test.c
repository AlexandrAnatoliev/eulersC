#include <stdio.h>

int main(void)
{
	int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};
	int arr[8][201] = {0};

	for (int i = 0; i < 201; i++)
		arr[0][i] = 1;

	for (int i = 0; i < 8; i++)
		arr[i][0] = 1;

	for (int j = 1; j < 8; j++)
	{
		
		for (int i = 1; i < 201; i++)
		{
			int cnt = 0;
			while(cnt <= i)
			{
				arr[j][i] += arr[j-1][i - cnt];
				cnt += coins[j];
			}
				

		}
	}

	printf("%d", arr[7][200]);
	return 0;
}