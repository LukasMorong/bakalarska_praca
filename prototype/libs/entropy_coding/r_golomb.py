from math import floor, log2


def truncated_binary_encoding(n: int, b: int) -> str:
    """Return string representing given number in truncated binary encoding.
        n:int, number to convert to truncated binary encoding.
        b:int, maximal size.
    """
    k = floor(log2(b))
    u = (1 << k+1) - b
    return f"{{0:0{k}b}}".format(n if n < u else n+u)


def encode(val_arr, divider):
    result = []

    for val in val_arr:
        val = encode_s(int(val))

        q = int(val/divider)
        r = val%divider

        result += unary_encode(q) + truncated_binary_encoding(r, divider)
    
    return ''.join(result)

def decode(bit_arr, divider):
    pass

def unary_encode(number):
    return number * '1' + '0'

def unary_decode(bin_str):
    return len(bin_str) - 1

#   negatine    ( 2n-1 )
#   positive    ( 2m )
def encode_s(val):
    
    if val < 0:
        return -2 * val - 1
    else:
        return 2 * val

def decode_s(val):
    
    if val % 2 == 1:
        return int((val + 1) / -2)
    else:
        return int(val / 2)


if __name__ == "__main__":
    numbers = [-18, 0, -0, -1, 68, 44]
    print(numbers)

    encoded = encode(numbers, 32)
    print(encoded)

    decoded = decode(encoded, 32)
    print(decoded)

    print(unary_encode(5))
    print(unary_decode('111110'))