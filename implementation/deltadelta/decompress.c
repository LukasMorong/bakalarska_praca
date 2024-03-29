/*
 * Filename: decompress.c
 * Author: Lukas Morong, xmoron01
 * Year: 2023
 * Description: 
 *     DeltaDelta kodovanie dekompresia
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>


#define SAMPLE_COUNT 624
#define MAX_DIGITS 10  /* Maximum digits for 32-bit integer plus null byte */

#define OUTPUT

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

void print_uart0(const char *s);
void print_uart0_int(int value);

void deltadelta_compress(volatile int16_t i_samples[], volatile int16_t q_samples[]);
void deltadelta_decompress(volatile int16_t i_samples[], volatile int16_t q_samples[]);


int c_entry(){
    //original
    volatile int16_t i_result[SAMPLE_COUNT] = {23, -141, 9, 24, 54, 51, 61, 27, 32, -24, -26, -34, -51, -39, -43, -17, -29, 15, 21, 29, 52, 41, 45, 17, 32, -18, -25, -44, -57, -41, -35, 6, -6, 17, 4, 3, 35, 40, 56, 36, 21, 12, -40, -38, -51, -46, -62, -20, 1, 37, 80, 74, 20, -12, -29, -33, -14, -7, -7, -15, -5, 2, 8, 13, -4, -27, -16, -8, 38, 52, 65, 23, 4, -7, -47, -41, -48, -39, -42, -3, 6, 8, 47, 38, 45, 36, 42, 2, -2, -15, -49, -44, -53, -34, -42, 11, 30, 54, 71, 43, 21, -35, -29, -34, -9, -5, -9, -18, -25, 2, 17, 31, 14, -10, -17, 3, 37, 49, 32, 16, -37, -28, -43, -39, -47, -19, -6, -3, 30, 19, 41, 45, 63, 24, 7, -5, -46, -35, -44, -36, -42, -16, -11, -7, 50, 65, 78, 44, 12, -59, -51, -35, -7, -1, -7, 1, -3, 13, 17, 14, -2, -13, -20, 7, 37, 52, 36, 19, -47, -53, -55, -45, -39, 5, 4, 6, 36, 40, 58, 43, 40, -14, -14, -11, -37, -33, -50, -40, -27, -24, 21, 19, 62, 59, 64, 9, -9, -23, -41, -29, -26, -20, -21, 9, 18, 31, 32, 16, -15, -19, -7, 15, 27, 34, 1, -4, -35, -39, -53, -37, -29, -17, 44, 43, 46, 32, 31, 16, 22, 24, -26, -31, -39, -47, -41, -25, -21, -17, 32, 37, 56, 50, 47, 0, -15, -27, -40, -24, -19, -9, -13, 9, 16, 22, 22, 9, 2, -4, 6, 20, 10, 14, -22, -24, -37, -39, -36, -47, 1, 3, 60, 58, 60, 35, 16, 14, -22, -4, -37, -33, -46, -36, -33, -32, 14, 9, 50, 49, 60, 33, 13, -10, -52, -40, -26, 2, 7, 5, -7, -14, 5, 19, 29, 16, 5, -7, 5, 29, 9, -3, -33, -62, -69, -27, -4, 10, 46, 29, 21, 23, 29, 32, 31, 31, -24, -29, -45, -50, -44, -46, -4, -12, 34, 31, 42, 49, 39, 32, -18, -19, -46, -32, -23, 0, 7, 10, 9, 8, 9, 10, 11, -1, 2, 13, 8, 18, -12, -22, -40, -50, -44, -40, 18, 13, 50, 33, 42, 38, 36, 40, -15, -20, -28, -46, -42, -35, -32, -37, 10, 15, 26, 54, 46, 38, 25, 20, -28, -37, -50, -36, -23, 14, 22, 23, 12, 3, 2, 6, 15, 6, 3, 5, 1, 4, -1, -35, -43, -56, -31, -27, 30, 32, 41, 44, 32, 36, 17, 32, -13, -21, -37, -57, -49, -50, -7, -10, 34, 29, 27, 43, 41, 52, 1, -15, -63, -47, -29, 10, 15, 5, 0, -1, 3, 17, 25, 17, 4, -8, -22, 1, 25, 18, -9, -55, -60, -61, 3, 10, 13, 44, 46, 52, 43, 40, -12, -13, -18, -46, -42, -39, -32, -34, 1, 3, 15, 49, 45, 54, 28, 33, -19, -32, -48, -54, -28, -15, 17, 11, 25, 28, 38, 23, -1, -19, -43, -22, 14, 39, 50, -5, -39, -75, -57, -46, 20, 24, 25, 47, 41, 47, 29, 20, 16, -32, -27, -57, -48, -53, -15, -10, -5, 39, 38, 50, 39, 40, 10, 6, -9, -62, -75, -54, -10, 21, 58, 32, 10, 0, 9, 8, 11, 2, -22, -22, -6, 18, 28, 16, -43, -76, -54, -18, 9, 62, 42, 41, 34, 48, 15, 5, -12, -52, -45, -52, -34, -41, -1, 6, 16, 53, 43, 44, 25, 37, 8, -4, -30, -86, -73, -56, 26, 46, 47, 24, 10, -2, 7, 13, -4, -5, -15, -19, -9, 8, 13, -4, -31, -39, -41, 11, 17, 51, 43, 50, 24, 18, 17, -31, -30, -56, -47, -50, -9, -3, -3, 36, 34, 49, 45, 39, 2, 1, 2, -39};
    volatile int16_t q_result[SAMPLE_COUNT] = {303, -314, -49, -56, -5, 7, 16, 45, 40, 41, 30, 37, 5, 6, 3, -43, -44, -60, -43, -43, 5, 14, 23, 46, 43, 36, 33, 39, -1, -6, -16, -54, -47, -41, -30, -35, 2, 8, 12, 51, 45, 47, 30, 35, -8, -8, -14, -45, -42, -57, -27, -19, 34, 37, 38, 22, 9, 5, -6, 2, -10, -16, -26, -25, -6, 12, 19, -14, -28, -23, -5, 47, 52, 57, 28, 20, 20, -33, -30, -57, -48, -50, -25, -13, -11, 38, 35, 49, 43, 48, 18, 16, 12, -38, -42, -62, -48, -40, 9, 19, 25, 37, 29, 16, 6, -2, -17, -17, -19, -9, -9, 4, -2, -11, -4, -8, -7, 16, 25, 44, 47, 53, 0, -15, -25, -51, -32, -32, -25, -41, -10, -8, 6, 52, 50, 58, 33, 32, -9, -11, -18, -48, -42, -47, -20, -18, 23, 27, 35, 39, 21, 5, -21, -18, -14, -6, -10, -9, -7, -3, 5, -6, -24, -8, -1, 44, 46, 52, 21, 11, 16, -26, -27, -52, -48, -50, -12, -7, -8, 23, 19, 54, 50, 55, 13, 0, -4, -31, -26, -34, -50, -50, -14, 10, 36, 52, 37, 27, -6, -8, -25, -20, -16, -3, -3, -9, -5, -4, 8, 0, -18, -8, 11, 36, 62, 60, 6, -9, -16, -43, -32, -41, -33, -29, -28, 17, 10, 37, 35, 41, 43, 30, 27, -24, -12, -40, -29, -45, -40, -34, -24, 37, 43, 53, 28, 13, -16, -12, -9, -11, -7, -4, -5, -9, -9, -6, -10, 1, -4, 2, 32, 57, 46, 29, 14, -43, -35, -38, -37, -44, -26, -21, -22, 38, 39, 49, 52, 43, 9, 3, 4, -24, -22, -28, -47, -61, -37, -20, 10, 80, 77, 73, 4, -22, -38, -41, -22, -11, -8, -11, 8, 15, 20, 9, -9, -24, -19, 4, 41, 52, 59, 5, -3, -50, -43, -47, -34, -23, -30, 10, -1, 39, 39, 50, 41, 30, 26, -20, -20, -20, -34, -31, -35, -39, -50, 6, 29, 61, 82, 59, -8, -32, -32, -28, -5, -6, -16, -26, -6, 6, 19, 21, 1, -16, -8, 12, 45, 50, 46, -19, -30, -41, -49, -42, -26, -16, -13, 23, 19, 23, 44, 46, 61, 17, 15, -42, -36, -36, -39, -30, -40, -17, -27, 24, 41, 68, 75, 41, 2, -56, -47, -29, -11, -11, -5, -5, 4, 25, 25, 7, -10, -24, -12, 17, 50, 53, 25, 2, -60, -58, -46, -37, -44, 2, 14, 25, 54, 44, 33, 29, 40, 3, -3, -22, -62, -53, -41, -24, -29, 5, 5, 19, 60, 76, 50, 24, -8, -58, -43, -33, -12, -11, -18, 7, 11, 33, 24, 14, -5, -5, 3, 11, 31, 12, 4, -16, -50, -47, -55, -16, -19, 23, 20, 26, 52, 50, 53, 10, 13, -28, -22, -28, -52, -44, -40, -3, -6, -12, 24, 32, 61, 58, 53, -9, -26, -41, -46, -30, -5, 1, 1, 13, 12, 15, 19, 18, -2, -9, -5, 2, 19, 27, -6, -21, -51, -46, -49, -9, -2, 2, 45, 45, 56, 46, 46, -4, -14, -21, -44, -35, -43, -36, -52, -6, 5, 25, 67, 57, 57, 13, 0, -40, -30, -25, -18, -6, -5, 6, -1, 4, 2, 9, 19, 15, 19, 3, 5, 10, -4, -2, -32, -41, -56, -31, -15, -3, 45, 33, 42, 27, 34, 19, 20, 19, -27, -28, -48, -41, -50, -26, -16, -9, 46, 42, 58, 38, 33, -4, -15, -21, -38, -23, -21, -4, -11, 11, 16, 28, 25, 11, -2, -16, 0, 8, 17, 22, -13, -26, -44, -52, -58, -12, 7, 23, 52, 41, 46, 33, 44, 3, -4, -10, -47, -44, -55, -40, -29, -23, 32, 23, 55, 45, 47, 23};

    #ifdef OUTPUT

    // for(int i = 0; i < SAMPLE_COUNT; i++){
    //     print_uart0_int(i_result[i]);
    // }

    // print_uart0("\n");

    // for(int i = 0; i < SAMPLE_COUNT; i++){
    //     print_uart0_int(q_result[i]);
    // }

    // print_uart0("\n");
    // print_uart0("\n");

    #endif //OUTPUT

    deltadelta_decompress(i_result, q_result);

    return 0;
}

void *memcpy(void *dest, const void *src, size_t n){
    for (size_t i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

#ifdef OUTPUT

void print_uart0_int(int value) {
    char buffer[MAX_DIGITS];
    int i = MAX_DIGITS - 1;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (value == 0) {
        *UART0DR = '0';
        *UART0DR = ',';
        *UART0DR = ' ';
        return;
    }

    /* Handle negative numbers */
    if (value < 0) {
        *UART0DR = '-';
        value = -value;
    }

    /* Fill buffer from end */
    while (value > 0 && i >= 0) {
        buffer[i--] = (value % 10) + '0';
        value /= 10;
    }

    /* Output the number */
    while (++i < MAX_DIGITS)
        *UART0DR = buffer[i];

    *UART0DR = ',';
    *UART0DR = ' ';
    
}

void print_uart0(const char *s) {
    while(*s != '\0') { /* Loop until end of string */
        *UART0DR = (unsigned int)(*s); /* Transmit char */
        s++; /* Next char */
    }
}

#endif //OUTPUT

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

    #ifdef OUTPUT

    for(int i = 0; i < SAMPLE_COUNT; i++){
        print_uart0_int(i_result[i]);
    }

    print_uart0("\n");

    for(int i = 0; i < SAMPLE_COUNT; i++){
        print_uart0_int(q_result[i]);
    }

    print_uart0("\n");
    print_uart0("\n");

    #endif //OUTPUT
}

void deltadelta_decompress(volatile int16_t i_samples[], volatile int16_t q_samples[]){
    int16_t previousI = 0;
    int16_t previousQ = 0;
    int16_t previous_resultI = 0;
    int16_t previous_resultQ = 0;

    int16_t i_result[SAMPLE_COUNT];
    int16_t q_result[SAMPLE_COUNT];

    for(int i = 0; i < SAMPLE_COUNT; i++){
        previousI += i_samples[i];
        previous_resultI += previousI;
        i_result[i] = previous_resultI;

        previousQ += q_samples[i];
        previous_resultQ += previousQ;
        q_result[i] = previous_resultQ;
    }

    #ifdef OUTPUT

    for(int i = 0; i < SAMPLE_COUNT; i++){
        print_uart0_int(i_result[i]);
    }

    print_uart0("\n");

    for(int i = 0; i < SAMPLE_COUNT; i++){
        print_uart0_int(q_result[i]);
    }

    print_uart0("\n");
    print_uart0("\n");

    #endif //OUTPUT
}