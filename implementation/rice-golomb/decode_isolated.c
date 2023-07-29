/*
 * Filename: decode_isolated.c
 * Author: Lukas Morong, xmoron01
 * Year: 2023
 * Description: 
 *     Rice golomb kodovanie, izolovana implementacia na ucely urcenia velkosti
 *     vysledneho asembleru, s optimalizaciou parametru
 */

#include <stdint.h>

#define SAMPLE_COUNT 624

int16_t decode_signed(int16_t val) {
    if (val & 1) {
        return -((val + 1) >> 1);
    } else {
        return val >> 1;
    }
}

void golomb_decode(volatile uint8_t bits[], int16_t len){
    int16_t result[SAMPLE_COUNT];
    int8_t divider = 0;
    int16_t counter = 0;
    int16_t bitCounter = 0;

    //parameter
    for(int b = 1; b <= 4; b++){
        divider |= bits[bitCounter++] ? (1 << (4 - b)) : 0;
    }

    //truncated parameter
    int16_t k = divider;
    int16_t u = (1 << (k+1)) - (1 << divider);

    uint16_t unaryCounter = 0;

    for(int b = 4; b < len; b++){
        if(bits[b]){
            unaryCounter++;
        } else {
            uint16_t q = unaryCounter << divider;
            unaryCounter = 0;

            //consume delimiting zero
            b++;

            uint16_t r = 0;
            for(int i = 1; i <= k; i++){
                r |= bits[b++] ? (1 << (k - i)) : 0;
            }
            
            if(r > u){
                r = (r << 1) | bits[b];
            } else {
                b--;
            }

            result[counter++] = decode_signed(q+r);
        }
    }
}