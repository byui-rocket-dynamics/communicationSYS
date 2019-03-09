#include <wiringPiSPI.h>

using namespace std;

#define CHANNEL 1

int main()
{
   unsigned char buffer[100];
   int fd;
   int result;
   
   fd = wiringPiSPISetup(CHANNEL, 500000);
   printf("Initial Resilt %d", fd);

   buffer[0] = 0x76;

   for(int i = 1; i <= 0x7f; i <<= 1)
   {
      // the decimals, colon and apostrophe dots
      buffer[0] = 0x77;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The first character
      buffer[0] = 0x7b;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The second character
      buffer[0] = 0x7c;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The third character
      buffer[0] = 0x7d;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The last character
      buffer[0] = 0x7e;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // Pause so we can see them
      sleep(5);
   }

   // clear display again
   buffer[0] = 0x76;
   wiringPiSPIDataRW(CHANNEL, buffer, 1);

   return 0;
}