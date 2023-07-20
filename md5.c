#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef char* string;

const uint8_t S[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

// big-endian format, could be calculated with 
// T[i] = (uint32_t) floor( pow(2, 32) * fabs( sin(i + 1) ) )
const uint32_t T[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

uint32_t swap_endian(uint32_t num){
    uint32_t b0 = (num & 0x000000ff) << 24u;
    uint32_t b1 = (num & 0x0000ff00) << 8u;
    uint32_t b2 = (num & 0x00ff0000) >> 8u;
    uint32_t b3 = (num & 0xff000000) >> 24u;

    return b0 | b1 | b2 | b3;
}

string md5(string message){
    uint32_t initial_length = strlen(message);

    uint32_t buffer_length = initial_length + 1;
    do {
        buffer_length++;
    } while (buffer_length % 64 != 56);

    uint8_t buffer[buffer_length + 8]; // buffer_length % 64 == 0

    memcpy(buffer, message, initial_length);
    
    buffer[initial_length] = (uint8_t) 0x80;
    
    for (uint32_t i = initial_length + 1; i < buffer_length; i++){
        buffer[i] = (uint8_t) 0x00;
    };

    uint32_t initial_bits_length = initial_length * 8;
    memcpy(buffer + buffer_length, (uint8_t[]){ 
        (uint8_t)initial_bits_length,
        (uint8_t)(initial_bits_length >> 8),
        (uint8_t)(initial_bits_length >> 16),
        (uint8_t)(initial_bits_length >> 24),
        0x00, 0x00, 0x00, 0x00 
    }, 8);

    buffer_length += 8; // buffer initialization over, set real length;
    
    uint32_t A = 0x67452301;
    uint32_t B = 0xefcdab89;
    uint32_t C = 0x98badcfe;
    uint32_t D = 0x10325476;

    uint32_t chunks_count = buffer_length / 64;

    for (uint32_t chunk = 0; chunk < chunks_count; chunk++){
        uint32_t *M = (uint32_t *)(buffer + chunk * 64); // provided length of M array is 16;

        uint32_t AA = A;
        uint32_t BB = B;
        uint32_t CC = C;
        uint32_t DD = D;

        for (uint8_t i = 0; i < 64; i++) {
            uint32_t F;
            uint8_t g;

            if (i < 16) {
                F = (BB & CC) | (~BB & DD);
                g = i;
            } else if (i < 32) {
                F = (DD & BB) | (~DD & CC);
                g = (i * 5 + 1) % 16;
            } else if (i < 48) {
                F = BB ^ CC ^ DD;
                g = (i * 3 + 5) % 16;
            } else {
                F = CC ^ (BB | (~DD));
                g = (i * 7) % 16;
            }

            F = (F + AA) + (T[i] + M[g]);
            AA = DD;
            DD = CC;
            CC = BB;
            BB = BB + ((F << S[i]) | (F >> (32 - S[i])));
        };

        A += AA;
        B += BB;
        C += CC;
        D += DD;
    };

    // result has little-endian formated uint32
    string result = malloc(sizeof (char) * 33);
    sprintf(result, "%x%x%x%x", swap_endian(A), swap_endian(B), swap_endian(C), swap_endian(D));
    
    return result;
}

int main(int argc, string argv[]){
    const int initial_buffer_size = 4096;
    uint8_t stdin_provided = 0;

    string buffer = malloc(initial_buffer_size);
    uint64_t buffer_size = initial_buffer_size;
    string buf_ptr = buffer;

    while (
        fread(buf_ptr, sizeof(char), stdin_provided ? buffer_size / 2 : buffer_size, stdin)
    ){
        stdin_provided = 1;

        buffer = realloc(buffer, buffer_size * 2);
        buf_ptr = &buffer[buffer_size];
        buffer_size = buffer_size * 2;
    };

    if (!stdin_provided && argc < 2 || (argc >= 2 ? !strcmp("--help", argv[1]) : 0)) {
        puts("Usage: md5 [OPTIONS] [STRING ARGUMENT]");

        return 0;
    }

    string data = stdin_provided ? buffer : argv[1];
    string hash = md5(data);
    printf("%s\n", hash);

    return 0;
}

