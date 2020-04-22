#include "bitpack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "cryptography.h"


int main() 
{       
        char* input = "1c0111001f010100061a024b53535009181c";
        int length = strlen(input);

        char* comparable = "686974207468652062756c6c277320657965";

        uint8_t* input_in_binary = unpack_hex_to_binary(input, length);
        uint8_t* comparable_in_binary = unpack_hex_to_binary(comparable, length);
        
        length /= 2;

        uint8_t* result = equal_length_xor(input_in_binary, comparable_in_binary, length);
        pretty_print_hex(result, length);

        return 0;
}