#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int main(int argc, char **argv)
{

     int record_size = 100; // Default log record size
     
     if (argc == 2) {
          record_size = atoi(argv[1]); // overwrite with first argument
     }

     printf("Record size: %i\n",record_size);
     
     uint8_t record[record_size]; // Our test log record is just a bunch of 0s
     memset(record,0,record_size);
     
     FILE *F = fopen("test.log","ab");

     while(1) {
          fwrite(record,record_size,1,F);       
     }

}
