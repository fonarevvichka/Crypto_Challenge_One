import binascii


def fixedXorCompare(s):
    return hex(int(s, 16) ^ int("686974207468652062756c6c277320657965", 16))[2:]

def char(s, key):
    key = hex(ord(key))[2:]
    key = key * int(len(s)/2)
    xorResult = int(s, 16) ^ int(key, 16)
    hexResult = hex(xorResult)[2:]
    print (hexResult)
    return bytearray.fromhex(hexResult).decode('UTF-8')
