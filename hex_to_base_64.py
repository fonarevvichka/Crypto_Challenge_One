#!/usr/bin/python3
import base64
import binascii

def hex_to_64(hex_input):
    message = binascii.unhexlify(hex_input)
    base64_bytes = base64.b64encode(message)
    base64_message = base64_bytes.decode('ascii')\

    return base64_message

if __name__ == "__main__":
    print(hex_to_64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"))