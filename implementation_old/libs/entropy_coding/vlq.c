#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define VLQ_OCTET_BITS 8
#define VLQ_DATA_BITS 6
#define VLQ_CONTINUE_MASK (1 << 7)
#define VLQ_SIGN_MASK (1 << 6)

uint8_t* vlq_encode(int16_t* array, int len) {

}

int16_t* vlq_decode(uint8_t* array, size_t len, size_t* output_len) {

}