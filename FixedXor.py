import conversions
from operator import xor

def fixedXorCompare(s):
    return conversions.deHex(s) ^ conversions.deHex("686974207468652062756c6c277320657965")
print(fixedXorCompare("1c0111001f010100061a024b53535009181c"))
