"""
File name: slq.py
Author: Lukas Morong, xmoron01
Year: 2023
Description: Static length coding
            package used to imitate c language static size datatypes
            is used to save values in bitfield and enables to calculate total length
"""

def encode(num_arr):
    result = ''

    #int_bit_size = bites_required(num_arr)
    int_bit_size = 2

    for number in num_arr:
        bin_number = list(format(abs(int(number)), f'0{int_bit_size*8}b'))

        if number < 0:
            bin_number[0] = '1'

        result = result + ''.join(bin_number)

    return result, int_bit_size

def bites_required(num_arr):
    max_len = 0

    for number in num_arr:
        bit_len = int(number).bit_length()

        if max_len < bit_len:
            max_len = bit_len

    #signbit
    max_len += 1

    if max_len % 8 == 0:
        nof_bites = int(max_len/8)
    else:
        nof_bites = int(max_len/8) + 1

    return nof_bites

def decode(bit_string, int_bite_size):
    numbers = []

    while len(bit_string) > 0:
        bit_slice = list(bit_string[:int_bite_size * 8])
        bit_string = bit_string[int_bite_size * 8:]

        if bit_slice[0] == '1':
            bit_slice[0] = '0'
            numbers.append(-1 * int(''.join(bit_slice), 2))
        else:
            numbers.append(int(''.join(bit_slice), 2))

    return(numbers)

if __name__ == "__main__":
    numbers = [1, 18, -356, 0, 0, -1, 47]
    print(numbers)

    encoded, int_len = encode(numbers)
    print(encoded)

    decoded = decode(encoded, int_len)
    print(decoded)
