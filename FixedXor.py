import conversions
from binascii import hexlify

def fixedXorCompare(s):
    return hex(int(s, 16) ^ int("686974207468652062756c6c277320657965", 16))[2:]

print(fixedXorCompare("1c0111001f010100061a024b53535009181c"))
