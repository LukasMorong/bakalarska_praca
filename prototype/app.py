import argparse
import os
import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import entropy

from libs.entropy_coding import slq
from libs.entropy_coding import vlq
from libs.entropy_coding import rice_golomb
from libs.data_transformation import delta_encoding


#input data
# {
#     i: [],
#     q: []
# }

#ant - how antenas were sampled

#options (t, e)
# transformation - t: [0 - none, 1 - delta, 2 - deltadelta, 3 - predictive, 4-predictivedelta, 5-predictivedeltadelta]
# entropy coding - e: [0 - none (16bit), 1 - vlq, 2 - rice golomb]

# output - bitString

def compress(inputData, ant, options):
    (t, e) = options
    bitString = []
    transformed = []

    # transformation

    if t == 0:
        transformed = inputData['i'] + inputData['q']
    elif t == 1:
        i_encoded = delta_encoding.encode(inputData['i'])
        q_encoded = delta_encoding.encode(inputData['q'])
        transformed = i_encoded + q_encoded
    elif t == 2:
        i_encoded = delta_encoding.encode(delta_encoding.encode(inputData['i']))
        q_encoded = delta_encoding.encode(delta_encoding.encode(inputData['q']))
        transformed = i_encoded + q_encoded
    elif e == 3:
        #predictive
        pass
    elif e == 4:
        #predictive delta
        pass
    elif e == 5:
        #predictive deltadelta
        pass
    

    #entropy coding
    if e == 0:
        encoded, item_len = slq.encode(transformed)
    elif e == 1:
        encoded = vlq.encode(transformed)
    elif e == 2:
        optimal = rice_golomb.find_optimal_parameter(transformed, 15)
        encoded = '{0:04b}'.format(int(optimal)) + rice_golomb.encode(transformed, 2**optimal)

    return encoded

# input - bitString

# ant - antena switching

#options (t, e)
# transformation - t: [0 - none, 1 - delta, 2 - deltadelta, 3 - predictive, 4-predictivedelta, 5-predictivedeltadelta]
# entropy coding - e: [0 - none (16bit), 1 - vlq, 2 - rice golomb]

# output
# {
#     i: [],
#     q: [],
# }

def decompress(inputData, ant, options):
    (t, e) = options
    decoded = []
    output = {"i": [], "q": []}

    #entropy decoding
    if e == 0:
        decoded = slq.decode(inputData, 2)
    elif e == 1:
        decoded = vlq.decode(inputData)
    elif e == 2:
        parameter = int(inputData[:4], 2)
        decoded = rice_golomb.decode(inputData[4:], 2**parameter)
    elif e == 3:
        #predictive
        pass
    elif e == 4:
        #predictive delta
        pass
    elif e == 5:
        #predictive deltadelta
        pass


    # reconstruction
    if t == 0:
        output['i'] = decoded[:len(decoded)//2]
        output['q'] = decoded[len(decoded)//2:]
    elif t == 1:
        delta_i = decoded[:len(decoded)//2]
        delta_q = decoded[len(decoded)//2:]

        output['i'] = list(delta_encoding.decode(delta_i))
        output['q'] = list(delta_encoding.decode(delta_q))
    elif t == 2:
        delta_i = decoded[:len(decoded)//2]
        delta_q = decoded[len(decoded)//2:]

        output['i'] = list(delta_encoding.decode(delta_encoding.decode(delta_i)))
        output['q'] = list(delta_encoding.decode(delta_encoding.decode(delta_q)))
    
    return output

def print_stats(arr, name):
    std_dev = round(np.std(arr), 2)
    min = np.min(arr)
    max = np.max(arr)
    
    print(f'Standard Deviation: {std_dev}')
    print(f'RANGE: [{min},{max}]')
    value,counts = np.unique(arr, return_counts=True)
    print(f'Entropy: {entropy(counts)}')

    slq_arr, data_i_bit_len = slq.encode(arr)
    vlq_arr = vlq.encode(arr)
    golomb = r_golomb.encode(arr, 8)

    print(f'16b_int: {len(slq_arr)} BITS')
    print(f'Variable length quantity: {len(vlq_arr) } BITS')
    print(f'Rice Golomb Coding: {len(golomb) } BITS')

    plt.rcParams["figure.figsize"] = (10,10)
    plt.hist(arr, 500, density=True, facecolor='blue', alpha=0.75)
    plt.grid(True)
    plt.title(f'HISTOGRAM ({name})')
    plt.xlabel('value')
    plt.ylabel('percentage')
    plt.show()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='File compression and decompression utility.')
    parser.add_argument('--compress', metavar='FILE', help='Compress the specified file')
    parser.add_argument('--decompress', metavar='FILE', help='Decompress the specified file')
    args = parser.parse_args()

    if args.compress:
        input_file = args.compress
        output_file = f'{input_file}.compressed'
        compress(input_file, output_file)
        print(f'File compressed successfully: {input_file} -> {output_file}')
    elif args.decompress:
        input_file = args.decompress
        output_file = os.path.splitext(input_file)[0]
        decompress(input_file, output_file)
        print(f'File decompressed successfully: {input_file} -> {output_file}')
    else:
        parser.print_help()