#include <stdio.h>
#include <stdint.h>
#include "sincos.h"

main()
{
  int i;
  for (i = 0; i <= 0x10000; i++)
    printf("%d %d\n", i, isin(i));
  exit(0);
}
