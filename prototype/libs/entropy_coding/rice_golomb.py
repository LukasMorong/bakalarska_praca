"""
File name: rice_golomb.py
Author: Lukas Morong, xmoron01
Year: 2023
Description: Python prototype implementation of rice-golomb coding
            contains all functions needed to encode and decode
            contains function for calculating optimal parameter
"""

from math import floor, log2


def truncated_binary_encoding(x, n):
    k = floor(log2(n))
    u = (1 << k+1) - n
    
    return f"{{0:0{k}b}}".format(x if x < u else x+u)

def truncated_binary_decoding(bits, n):
    k = floor(log2(n))
    u = (1 << k+1) - n

    if(int(bits[:k], 2) < u):
        return(int(bits[:k], 2), k)

    return(int(bits[:k+1], 2) - u, k+1)


def encode(val_arr, divider):
    result = []

    for val in val_arr:
        val = encode_signed(int(val))

        q = int(val/divider)
        r = val%divider

        result += unary_encode(q) + truncated_binary_encoding(r, divider)
    
    return ''.join(result)

def decode(bitstream, m):
    numbers = []
    count = 0
    skip = 0

    for idx, bit in enumerate(bitstream):
        if(skip != 0):
            skip = skip - 1
            continue
        if(bit == '1'):
            count = count + 1
        if(bit == '0'):
            q = count*m
            count = 0

            r, skip = truncated_binary_decoding(bitstream[idx + 1:], m)

            numbers.append(decode_signed(q+r))

    return numbers


def unary_encode(number):
    return number * '1' + '0'

def unary_decode(bin_str):
    return len(bin_str) - 1

#   negatine    ( 2n-1 )
#   positive    ( 2n )
def encode_signed(val):
    
    if val < 0:
        return -2 * val - 1
    else:
        return 2 * val

def decode_signed(val):
    
    if val % 2 == 1:
        return int((val + 1) / -2)
    else:
        return int(val / 2)


def calculate_average_bit_length(data, parameter):
    encoded_data = encode(data, parameter)
    return len(encoded_data) / len(data)

#finds optimal parameter for rice golomb coding (powers of 2)
def find_optimal_parameter(data, max_parameter):
    min_avg_bit_length = float('inf')
    optimal_parameter = 1

    for parameter in range(1, max_parameter):
        avg_bit_length = calculate_average_bit_length(data, 2**parameter)
        if avg_bit_length < min_avg_bit_length:
            min_avg_bit_length = avg_bit_length
            optimal_parameter = parameter

    return optimal_parameter

if __name__ == "__main__":
    numbers = [1, 18, -356, -0, 0, -1, 47]
    print(numbers)

    optional = find_optimal_parameter(numbers, 10)
    print(optional)

    encoded = encode(numbers, optional)
    print(encoded)

    decoded = decode(encoded, optional)
    print(decoded) 

    print(unary_encode(5))
    print(unary_decode('111110'))

    print(truncated_binary_encoding(3,5))