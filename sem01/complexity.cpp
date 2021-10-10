#include <iostream>

int f1(int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i++)
	{
        sum += n; 
    }
    return sum;
}

int f2(int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            sum++;
        }
    }
    return sum;
}

int f3(int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            sum++;
        }
    }
    return sum;
}

int f4(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i*=2)
    {
        for (int j = 1; j <= n; j++)
        {
            sum++;
        }
    }
    return sum;
}

int f5(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i*=2)
    {
        for (int j = 1; j <= i; j++)
        {
            sum++;
        }
    }
    return sum;
}

int main()
{
    
} 