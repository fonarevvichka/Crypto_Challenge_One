#include "bitpack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "cryptography.h"

int main() 
{       
    char* message = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int length = strlen(message);

    uint8_t* input_in_binary = unpack_hex_to_binary(message, length);

    length /= 2;



    /* intialize frequency table */
    double** frequency_table = malloc(sizeof(double*) * 256);
    
    for (int i = 0; i < 256; i++) {
        frequency_table[i] = malloc(sizeof(double) * 27);
        double* frequency = frequency_table[i];

        for (int k = 0; k < 27; k++) {
            frequency[k] = 0.0;
        }
    }
    /* intialize frequency table */
    

    /* populate frequency table */
    uint8_t** all_decryptions = malloc(sizeof(uint8_t*) * 256);

    for (int i = 0; i < 256; i++) { /* iterate through all possible bytes */
        all_decryptions[i] = single_char_xor(input_in_binary, length, i);
        calculate_char_freq(all_decryptions[i], length, frequency_table[i]);
    }
    /* populate frequency table */

    /* evaluate frequency table */
    int best_option = evaluate_char_freq(frequency_table, length);
    /* evaluate frequency table */

    decode_hex(all_decryptions[best_option], length); /* print best option */

    /* free memory */
    for (int i = 0; i < 256; i++) {
        free(frequency_table[i]);
        free(all_decryptions[i]);
    }

    free(all_decryptions);
    free(frequency_table);
    free(input_in_binary);
    /* free memory */

    return 0;
}