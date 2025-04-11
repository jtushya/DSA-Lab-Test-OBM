#include <bits/stdc++.h>
using namespace std;

int factorialNonRecursive(int n)
{
  int fact = 1;

  for (int i = 1; i <= n; i++)
  {
    fact = fact * i;
  }

  return fact;
}

int factorialNonTailRecursive(int n)
{
  // Base case
  if(n==0)
  return 1;

  int fact=factorialNonTailRecursive(n-1);
  fact=fact*n;

  return fact;
}

int factorialTailRecursive(int n, int fact)
{
  // Base case
  if (n == 0)
    return fact;

  return factorialTailRecursive(n - 1, n*fact);
}


int main()
{
  int iterations = 100000;

  while (iterations--)
  {
    factorialNonRecursive(2000);
    factorialTailRecursive(2000, 1);
    factorialNonTailRecursive(2000);
  }

  return 0;
}