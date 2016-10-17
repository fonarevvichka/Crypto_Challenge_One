from binascii import unhexlify
import base64

def hexToBase64(s):
    rawBytes = unhexlify(s)
    return base64.b64encode(rawBytes)
def deHex(s):
    return unhexlify(s)

