#include "bitpack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "string.h"
#include "cryptography.h"

int main() 
{       
    // FILE* message_file = fopen("message.txt", "r");
    // FILE* key_file = fopen("key.txt", "r");

    // char*   line_buf          = NULL;
    // char*   key_buf           = NULL;
    // size_t  buf_size          = 1;
    // size_t  line_length       = 0;
    // size_t  key_length        = 0;

    // key_length          = getline(&key_buf, &buf_size, key_file);
    // binary_message key  = unpack_ascii_message(key_buf, key_length);

    // line_length = getline(&line_buf, &buf_size, message_file);
    // while (line_length != -1) {
    //     binary_message message = unpack_ascii_message(line_buf, line_length);
        
    //     binary_message result = xor(message, key);

    //     pretty_print_hex(result -> message, message -> length);
        
    //     /* free memory */
    //     free(message -> message);
    //     free(message);
    //     free(result -> message);
    //     free(result);
    //     /* free memory */
    
    //     line_length = getline(&line_buf, &buf_size, message_file);
    // }

    // free(key -> message);
    // free(key);
//--------------------------------------------------------------------------/
    
    char* plaintext_message = "Burning 'em, if you ain't quick and nimble \nI go crazy when I hear a cymbal";
    int length = strlen(plaintext_message);
    
    binary_message message = unpack_ascii_message(plaintext_message, length);
    
    char* plaintext_key = "ICE";
    int key_length = strlen(plaintext_key);
    
    binary_message key = unpack_ascii_message(plaintext_key, key_length);
    
    binary_message result = xor(message, key);

    pretty_print_hex(result -> message, result -> length);
    
    /* free memory */
    free(key -> message);
    free(key);
    free(message -> message);
    free(message);
    free(result -> message);
    free(result);
    /* free memory */


    return 0;
}