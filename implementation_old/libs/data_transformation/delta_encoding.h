#ifndef DELTA_ENCODING_H
#define DELTA_ENCODING_H

#include <stdint.h>

int delta_encode(int16_t* input, int size);

int delta_decode(int16_t* input, int size);

#endif  // DELTA_ENCODING_H
