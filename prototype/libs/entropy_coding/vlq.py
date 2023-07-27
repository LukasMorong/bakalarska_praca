#ABvvvvvv Bvvvvvvv
#A - sign
#B - octet follows

def encode(num_arr):
    result = ''

    for number in num_arr:
        result = result + encode_number(number)

    return result


def encode_number(number):
    bit_string = format(abs(int(number)), f'b')
    
    last_octet = True
    result = ''

    while len(bit_string) > 6:
        octet_data = bit_string[-7:]
        bit_string = bit_string[:-7]
        
        if last_octet:
            result = '0' + octet_data + result
            last_octet = False
        else:
            result = '1' + octet_data + result


    sign_bit = '0'

    if number < 0:
        sign_bit = '1'


    if last_octet:
        result = '0' + sign_bit + (6 - len(bit_string)) * '0' + bit_string + result
    else:
        result = '1' + sign_bit + (6 - len(bit_string)) * '0' + bit_string + result



    return result

def decode(bit_string):
    numbers = []

    while len(bit_string) != 0:
        result = ''
        first_octet = True
        last_octet = False
        sign = '+'

        while last_octet != True:
            sub_string = bit_string[:8]
            bit_string = bit_string[8:]

            if first_octet:
                octet_data = sub_string[2:]

                if sub_string[0] == '0':
                    last_octet = True
                
                if sub_string[1] == '1':
                    sign = '-'

                first_octet = False
            
            else:
                octet_data = sub_string[1:]
                
                if sub_string[0] == '0':
                    last_octet = True

            result = result + octet_data

        if sign == '-':
            numbers.append(-1 * int(result, 2))
        else:
            numbers.append(int(result, 2))

    return numbers

if __name__ == "__main__":
    numbers = [1, 18, -356, 0, 0, -1, 47]
    print(numbers)

    encoded = encode(numbers)
    print(encoded)

    decoded = decode(encoded)
    print(decoded)