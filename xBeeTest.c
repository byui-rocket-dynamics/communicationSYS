#include <stdio.h>
#include <string.h>
#include "xBee.h"

int main()
{
   char str[11];
   for(;;){
      printf("Enter string less than 10 characters: ");
      scanf("%s\n", str);
      printf("%s\n", str);
   }
   return 0;
}