/* Last Modified: March 5th, 2020
 * Brian Savage and Vichka Fonarev
 * bsavag01         vfonar01
 * 
 * Comp40 - HW4 - Arith
 * bitpack.h
 * Does: interface for bitpacking
 * Possible Errors: Handles all unit testing and (de)compression properly
 */

#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED

#include <stdbool.h>
#include <stdint.h>

#define UNSIGNED uint8_t
#define SIGNED int8_t
#define SIZE 8

bool Bitpack_fitsu(UNSIGNED n, unsigned width);
bool Bitpack_fitss( SIGNED n, unsigned width);

UNSIGNED Bitpack_getu(UNSIGNED word, unsigned width, unsigned lsb);
SIGNED Bitpack_gets(UNSIGNED word, unsigned width, unsigned lsb);

UNSIGNED Bitpack_newu(UNSIGNED word, unsigned width, unsigned lsb, 
		      UNSIGNED value); 
UNSIGNED Bitpack_news(UNSIGNED word, unsigned width, unsigned lsb, 
		      SIGNED value);

#endif
