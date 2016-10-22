import xor

def repeatingKeyXor(s, key):
    key = convertStrToHex(key)
    s = convertStrToHex(s)
    return xor.repeatingKey(s, key)
def repeatingKeyXorFromFile(fileName, key):
    textToEncrypt = open(fileName, "r")
    encryptedMessage = ''
    for i in range(0,2):
        s = textToEncrypt.read()
        # print(s)
        # print(encryptedMessage)
    return repeatingKeyXor(s, key)

def convertStrToHex(s):
    convertedString = ''
    for i in range(0, len(s)):
        convertedString += hex(ord(s[i]))[2:]
    return convertedString

print(repeatingKeyXorFromFile("message.txt", 'ICE'))
# (repeatingKeyXorFromFile("message.txt", "ICE"))
