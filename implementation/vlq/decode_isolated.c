/*
 * Filename: decode_isolated.c
 * Author: Lukas Morong, xmoron01
 * Year: 2023
 * Description: 
 *     VLQ dekodovanie, izolovana implementacia na ucely urcenia velkosti
 *     vysledneho asembleru
 */

#include <stdint.h>
#include <stdbool.h>


#define SAMPLE_COUNT 624
#define MAX_LEN (SAMPLE_COUNT * 16)
#define VLQ_OCTET_BITS 8
#define VLQ_DATA_BITS_FIRST 6
#define VLQ_DATA_BITS_NEXT 7
#define VLQ_CONTINUE_MASK (1 << 7)
#define VLQ_SIGN_MASK (1 << 6)


void vlq_decode(volatile int8_t data[], int encoded_count){
    int16_t result[SAMPLE_COUNT];
    int count = 0;

    for(int16_t i = 0; i < encoded_count; i++){
        int8_t octet = data[i];
        bool negative = octet & VLQ_SIGN_MASK;
        int16_t number = octet & ((1 << VLQ_DATA_BITS_FIRST) - 1);

        while(octet & VLQ_CONTINUE_MASK){
            if(i >= encoded_count) break;

            octet = data[++i];
            number = (number << VLQ_DATA_BITS_NEXT) | (octet & ((1 << VLQ_DATA_BITS_NEXT) - 1));
        }

        if(negative){
            number *= -1;
        }

        result[count++] = number; 
    }
}