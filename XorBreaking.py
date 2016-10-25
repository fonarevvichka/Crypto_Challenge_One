import binascii
import base64

import xor
import singleCharXor
# works
def editDistanceCalc(s1, s2):

    # s1 = bytearray.fromhex(s1[2:]).decode()
    # s2 = bytearray.fromhex(s2).decode()

    s1Bit = returnBits(s1)
    s2Bit = returnBits(s2)
    convertedStringOne = str(s1Bit)
    convertedStringTwo = str(s2Bit)
    differences = 0
    lengthOne = len(convertedStringOne)
    lengthTwo = len(convertedStringTwo)

    for k in range(0, max(lengthOne, lengthTwo)):
        if(convertedStringOne[k % lengthOne] != convertedStringTwo[k % lengthTwo]):
            differences += 1

    return differences
# works
def returnBits(s):
    hexString = ''
    for k in range(0, len(s)):
        hexString += hex(ord(s[k]))[2:]
    return bin(int(hexString, 16))[2:]
# works
def returnEditDistance(s, keysize):
    shortenedS1 = s[:keysize]
    shortenedS2 = s[keysize:2*keysize]
    # print(shortenedS1)
    # print(shortenedS2)
    shortenedS3 = s[keysize*2:keysize*3]
    shortenedS4 = s[keysize*3:keysize*4]
    shortenedS5 = s[keysize*4:keysize*5]
    shortenedS6 = s[keysize*5:keysize*6]

    temp1 = editDistanceCalc(shortenedS1, shortenedS2)/keysize
    temp2 = editDistanceCalc(shortenedS3, shortenedS4)/keysize
    temp3 = editDistanceCalc(shortenedS5, shortenedS6)/keysize
    return (temp1 + temp2 + temp3)/3
# works
def base64toHex(s):
    rawBytes = base64.b64decode(s)
    return binascii.hexlify(rawBytes)
def findKeyLength(s):
    highScore = 666666
    for k in range(2, 22):
        tempLowScore = returnEditDistance(s, 2*k)
        if(highScore > tempLowScore):
            optimalKeyLength = 2*k
            highScore = tempLowScore
    print(optimalKeyLength)
    return optimalKeyLength
def createNewSringFromKey(fileName, keyLength):
    file = open(fileName, "r")
    temp = ''
    newStrings = list()
    originalLine = file.read()
    originalLine = str(base64toHex(originalLine))[2:len(originalLine)+2]
    # print(originalLine)
    originalLine = originalLine #error out of range
    # print(originalLine)
    for k in range(0, keyLength):
        for j in range(0, int(len(originalLine)/keyLength)-1):
            temp += originalLine[j*(keyLength) + k]
        newStrings.append(temp)
        temp = ''
    return newStrings


file = open("xorCrack.txt", 'r')
s = base64toHex(file.read())
s = str(s)[2:len(s)+2]
# print(s)
keyLength = findKeyLength(s)
strings = createNewSringFromKey("xorCrack.txt", keyLength)
key = ''
print(s)
print(strings)
for i in range(0, keyLength):
    # print(i)
    # print(strings[i])
    key += singleCharXor.crack(strings[i])
    print(key)
print(key)
hexResult = xor.repeatingKey(s, key)
print(bytearray.fromhex(hexResult).decode())