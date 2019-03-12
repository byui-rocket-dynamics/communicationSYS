#include <stdio.h>
#include <string.h>
#include "xBee.h"

int main()
{
   Packet packet;
   char str[11];
   for(;;){
      printf("Enter string less than 10 characters: ");
      scanf("%s\n", str);
      printf("converting %s to hex string...\n\n", str);

      TX(&packet, str);
      printf("\n\n");
   }
   return 0;
}