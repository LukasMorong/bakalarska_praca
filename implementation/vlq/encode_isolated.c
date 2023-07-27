#include <stdint.h>
#include <stdlib.h>


#define SAMPLE_COUNT 624
#define MAX_LEN (SAMPLE_COUNT * 16)
#define VLQ_OCTET_BITS 8
#define VLQ_DATA_BITS_FIRST 6
#define VLQ_DATA_BITS_NEXT 7
#define VLQ_CONTINUE_MASK (1 << 7)
#define VLQ_SIGN_MASK (1 << 6)

#define SUB_64 0
#define SUB_8192 1
#define SUB_1048576 2

// returns number of required aditional octets
// assumes that value will be < 1 048 576
unsigned int getRequiredAditional(unsigned int value) {
    if (value <= 63)
        return SUB_64;
    else if (value <= 8191)
        return SUB_8192;
    else
        return SUB_1048576;
}

void vlq_encode(volatile int16_t samples[]) {
    uint8_t output[MAX_LEN];
    int count = 0;

    for (int16_t i = 0; i < SAMPLE_COUNT; ++i) {
        int16_t number = samples[i];
        int16_t abs_num = abs(number);

        int8_t aditional = getRequiredAditional(abs_num);

        uint8_t octet = (abs_num >> (VLQ_DATA_BITS_NEXT * aditional)) & ((1 << VLQ_DATA_BITS_FIRST) - 1);

        if (number < 0) { // if the number is negative
            octet |= VLQ_SIGN_MASK; // set the sign bit
        }

        if(aditional){
            octet |= VLQ_CONTINUE_MASK;
        }

        // add octet to the beginning of the output array
        output[count++] = octet;

        while(aditional--){

            octet = (abs_num >> (VLQ_DATA_BITS_NEXT * aditional)) & ((1 << VLQ_DATA_BITS_NEXT) - 1);

            if(aditional){
                octet |= VLQ_CONTINUE_MASK;
            }

            output[count++] = octet;

        }
    }
}