import binascii


def fixedXorCompare(s):
    return hex(int(s, 16) ^ int("686974207468652062756c6c277320657965", 16))[2:]
def char(s, key):
    key = hex(ord(key))[2:]
    key = key * int(len(s)/2)
    xorResult = int(s, 16) ^ int(key, 16)
    hexResult = hex(xorResult)[2:]
    # print (hexResult)
    try:
        return bytearray.fromhex(hexResult).decode('UTF-8', 'ignore')
    except ValueError:
        return "zzzzz"
def convertStrToHex(s):
    convertedString = ''
    for i in range(0, len(s)):
        convertedString += hex(ord(s[i]))[2:]
    return convertedString

def repeatingKey(s, key):
    hexResult = ''
    # print(key)
    for i in range(0, int((len(s))/2)):
        sChar = s[(2*i)] + s[(2*i)+1]
        keyChar = key[(2*i) % len(key)] + key[(2*i)%len(key) + 1]
        if(len(hex(int(sChar, 16) ^ int(keyChar, 16))[2:]) < 2):
            hexResult += "0"
        hexResult += hex(int(sChar, 16) ^ int(keyChar, 16))[2:]
    return hexResult
