import English
import xor

Alphabet = 'ABCDEFGHIGKLMNOPQRSTUVWXYZ'
highScore = 0
key = ''
s = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
for letter in Alphabet:
    if (English.matchScore(xor.char(s, letter))) > highScore:
        key = letter
        highScore = English.matchScore(xor.char(s, letter))
# print(key)
print(xor.char(s, key))
