import binascii
# from Crypto.Util.strxor import strxor_c

def fixedXorCompare(s):
    return hex(int(s, 16) ^ int("686974207468652062756c6c277320657965", 16))[2:]

def char(s, key):
    key = hex(ord(key))[2:]
    key = key * int(len(s)/2)
    xorResult = int(s, 16) ^ int(key, 16)
    hexResult = hex(xorResult)[2:]
    # return hexResult
    return bytearray.fromhex(hexResult).decode()

# Alphabet = "abcdefghijklmnopqrstuvwxyz"
# s = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
# iterator = 0
# for letter in Alphabet:
#     print(char(s, letter))
#     print(letter)
#