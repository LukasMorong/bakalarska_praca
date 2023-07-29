/*
 * Filename: compress_isolated.c
 * Author: Lukas Morong, xmoron01
 * Year: 2023
 * Description: 
 *     DeltaDelta kodovanie kompresia, izolovana implementacia na ucely urcenia velkosti
 *     vysledneho asembleru
 */

#include <stdint.h>

#define SAMPLE_COUNT 624

void deltadelta_compress(volatile int16_t i_samples[], volatile int16_t q_samples[]){
    int16_t previousI = 0;
    int16_t previousQ = 0;
    int16_t currentI;
    int16_t currentQ;
    int16_t resultPreviousI = 0;
    int16_t resultPreviousQ = 0;

    int16_t i_result[SAMPLE_COUNT];
    int16_t q_result[SAMPLE_COUNT];

    for(int i = 0; i < SAMPLE_COUNT; i++){
        currentI = i_samples[i] - previousI;
        previousI = i_samples[i];
        i_result[i] = currentI - resultPreviousI;
        resultPreviousI = currentI;

        currentQ = q_samples[i] - previousQ;
        previousQ = q_samples[i];
        q_result[i] = currentQ - resultPreviousQ;
        resultPreviousQ = currentQ;
    }
}