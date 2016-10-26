import English
import xor
def crack(s):
    Alphabet = 'ABCDEFGHIGKLMNOPQRSTUVWXYZ'
    highScore = 0
    key = ''
    for letter in Alphabet:
        matchScore = English.matchScore(xor.char(s, letter))
        if matchScore > highScore:
            # print (letter)
            key = letter
            highScore = matchScore
    # print(key)
    return key
