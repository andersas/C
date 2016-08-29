#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/file.h>

int main(int argc, char **argv)
{

     int record_size = 100; // Default log record size
     int fd;
     off_t log_size;
     size_t i;
     uint8_t *mmap_area;

     if (argc == 2) {
          record_size = atoi(argv[1]); // overwrite with first argument
     }

     printf("Record size: %i\n",record_size);
     
     uint8_t record[record_size]; // Our test log record is just a bunch of 0s
     memset(record,0,record_size);
     
     fd = open("test.log",O_CREAT|O_RDWR,00660);
     log_size = 100L*1024L*1024L*1024L;
     ftruncate(fd,log_size); // Truncate the test file to 100 GB
     mmap_area = mmap(NULL,log_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
     close(fd);

     for (i = 0; i < log_size-record_size; i+=record_size) {
          memcpy(&mmap_area[i],record,record_size);
     }

}
