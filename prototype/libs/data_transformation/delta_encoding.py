"""
File name: delta_encoding.py
Author: Lukas Morong, xmoron01
Year: 2023
Description: Python prototype implementation of delta encoding
"""

import numpy as np

def encode(data):
    previous = 0
    compressed = []
    for val in data:
        compressed.append(val - previous)
        previous = val

    return compressed

def decode(data):
    previous = 0
    decompressed = np.array([])
    for val in data:
        decompressed = np.append(decompressed, previous + val)
        previous = previous + val

    return decompressed


if __name__ == "__main__":
    data = [1, 1, 1, -5, -10]
    print(data)

    encoded = encode(data)
    print(encoded)

    decoded = decode(encoded)
    print(decoded)
