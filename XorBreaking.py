import English
import binascii
import base64

def editDistanceCalc(s1, s2):
    s1Bit = returnBits(s1)
    s2Bit = returnBits(s2)
    convertedStringOne = str(s1Bit)
    convertedStringTwo = str(s2Bit)
    differences = 0
    lengthOne = len(convertedStringOne)
    lengthTwo = len(convertedStringTwo)
    # lengthThree = len(convertedStringThree)
    # legnthFour = len(convertedStringFour)

    for k in range(0, max(lengthOne, lengthTwo)):
        if(convertedStringOne[k % lengthOne] != convertedStringTwo[k % lengthTwo]):
            differences += 1

    return differences
def returnBits(s):
    hexString = ''
    for k in range(0, len(s)):
        hexString += hex(ord(s[k]))[2:]
    return bin(int(hexString, 16))[2:]
def returnEditDistance(s, keysize):
    shortenedS1 = s[:keysize]
    shortenedS2 = s[keysize:2*keysize]
    shortenedS3 = s[keysize*2:keysize*3]
    shortenedS4 = s[keysize*3:keysize*4]
    temp = editDistanceCalc(shortenedS1, shortenedS2)/keysize
    temp2 = editDistanceCalc(shortenedS3, shortenedS4)/keysize
    return temp + temp2 / 2
def base64toHex(s):
    rawBytes = base64.b64decode(s)
    return binascii.hexlify(rawBytes)
def breakRepeatingXor(s):
    file = open(s, 'r')
    s = base64toHex(file.read())
    s = str(s)[2:len(s)+2]
    print(s)
    highScore = 666
    tempHighScore = 666
    for k in range(2, 41):
        tempHighScore = min(highScore, returnEditDistance(s, k))
        if(highScore != tempHighScore):
            optimalKeyLength = k
            highScore = tempHighScore

    return optimalKeyLength

keyLength = (breakRepeatingXor("xorCrack.txt"))

