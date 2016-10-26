import binascii
import base64

import conversions
import xor
import singleCharXor
# works
from repeatingKeyXor import repeatingKeyXor

def editDistanceCalc(s1, s2):
    s1Converted = xor.hexToString(s1)
    s2Converted = xor.hexToString(s2)

    s1Bit = returnBits(s1Converted)
    s2Bit = returnBits(s2Converted)

    convertedStringOne = str(s1Bit)
    convertedStringTwo = str(s2Bit)

    lengthOne = len(convertedStringOne)
    lengthTwo = len(convertedStringTwo)

    differences = 0
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
    # print(s)
    shortenedS1 = s[:keysize]
    shortenedS2 = s[keysize:2*keysize]
    shortenedS3 = s[keysize*2:keysize*3]
    shortenedS4 = s[keysize*3:keysize*4]
    shortenedS5 = s[keysize*4:keysize*5]
    shortenedS6 = s[keysize*5:keysize*6]
    temp1 = editDistanceCalc(shortenedS1, shortenedS2)/keysize
    temp2 = editDistanceCalc(shortenedS3, shortenedS4)/keysize
    temp3 = editDistanceCalc(shortenedS5, shortenedS6)/keysize
    # print(temp1, " ", temp2, " ", temp3)
    return (temp1 + temp2 + temp3)/3
# works
def base64toHex(s):
    rawBytes = base64.b64decode(s)
    return binascii.hexlify(rawBytes)
def findKeyLength(s):
    highScore = 666666
    for k in range(2, 25):
        tempLowScore = returnEditDistance(s, 2*k)
        if(highScore > tempLowScore):
            optimalKeyLength = k
            highScore = tempLowScore
            # print(optimalKeyLength)
        # print(highScore)
    return optimalKeyLength
def createNewSringFromKey(s, keyLength):
    newStrings = list()
    temp = ''
    print(s)
    for k in range(0, keyLength):
        for j in range(0, int(len(s)/keyLength)-1):
            temp += s[j*(keyLength) + k]
        newStrings.append(temp)
        temp = ''
    return newStrings
def caller():
    # file stuff
    file = open("xorCrack.txt", 'r')
    s = file.read()
    s = base64toHex(s)
    s = str(s)[2:len(s)+2]
    s = s.upper()
    # file stuff

    # get key length
    keyLength = findKeyLength(s) + 1
    # get key length

    strings = createNewSringFromKey(s, keyLength)
    # print(strings)
    key = ''
    # print(keyLength)
    for i in range(0, keyLength):
        key += singleCharXor.crack(strings[i])
        # print(strings[i])
    print(key)
    # print(base64toHex(s).upper())
    # (xor.hexToString(xor.repeatingKey(s, xor.stringToHex(key))))
caller()
# print((conversions.hexToBase64(xor.repeatingKey(xor.stringToHex("I went to the mall on a tuesday afternoon. It was a ball of fun, we partied all day and all night it was an enormous ball of fun"), "414243"))))