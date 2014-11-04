#include <stdio.h>

void f_signed(long a, long b)
{
  if (a > b) puts("a > b");
  if (a == b) puts("a == b");
  if (a < b) puts("a < b");
}

void f_unsigned(unsigned long a, unsigned long b)
{
  if (a > b) puts("a > b");
  if (a == b) puts("a == b");
  if (a < b) puts("a < b");
}

int main()
{
  f_signed(1, 2);
  f_unsigned(1, 2);
  return 0;
}
