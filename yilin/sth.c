#include <stdio.h>
#include <inttypes.h>

int sth1()
{
	char a, b, c; 
	int n=0;
	for (a = 'x'; a <= 'z'; ++a)
	{
		if (a == 'y') continue;
		for (b = 'x'; b <= 'z'; ++b)
		{
			if (b == a) continue;
			for (c = 'x'; c <= 'z'; ++c)
			{
				if(c == a || c == b || c == 'z') continue;
				printf("The match_%d is: a--%c, b--%c, c--%c\n", ++n, a, b, c);
			}
		}
	}
	return 0;
}

int sth2()
{
	int n;
	int total = 0;
	scanf("%d", &n);
	int left = 0;
	for (int i = 0; i <= n / 5; ++i) 
	{
	    left = n - i * 5;
	    for (int j = 0; j <= left / 10; ++j) 
	    {
	        total += 3;
	    }
	}
	printf("%d\n", total);
	return 0;
}

int sth3(int m, int n)
{
	int r;
	if (m > n) 
	{
		m = m ^ n;
		n = m ^ n;
		m = m ^ n;
	}
	while (1)
	{
		r = n % m;
		if (r == 0)
			break;
		n = m;
		m = r;
	}
	return m;
}

uint64_t sth4(int n)
{
	if (n == 1)
		return 1;
	if (n == 2)
		return 1;
	uint64_t i = 1;
	uint64_t j = 1;
	uint64_t k;
	while (--n > 1)
	{
		k = i + j;
		// printf("i: %"PRIu64", j: %"PRIu64", k: %"PRIu64"\n", i, j, k);
		i = j;
		j = k;
	}
	return k;
}

int sth5(int n)
{
	int i;
	while (n != 0)
	{
		i = n % 10;
		printf("%d", i);
		n /= 10;
	}
	printf("\n");
	return 0;
}

int sth6()
{
	char str[1024];
	scanf("%s", str);
	int i = 0, j = 0;
	while (str[j] != '\0')
		++j; 
	--j;
	char tmp;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		++i; --j;		
	}
	printf("%s\n", str);
	return 0;
}

int sth7(int y)
{
	y *= 100;
	int c = 0;
	for (int i = y - 100; i < y; ++i)
	{
		if (c == 10)
		{
			c = 0;
			printf("\n");
		}
		if (i % 4 == 0) {
			if (i % 100 == 0)
			{
				if (i % 400 == 0)
				{
					printf("%d ", i);
					++c;
				}
				continue;
			}
			printf("%d ", i);
			++c;
		}
	}
	printf("\n");
	return 0;
}

int sth8(int m, int n) // **** ** **
{
	
}

int main()
{
	// sth1();
	// sth2();
	// printf("%d\n", sth3(2100000000, 11));
	// printf("%"PRIu64"\n", sth4(10));
	// sth5(00100);
	// sth6();
	sth7(21);
	return 0;
}