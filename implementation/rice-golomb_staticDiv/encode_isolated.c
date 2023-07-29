/*
 * Filename: encode_isolated.c
 * Author: Lukas Morong, xmoron01
 * Year: 2023
 * Description: 
 *     Rice golomb dekodovanie, izolovana implementacia na ucely urcenia velkosti
 *     vysledneho asembleru
 */

#include <stdint.h>

#define SAMPLE_COUNT 624
#define MAX_RESULT_LEN 16384

int16_t encode_signed(int16_t val) {
    if (val < 0) {
        return ((-val) << 1) - 1;
    } else {
        return val << 1;
    }
}

uint16_t golomb_encode(volatile int16_t samples[], int8_t optimal){
    uint8_t result[MAX_RESULT_LEN];
    uint16_t counter = 0;

    //store parameter
    for(int b = 0; b < 4; b++){
        result[counter++] = optimal & (1 << (3 - b)) ? 1 : 0;
    }

    //truncated parameter
    int16_t k = optimal;
    int16_t u = (1 << (k+1)) - (1 << optimal);


    for(int i = 0; i < SAMPLE_COUNT; i++){
        int16_t number = encode_signed(samples[i]);

        int16_t q = number >> optimal;
        int16_t r = number & ((1 << optimal) - 1);

        //unary code q
        for(int j = 0; j < q; j++){
            result[counter++] = 1;
        }
        //delimit unary with zero
        result[counter++] = 0;

        //truncated
        if(r < u){
            for(int b = 1; b <= k; b++){
                result[counter++] = r & (1 << (k - b)) ? 1 : 0;
            }
        } else {
            for(int b = 1; b <= k + 1; b++){
                result[counter++] = r & (1 << (k - b)) ? 1 : 0;
            }
        }

    }
    return(counter);
}