#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>

#define SAMPLE_COUNT 624
#define MAX_DIGITS 10  /* Maximum digits for 32-bit integer plus null byte */
#define DICT_1_SIZE 32
#define DICT_2_SIZE 16

#define OUTPUT

volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

void print_uart0(const char *s);
void print_uart0_int(int value);

void predictive_compress(volatile int16_t samples[], volatile int8_t ant[]);


int c_entry(){
    // original
    volatile int16_t i_samples[SAMPLE_COUNT] = {23, -95, -204, -289, -320, -300, -219, -111, 29, 145, 235, 291, 296, 262, 185, 91, -32, -140, -227, -285, -291, -256, -176, -79, 50, 161, 247, 289, 274, 218, 127, 42, -49, -123, -193, -260, -292, -284, -220, -120, 1, 134, 227, 282, 286, 244, 140, 16, -107, -193, -199, -131, -43, 33, 80, 94, 94, 87, 73, 44, 10, -22, -46, -57, -72, -114, -172, -238, -266, -242, -153, -41, 75, 184, 246, 267, 240, 174, 66, -45, -150, -247, -297, -309, -276, -207, -96, 17, 128, 224, 271, 274, 224, 140, 14, -101, -186, -217, -177, -94, 10, 79, 119, 125, 122, 114, 97, 62, 2, -56, -97, -107, -103, -109, -132, -152, -135, -69, 29, 143, 220, 269, 275, 242, 162, 63, -42, -150, -228, -287, -305, -278, -188, -74, 47, 163, 233, 268, 259, 214, 127, 24, -90, -211, -282, -288, -216, -100, 28, 97, 115, 98, 74, 49, 17, -14, -48, -69, -73, -63, -55, -60, -85, -103, -84, -13, 94, 220, 299, 325, 296, 222, 109, 1, -103, -201, -263, -285, -249, -170, -51, 54, 145, 225, 268, 278, 238, 158, 51, -80, -190, -281, -310, -280, -186, -83, 11, 82, 112, 113, 88, 43, -23, -80, -119, -127, -103, -63, -38, -32, -33, -19, 22, 97, 173, 245, 282, 280, 225, 133, 12, -126, -220, -271, -276, -249, -191, -117, -21, 99, 193, 256, 280, 257, 193, 104, -6, -133, -228, -286, -288, -240, -145, -50, 30, 83, 96, 85, 55, 16, -36, -79, -106, -111, -94, -68, -40, -16, 14, 64, 124, 198, 250, 278, 269, 221, 137, 6, -124, -251, -318, -327, -276, -190, -88, 28, 122, 212, 265, 285, 259, 197, 102, -25, -138, -242, -296, -301, -246, -158, -57, 34, 73, 72, 45, 20, 2, -11, -31, -65, -94, -104, -85, -50, -10, 23, 61, 128, 204, 277, 317, 295, 204, 86, -36, -148, -214, -251, -267, -260, -224, -156, -57, 73, 179, 256, 288, 270, 208, 100, -12, -136, -226, -285, -302, -270, -199, -96, -11, 55, 75, 63, 28, -7, -35, -53, -62, -63, -55, -37, -8, 20, 50, 93, 144, 213, 270, 305, 300, 245, 146, 7, -114, -222, -280, -305, -288, -233, -142, -11, 105, 201, 269, 291, 271, 216, 129, 5, -109, -208, -281, -300, -273, -208, -118, -8, 74, 119, 114, 73, 9, -41, -69, -74, -67, -57, -45, -27, 6, 45, 87, 134, 182, 234, 285, 301, 274, 191, 77, -64, -175, -254, -292, -286, -248, -174, -83, 40, 150, 239, 291, 286, 232, 128, 17, -104, -191, -249, -280, -268, -215, -110, -4, 87, 115, 96, 48, 10, -13, -31, -49, -68, -84, -83, -57, -14, 33, 72, 89, 107, 150, 211, 263, 260, 197, 73, -48, -159, -257, -311, -319, -275, -188, -61, 54, 156, 240, 278, 274, 231, 156, 47, -61, -166, -256, -297, -293, -235, -149, -30, 70, 138, 158, 124, 62, -15, -75, -124, -148, -144, -102, -37, 27, 72, 74, 54, 48, 81, 164, 242, 281, 245, 152, 13, -106, -201, -271, -294, -276, -211, -117, -3, 127, 225, 296, 310, 276, 189, 87, -25, -142, -220, -260, -250, -201, -112, -13, 92, 188, 222, 181, 86, -19, -103, -129, -123, -107, -91, -66, -33, 11, 57, 81, 83, 79, 93, 135, 193, 208, 147, 32, -101, -225, -287, -307, -286, -231, -128, -10, 113, 224, 283, 297, 259, 187, 74, -40, -148, -240, -279, -275, -227, -154, -44, 74, 188, 272, 270, 195, 64, -41, -100, -112, -100, -78, -58, -31, 9, 45, 76, 92, 89, 77, 73, 82, 87, 61, -4, -110, -205, -283, -310, -294, -228, -138, -30, 95, 189, 253, 261, 222, 133, 35, -66, -170, -238, -272, -257, -197, -98, 3, 105, 209, 274};
    volatile int16_t q_samples[SAMPLE_COUNT] = {303, 292, 232, 116, -5, -119, -217, -270, -283, -255, -197, -102, -2, 104, 213, 279, 301, 263, 182, 58, -61, -166, -248, -284, -277, -234, -158, -43, 71, 179, 271, 309, 300, 250, 170, 55, -58, -163, -256, -298, -295, -245, -165, -50, 57, 156, 241, 281, 279, 220, 134, 29, -42, -76, -72, -46, -11, 29, 63, 99, 125, 135, 119, 78, 31, -4, -20, -50, -108, -189, -275, -314, -301, -231, -133, -15, 123, 228, 303, 321, 291, 211, 106, -12, -141, -232, -288, -295, -259, -175, -73, 45, 175, 267, 317, 305, 245, 145, 54, -18, -65, -75, -56, -21, 20, 59, 81, 86, 72, 49, 17, -11, -41, -82, -127, -180, -240, -284, -303, -278, -206, -81, 44, 154, 239, 273, 275, 245, 190, 94, -12, -126, -234, -290, -296, -244, -159, -42, 66, 163, 242, 273, 262, 204, 126, 30, -43, -89, -100, -72, -23, 31, 64, 79, 80, 75, 60, 36, 5, -29, -58, -93, -152, -219, -287, -311, -289, -215, -120, -14, 108, 204, 273, 290, 259, 178, 85, -15, -123, -208, -274, -286, -248, -155, -49, 57, 159, 230, 275, 286, 247, 158, 55, -38, -95, -100, -68, -9, 44, 89, 109, 109, 93, 74, 52, 21, -15, -55, -87, -119, -169, -227, -274, -285, -234, -123, -6, 102, 194, 243, 260, 236, 179, 93, -21, -118, -205, -255, -270, -244, -175, -76, 50, 152, 242, 292, 313, 289, 225, 127, 5, -80, -122, -111, -72, -20, 16, 40, 55, 59, 56, 49, 37, 16, -14, -50, -96, -141, -190, -237, -252, -210, -122, -5, 126, 214, 267, 282, 260, 194, 102, -11, -146, -243, -301, -310, -267, -181, -86, 12, 114, 192, 248, 276, 257, 177, 60, -77, -204, -251, -221, -118, -11, 74, 121, 127, 111, 84, 49, 3, -35, -58, -61, -55, -58, -85, -131, -173, -174, -123, -13, 102, 214, 276, 295, 267, 205, 120, 5, -100, -206, -273, -301, -279, -216, -123, -4, 95, 174, 233, 258, 252, 211, 131, 1, -123, -218, -252, -204, -97, 2, 69, 104, 111, 113, 109, 89, 43, -9, -55, -82, -88, -93, -114, -143, -160, -132, -54, 70, 175, 250, 284, 269, 212, 129, 30, -82, -171, -241, -288, -291, -248, -144, -23, 113, 207, 265, 287, 270, 223, 136, 32, -99, -206, -272, -270, -193, -75, 45, 109, 126, 114, 91, 57, 18, -26, -66, -81, -71, -54, -47, -64, -93, -105, -67, 24, 140, 258, 316, 316, 270, 187, 60, -65, -176, -262, -294, -282, -237, -163, -49, 68, 182, 274, 304, 281, 217, 129, 12, -100, -207, -295, -323, -275, -177, -55, 59, 115, 128, 108, 76, 33, -28, -82, -125, -135, -121, -93, -70, -52, -31, 1, 64, 139, 218, 281, 294, 260, 171, 66, -58, -159, -240, -295, -298, -251, -151, -41, 82, 177, 250, 295, 288, 237, 146, 52, -48, -160, -248, -304, -299, -236, -120, -13, 68, 108, 102, 66, 25, -15, -54, -80, -94, -93, -73, -35, 1, 28, 50, 74, 117, 187, 251, 294, 286, 232, 129, 17, -97, -209, -276, -298, -264, -184, -58, 64, 172, 259, 302, 310, 275, 204, 81, -48, -172, -271, -303, -278, -196, -101, -6, 49, 74, 74, 56, 32, 3, -20, -44, -64, -82, -91, -81, -56, -12, 35, 87, 149, 207, 263, 287, 270, 197, 93, -26, -148, -225, -269, -271, -246, -187, -109, -11, 106, 196, 258, 272, 245, 168, 65, -54, -182, -264, -304, -286, -230, -141, -56, 14, 63, 74, 62, 29, -8, -56, -93, -114, -107, -75, -32, 9, 34, 59, 92, 142, 214, 273, 306, 295, 232, 111, -22, -148, -251, -302, -312, -276, -207, -94, 22, 134, 236, 291, 302, 258, 174, 61, -75, -179, -260, -286, -267, -201, -112};
    volatile int8_t ant[SAMPLE_COUNT] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -2, -2, -2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, 2, 2, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    #ifdef OUTPUT

    // for(int i = 0; i < SAMPLE_COUNT; i++){
    //     print_uart0_int(i_samples[i]);
    // }

    // print_uart0("\n");

    // for(int i = 0; i < SAMPLE_COUNT; i++){
    //     print_uart0_int(q_samples[i]);
    // }

    // print_uart0("\n");
    // print_uart0("\n");

    #endif //OUTPUT

    predictive_compress(i_samples, ant);
    predictive_compress(q_samples, ant);

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

    #ifdef OUTPUT

    // for(int i = 0; i < SAMPLE_COUNT; i++){
    //     print_uart0_int(result[i]);
    // }

    // print_uart0("\n");
    // print_uart0("\n");

    #endif //OUTPUT
}

