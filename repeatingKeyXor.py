import binascii

def repeatintKeyXor(s, key):
    return s

def repeatKey(s, key):
    repeatedKey = ''
    j = 0
    while j < int(len(s)/len(key)):
        i = 0
        print (len(key))
        while i < int(len(key)-1):
            repeatedKey += key[i] + key[i+1]
            i += 2
            # print(i)
            # print (repeatedKey)
        j += 1
    return repeatedKey
