#include <stdint.h>

#define SAMPLE_COUNT 624

void delta_decompress(volatile int16_t i_samples[], volatile int16_t q_samples[]){
    int16_t previousI = 0;
    int16_t previousQ = 0;

    int16_t i_result[SAMPLE_COUNT];
    int16_t q_result[SAMPLE_COUNT];

    for(int i = 0; i < SAMPLE_COUNT; i++){
        previousI += i_samples[i];
        i_result[i] = previousI;

        previousQ += q_samples[i];
        q_result[i] = previousQ;
    }
}