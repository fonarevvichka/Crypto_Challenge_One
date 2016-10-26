def hexToString(s):
    convertedString = ''
    for i in range(0, len(s)//2):
       convertedString += chr(int((s[2*i] + s[2*i+1]), 16))
    return convertedString
def stringToHex(s):
    convertedS = ''
    for i in range(0, len(s)):
        convertedS += hex(ord(s[i]))[2:]
    return convertedS
def char(s, key):
    s = s.upper()
    initKey = key
    key = hex(ord(key))[2:]
    key = key * int(len(s)/2)
    if (int(len(s)/2)) * 2 != len(s):
        key += hex(ord(initKey))[2:3]
    # print(s)
    # print(key)
    xorResult = int(s, 16) ^ int(key, 16)
    hexResult = hex(xorResult)[2:]
    # print (hexResult)
    # try:
    # print(hexToString(hexResult))
    return hexToString(hexResult)
    # except ValueError:
    #     return "zzzzz"
def convertStrToHex(s):
    convertedString = ''
    for i in range(0, len(s)):
        convertedString += hex(ord(s[i]))[2:]
    return convertedString

def repeatingKey(s, key):
    hexResult = ''
    # print(len(key))
    for i in range(0, int((len(s))/2)):
        sChar = s[(2*i)] + s[(2*i)+1]
        keyChar = key[(2*i) % len(key)] + key[(2*i)%len(key) + 1]
        if(len(hex(int(sChar, 16) ^ int(keyChar, 16))[2:]) < 2):
            hexResult += "0"
        hexResult += hex(int(sChar, 16) ^ int(keyChar, 16))[2:]
    return hexResult
