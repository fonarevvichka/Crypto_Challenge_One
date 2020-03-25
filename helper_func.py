#!/usr/bin/python3
import base64
import binascii

def hex_to_64(hex_input):
    message = binascii.unhexlify(hex_input)
    print(message)
    base64_bytes = base64.b64encode(message)

    return base64_bytes

def fixed_xor(hex_input):
    fixed_string = "686974207468652062756c6c277320657965"

    result = int(hex_input, 16) ^ int(fixed_string, 16)
    
    return hex(result)

if __name__ == "__main__":
    print(fixed_xor("1c0111001f010100061a024b53535009181c"))