#include "bitpack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "cryptography.h"

void hex_to_64(char* input, int length) {
        /* convert to binary */
        uint8_t* binary_data = unpack_hex_to_binary(input, length);
        length /= 2;
        /* convert to binary */
        
        /* convert to base64*/
        pretty_print_base64(binary_data, length);
        /* convert to base64*/

        free(binary_data);
}

int main() 
{       
        char* input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        int length = strlen(input);
        hex_to_64(input, length);
        return 0;
}



