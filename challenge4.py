import binascii
encryptedStrings = open("encryptedStrings.txt", "r")
import English
import xor

ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
highScore = 0
key = ''
bestLine = ''

for line in encryptedStrings:
    line = encryptedStrings.readline()
    # print(line)
    # print(int(line, 16))
    # print(hex(intLine)[2:])
    for letter in ALPHABET:
        if (English.matchScore(xor.char(line, letter)) > highScore):
            key = letter
            bestLine = line
            highScore = English.matchScore(xor.char(line, letter))
# print(xor.char(bestLine, key))
