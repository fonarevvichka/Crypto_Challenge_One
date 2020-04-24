#include "bitpack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "cryptography.h"
#include <math.h>

 #define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static double english_freq[] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074, .13000             // V-Z, ' '
};

uint8_t base64_ascii_to_dec(int value) {
        if (value > 64 && value < 91) { /* upper case letters */
                return value - 65;
        } else if (value > 96 && value < 123) { /* upper case */
                return value - 97 + 26;
        } else if (value > 47 && value < 58) { /* numbers 0-9 */
                return value - 48 + 26 + 26;
        } else if (value == '+') {
                return 62;
        } else {
                return 63;
        }
}

int convert_hex_ascii_to_dec(int value) {
        if (value > 47 && value < 58) {/* digit */
                return value - 48;
        } else if (value > 96 && value < 123) {
                return value - 97 + 10;
        }

        fprintf(stderr, "Big Bad No Good Value \n");

        exit(0);
}

int convert_hex_to_ascii(int value) {
        if (value >= 0 && value < 10) {
                return value + 48;
        } else if (value > 9 && value < 17) {
                return value - 10 + 97;
        }
        return -1;
}

uint8_t* unpack_hex_to_binary(char* input, int length) {
        uint8_t* base2 = malloc(sizeof(uint8_t) * (length /2));

        for (int i = 0; i < length; i+= 2) {
                uint8_t first_val = input[i];
                uint8_t second_val = input[i+1];
                
                first_val = convert_hex_ascii_to_dec(first_val);
                second_val = convert_hex_ascii_to_dec(second_val);

                uint8_t packed_value = 0;
                packed_value = Bitpack_newu(packed_value, 4, 4, Bitpack_getu(first_val, 4, 0));
                packed_value = Bitpack_newu(packed_value, 4, 0, Bitpack_getu(second_val, 4, 0));
                
                base2[i/2] = packed_value;
                

        }

        return base2;    
}

binary_message unpack_hex_message(char* input, int length) {
        binary_message message = malloc(sizeof(struct binary_message));
        assert(message != NULL);
        
        uint8_t* base2 = malloc(sizeof(uint8_t) * (length /2));
        assert(base2 != NULL);

        for (int i = 0; i < length; i+= 2) {
                uint8_t first_val = input[i];
                uint8_t second_val = input[i+1];
                
                first_val = convert_hex_ascii_to_dec(first_val);
                second_val = convert_hex_ascii_to_dec(second_val);

                uint8_t packed_value = 0;
                packed_value = Bitpack_newu(packed_value, 4, 4, Bitpack_getu(first_val, 4, 0));
                packed_value = Bitpack_newu(packed_value, 4, 0, Bitpack_getu(second_val, 4, 0));
                
                base2[i/2] = packed_value;
                

        }

        message -> message = base2;
        message -> length = length / 2;
        return message;
}

binary_message unpack_base64_message(char* input) {
        int message_length = strlen(input);

        binary_message message = malloc(sizeof(struct binary_message));
        message -> message = malloc(sizeof(uint8_t) * message_length * 3 / 4);
        message -> length = message_length * 3 / 4;

        for (int i = 0; i < message_length; i += 4) {
                uint8_t high            = base64_ascii_to_dec(input[i]);
                uint8_t high_mid        = base64_ascii_to_dec(input[i+1]);
                uint8_t low_mid         = base64_ascii_to_dec(input[i+2]);
                uint8_t low             = base64_ascii_to_dec(input[i+3]);

                uint8_t packed_low      = 0;
                uint8_t packed_mid      = 0;
                uint8_t packed_high     = 0;

                packed_low = Bitpack_newu(packed_low, 6, 0, Bitpack_getu(low, 6, 0));
                packed_low = Bitpack_newu(packed_low, 2, 6, Bitpack_getu(low_mid, 2, 0));
                
                packed_mid = Bitpack_newu(packed_mid, 4, 0, Bitpack_getu(low_mid, 4, 2));
                packed_mid = Bitpack_newu(packed_mid, 4, 4, Bitpack_getu(high_mid, 4, 0));

                packed_high = Bitpack_newu(packed_high, 2, 0, Bitpack_getu(high_mid, 2, 4));
                packed_high = Bitpack_newu(packed_high, 6, 2, Bitpack_getu(high, 6, 0));

                int index = i * 3 / 4;
                message -> message[index] = packed_high;
                message -> message[index + 1] = packed_mid;
                message -> message[index + 2] = packed_low;
        }

        return message;
}

binary_message unpack_ascii_message(char* input, int length) {
        binary_message message = malloc(sizeof(struct binary_message));
        assert(message != NULL);
        
        uint8_t* base2 = malloc(sizeof(uint8_t) * length);
        assert(base2 != NULL);

        for (int i = 0; i < length; i++) {
                uint8_t val = input[i];

                uint8_t packed_value = 0;
                packed_value = Bitpack_newu(packed_value, 8, 0, val);
        
                base2[i] = packed_value;
        }

        message -> message = base2;
        message -> length = length;

        return message;
}

uint8_t* equal_length_xor(uint8_t* left, uint8_t* right, int length) {
        uint8_t* result = malloc(sizeof(uint8_t) * length);
 
        for (int i = 0; i < length; i++) {
                uint8_t left_block      = left[i];
                uint8_t right_block     = right[i];
                result[i]               = left_block ^ right_block;
        }
        return result;
}

uint8_t* single_char_xor(uint8_t* left, int length, uint8_t right_byte) {
        uint8_t* right = malloc(sizeof(uint8_t) * length);

        for (int i = 0; i < length; i++) {
                right[i] = right_byte;
        }

        uint8_t* result = equal_length_xor(left, right, length);

        free(right);

        return result;
}

binary_message xor(binary_message message, binary_message key) {
        int message_length      = message       -> length;
        int key_length          = key           -> length;
        
        binary_message result = malloc(sizeof(struct binary_message));
        assert(result != NULL);
        result -> message = malloc(sizeof(uint8_t) * message_length);
        assert(result -> message != NULL);
        result -> length = message_length;

        uint8_t* binary_message = message -> message;
        uint8_t* result_message = result -> message;
        uint8_t* key_message    = key -> message;
        for (int i = 0; i < message_length; i++) {
                uint8_t message_value   = binary_message[i];
                uint8_t key_value       = key_message[i % key_length];
                result_message[i]       = message_value ^ key_value;
        }

        return result;
}

void calculate_char_freq(uint8_t* binary_data, int length, double* frequency_counter) {
        for (int i = 0; i < length; i++) { /* iterate through binary data */
                uint8_t curr_char = binary_hex_to_ascii(binary_data[i]);
                if (curr_char > 96 && curr_char < 123) { /* valid lower letter */
                        frequency_counter[curr_char - 97]++;
                } else if (curr_char > 65 && curr_char < 91) { /* upper case */
                        frequency_counter[curr_char - 65]++;
                } else if (curr_char == 32) { /* space */
                        frequency_counter[26]++;
                }
        }
}

int evaluate_char_freq(double** frequency_table, int length) {
        double sum_of_offset[255];
        for (int i = 0; i < 255; i++) {
                double* frequency = frequency_table[i];
                
                for (int k = 0; k < 27; k++) {
                        frequency[k] /= length;
                        frequency[k] = fabs(frequency[k] - english_freq[k]);
                }
                sum_of_offset[i] = 0;
        }

        for (int i = 0; i < 255; i++) {
                for (int k = 0; k < 27; k++) {
                        sum_of_offset[i] += (frequency_table[i])[k];
                }
        }

        /* find min */
        double min = 100;
        int best_option = -1;
        for (int i = 0; i < 255; i++) {
                double curr_val = sum_of_offset[i];

                if (curr_val < min) {
                        min = curr_val;
                        best_option = i;
                }
        }
        /* find min */

        return best_option;
}

int binary_hex_to_ascii(uint8_t value) {
        uint8_t low_four = Bitpack_getu(value, 4, 0);
        uint8_t high_four = Bitpack_getu(value, 4, 4);

        return high_four * 16 + low_four;
}

void decode_hex(uint8_t* binary_data, int length) {
        for (int i = 0; i < length; i++) {
                printf("%c", binary_hex_to_ascii(binary_data[i]));
        }
        printf("\n");
}

void pretty_print_base64(uint8_t* binary_data, int length) {
        for (int i = 0; i < length; i += 3) {
                uint8_t high_six        = 0;
                uint8_t high_mid_six    = 0;
                uint8_t low_mid_six     = 0;
                uint8_t low_six         = 0;

                uint8_t first_int       = binary_data[i];
                uint8_t second_int      = binary_data[i+1];
                uint8_t third_int       = binary_data[i+2];


                high_six = Bitpack_newu(high_six, 6, 0, Bitpack_getu(first_int, 6, 2));
                
                high_mid_six = Bitpack_newu(high_mid_six, 2, 4, Bitpack_getu(first_int, 2, 0));
                high_mid_six = Bitpack_newu(high_mid_six, 4, 0, Bitpack_getu(second_int, 4, 4));
                
                low_mid_six = Bitpack_newu(low_mid_six, 4, 2, Bitpack_getu(second_int, 4, 0));
                low_mid_six = Bitpack_newu(low_mid_six, 2, 0, Bitpack_getu(third_int, 2, 6));
                
                low_six = Bitpack_newu(low_six, 6, 0, Bitpack_getu(third_int, 6, 0));

                printf("%c%c%c%c", encoding_table[high_six], encoding_table[high_mid_six]
                                 , encoding_table[low_mid_six], encoding_table[low_six]);
        }
        printf("\n");
}

void pretty_print_hex(uint8_t* binary_data, int length) {
        for (int i = 0; i < length; i++) {
                uint8_t high_four = Bitpack_getu(binary_data[i], 4, 4);
                uint8_t low_four = Bitpack_getu(binary_data[i], 4, 0);

                printf("%c%c", convert_hex_to_ascii(high_four), convert_hex_to_ascii(low_four));
        }
        printf("\n");
}

/* strings must be the same length */
int calculate_hamming_distance(char* left, char* right) {
        binary_message left_message = malloc(sizeof(struct binary_message));
        binary_message right_message = malloc(sizeof(struct binary_message));


        /* create left message */
        int left_length = strlen(left);
        int right_length = strlen(right);

        int min_length = MIN(left_length, right_length);
        
        left_message -> message = malloc(sizeof(uint8_t) * min_length);
        right_message -> message = malloc(sizeof(uint8_t) * min_length);

        left_message -> length  = min_length;
        right_message -> length = min_length;

        for (int i = 0; i < min_length; i++) {
                left_message    -> message[i] = left[i];
                right_message   -> message[i] = right[i];
        }

        int total_differences = 0;
        for (int i = 0; i < min_length; i++) {
                uint8_t left_word = left_message -> message[i];
                uint8_t right_word = right_message -> message[i];
                for (int k = 0; k < 8; k++) {
                        uint8_t left_bit = Bitpack_getu(left_word, 1, k);
                        uint8_t right_bit = Bitpack_getu(right_word, 1, k);
                
                        if (left_bit != right_bit) {
                                total_differences++;
                        }
                }
        }
        return total_differences;
}