# Komprese dat používaných pro lokalizaci zařízení
## https://www.vut.cz/studenti/zav-prace/detail/147092
## Lukas Morong, xmoron01
## 2023
---
---

# Prototype
Inside ./prototype folder
## Requirements:
    Python 3.x
    Jupyter Notebook (tested on version 7.0.0)
## Libraries:
    numpy
    matplotlib
    scipy
    pandas

## Installation
```
pip install -r requirements.txt
```
## Run
### prototypeDesign.ipynb - contains process of analysis and prototype design
### final_stats.ipynb - contains final stats and graph plots
```
jupyter notebook
```

# Implementation
Inside ./implementation folder
## Requirements:
    GNU Arm Embedded Toolchain
        - arm-none-eabi-as
        - arm-none-eabi-gcc
        - arm-none-eabi-ld
        - arm-none-eabi-objcopy
    qemu
    qemu-system-arm
## Libraries:
    strandard libraries

## Run
Constains two groups of files:
 - compress/decompress
    - standalone working demos of algorithms
    - used for runtime instruction caunt
- compress_isolated/decompress_isolated
    - contains isolated functions of algorithms
    - not runnable
    - used to determine asm instruction count after compilation
### Print available versions
```
make
```
then run by
```
make <version>
```
terminate run by ctrl+a then x

Output:
- log.txt - instructions
- output.txt - standard out