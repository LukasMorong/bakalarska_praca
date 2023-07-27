#include "delta_encoding.h"

int delta_encode(int16_t* data, int size) {
    int previous = 0;
    int current;

    for(int i = 0; i < size; i++){
        current = data[i] - previous;
        previous = data[i];
        data[i] = current;
    }

    return 0;
}

int delta_decode(int16_t* data, int size) {
    int previous = 0;

    for(int i = 0; i < size; i++){
        previous += data[i];
        data[i] = previous;
    }

    return 0;
}

#include <sys/stat.h>

// _open
int _open(const char* name, int flags, int mode) {
    return -1;
}

// _isatty
int _isatty(int file) {
    return 1;
}

// _kill
int _kill(int pid, int sig) {
    return -1;
}

// _getpid
int _getpid() {
    return 1;
}