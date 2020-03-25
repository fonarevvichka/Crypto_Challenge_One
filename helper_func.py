#!/usr/bin/python3
import base64
import binascii

def hex_to_64(hex_input):
    message_bytes = binascii.unhexlify(hex_input) # converts string to hex bytes
    base64_bytes = base64.b64encode(message_bytes) # encode those bytes to base64
    
    return base64_bytes

def base64_to_hex(base64_bytes):
    message_bytes = base64.b64decode(base64_bytes) # encode those bytes to base64
    hex_ouput = binascii.hexlify(message_bytes)
    
    return hex_ouput
    
def fixed_xor(hex_input):
    fixed_string = '686974207468652062756c6c277320657965'

    fixed_bytes = bytes.fromhex(fixed_string)
    input_bytes = bytes.fromhex(hex_input)
    resulting_bytes = bytes(a ^ b for a, b in zip(fixed_bytes, input_bytes))
    
    return resulting_bytes.hex()

# def single_byte_xor(hex_input):
#     print("blah")

if __name__ == "__main__":
    xor_result = fixed_xor('1c0111001f010100061a024b53535009181c')
    print(xor_result)