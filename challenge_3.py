
#!/usr/bin/python3
import helper_func
import binascii
import string


if __name__ == "__main__":
    # ALPHABET = list(string.ascii_lowercase)
    # for letter in ALPHABET:
    #     input_bytes = bytes.fromhex('1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736')
       
    #     hex_letter = hex(ord(letter))[2:4]
    #     single_byte = bytes.fromhex(hex_letter)
        
    #     print(helper_func.single_byte_xor(input_bytes, single_byte))

    helper_func.fixed_xor('1c0111001f010100061a024b53535009181c')