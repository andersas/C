#include <stdio.h>

int main() {
char a;
unsigned char b;

a = b = 128;
a >>= 1;
b >>= 1;
printf( "\nYour computer has %ssigned char.\n\n", a == b ? "un" : "" ); 

return 0;
}
