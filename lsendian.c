#include <stdint.h>
#include <stdio.h>


int main(){
    uint16_t endian_word = 0x0001;
    uint8_t is_little_endian = *((uint8_t *) &endian_word);

    printf("%s-endian\n", is_little_endian ? "little" : "big");

    return 0;
}

