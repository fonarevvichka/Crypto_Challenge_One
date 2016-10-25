import English
import xor
def crack(s):
    Alphabet = 'ABCDEFGHIGKLMNOPQRSTUVWXYZ'
    highScore = 0
    key = ''
    for letter in Alphabet:
        if (English.matchScore(xor.char(s, letter))) > highScore:
            key = letter
            highScore = English.matchScore(xor.char(s, letter))
    return key
