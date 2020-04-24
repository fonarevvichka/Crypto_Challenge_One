#ifndef CRYPTOGRAPHY_INCLUDED
#define CRYPTOGRAPHY_INCLUDED

#include "binary_message.h"

int convert_hex_ascii_to_dec(int value);
int convert_hex_to_ascii(int value);
uint8_t base64_ascii_to_dec(int value);
uint8_t* unpack_hex_to_binary(char* input, int length);
void calculate_char_freq(uint8_t* binary_data, int length, double* frequency_counter);
int evaluate_char_freq(double** frequency_table, int length);
void pretty_print_base64(uint8_t* binary_data, int length);
void pretty_print_hex(uint8_t* binary_data, int length);
int binary_hex_to_ascii(uint8_t value);
void decode_hex(uint8_t* binary_data, int length);
binary_message unpack_ascii_message(char* message, int length);
binary_message unpack_hex_message(char* input, int length);
binary_message unpack_base64_message(char* input);
uint8_t* single_char_xor(uint8_t* left, int length, uint8_t right_byte);
uint8_t* equal_length_xor(uint8_t* left, uint8_t* right, int length);
binary_message xor(binary_message message, binary_message key);

binary_message read_base64_file(FILE* file);

int calculate_hamming_distance(char* left, char* right);
#endif