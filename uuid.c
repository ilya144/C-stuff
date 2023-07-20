#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

typedef char* string;

string uuid4(){
    string buffer = malloc(129);
    buffer[128] = '\0';

    uint32_t d0, d1, d2, d3;

    srand(
        time(NULL)
    );

    d0 = rand();
    d1 = rand();
    d2 = rand();
    d3 = rand();

    d1 = (d1 & 0xffff8fff) | 0x00004000; // version 4
    d2 = (d2 & 0x0fffffff) | 0x80000000; // variant 1

    sprintf(
        buffer, 
        "%x-%x-%x-%x-%x%x", 
        d0, d1 >> 16, d1 & 0x0000ffff, d2 >> 16, d2 & 0x0000ffff, d3
    );
    
    return buffer;
}

void main(){
    string id = uuid4();
    
    puts(id);
}
