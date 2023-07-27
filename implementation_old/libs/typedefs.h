#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef struct {
    int16_t i;
    int16_t q;
} IQ;

typedef struct {
    IQ *samples;
    int8_t *ant;
} IQData;

#endif  // TYPEDEFS_H