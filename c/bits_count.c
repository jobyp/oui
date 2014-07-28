#include <stdio.h>

#define N 32

void count_bits(int a[], int i, unsigned int *count)
{
	if (i == 0)
	{
		if ( a[i + 1] == 1)
			*count += 1;
		else
			*count += 2;
		return;
	}

	if ( a[i + 1] == 1)
	{
		a[i] = 0;
		count_bits(a, i - 1, count);
	}
	else
	{
		a[i] = 0;
		count_bits(a, i - 1, count);
		a[i] = 1;
		count_bits(a, i - 1, count);
	}
	
	return;
}

int main()
{
	int a[N];
	unsigned int count = 0;
	
	for(int i = 0; i < N; i++)
		a[i] = 0;
	
	a[N - 1] = 0;
	count_bits(a, (N - 2), &count);
	
	a[N - 1] = 1;
	count_bits(a, (N - 2), &count);

	printf("%u\n", count);

	return 0;
}
