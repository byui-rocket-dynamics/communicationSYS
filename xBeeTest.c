#include <stdio.h>
#include <string.h>

int main()
{
   char str[10];
   for(;;){
      printf("Enter string less than 10 characters");
      scanf("%s", str);
      printf("%s", str);
   }
   return 0;
}