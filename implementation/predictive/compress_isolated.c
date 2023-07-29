/*
 * Filename: compress_isolated.c
 * Author: Lukas Morong, xmoron01
 * Year: 2023
 * Description: 
 *     Adaptivne Slovnikove Prediktivne kodovanie kompresia, 
 *     izolovana implementacia na ucely urcenia velkosti
 *     vysledneho asembleru
 */

#include <stdint.h>
#include <stdlib.h>

#define SAMPLE_COUNT 624
#define DICT_1_SIZE 32
#define DICT_2_SIZE 16

void predictive_compress(volatile int16_t samples[], volatile int8_t ant[]){
    volatile int16_t dict_1[DICT_1_SIZE];
    volatile int16_t dict_2[DICT_2_SIZE];

    for(int i = 0; i < DICT_1_SIZE; i++){
        dict_1[i] = 0;
    }
    for(int i = 0; i < DICT_2_SIZE; i++){
        dict_2[i] = 0;
    }
    volatile int16_t result[SAMPLE_COUNT];

    uint8_t count1 = 0;
    uint8_t count2 = 0;

    for(int i = 0; i < SAMPLE_COUNT; i++){
        if(abs(ant[i]) == 1) {
            count2 = 0;

            result[i] = samples[i] - dict_1[count1 % DICT_1_SIZE];
            dict_1[count1 % DICT_1_SIZE] = samples[i];

            count1++;

        } else {
            count1 = 0;

            result[i] = samples[i] - dict_2[count2 % DICT_2_SIZE];
            dict_2[count2 % DICT_2_SIZE] = samples[i];

            count2++;
        }
    }
}