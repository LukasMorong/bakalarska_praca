#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "libs/typedefs.h"
#include "libs/data_transformation/delta_encoding.h"

#define SAMPLE_COUNT 624

// fun declarations
void delta_none(IQData* data);


IQData* parse_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return NULL;
    }

    IQData *result = (IQData*)malloc(sizeof(IQData));
    result->samples = (IQ*)malloc(SAMPLE_COUNT * sizeof(IQ));
    result->ant = (int8_t *)malloc(SAMPLE_COUNT * sizeof(int8_t));
    
    int i_samples[SAMPLE_COUNT], q_samples[SAMPLE_COUNT];
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        fscanf(file, "%d, ", &i_samples[i]);
    }
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        fscanf(file, "%d, ", &q_samples[i]);
    }
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        result->samples[i].i = (int16_t)i_samples[i];
        result->samples[i].q = (int16_t)q_samples[i];
    }
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        int ant_sample;
        fscanf(file, "%d, ", &ant_sample);
        result->ant[i] = (int8_t)ant_sample;
    }

    fclose(file);
    return result;
}

int main() {
    char *filename = "data/data.txt";
    IQData *data = parse_file(filename);

    // Check data
    if (data != NULL) {
        // printf("Pairs:\n");
        // for (int i = 0; i < SAMPLE_COUNT; i++) {
        //     printf("(%d, %d)", data->samples[i].i, data->samples[i].q);
        // }
        // printf("\nData:\n");
        // for (int i = 0; i < SAMPLE_COUNT; i++) {
        //     printf("%d", data->ant[i]);
        // }

        delta_none(data);

        free(data->samples);
        free(data->ant);
        free(data);

    }

    return 0;
}

void delta_none(IQData* data){
  int16_t* i_samples = (int16_t *)malloc(SAMPLE_COUNT * sizeof(int16_t));
  int16_t* q_samples = (int16_t *)malloc(SAMPLE_COUNT * sizeof(int16_t));

  for(int i = 0; i < SAMPLE_COUNT; i++){
    i_samples[i] = data->samples[i].i;
    q_samples[i] = data->samples[i].q;
  }

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    printf("%d\n", q_samples[i]);
  }

  delta_encode(i_samples, SAMPLE_COUNT);
  delta_encode(q_samples, SAMPLE_COUNT);

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    printf("%d\n", q_samples[i]);
  }

  delta_decode(i_samples, SAMPLE_COUNT);
  delta_decode(q_samples, SAMPLE_COUNT);


  for (int i = 0; i < SAMPLE_COUNT; i++) {
    printf("%d\n", q_samples[i]);
  }


  free(i_samples);
  free(q_samples);
}


#include <sys/stat.h>

// _sbrk: Increase program data space.
void* _sbrk(int incr) {
    extern char _end; /* Defined by the linker */
    static char* heap_end;
    char* prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;

    heap_end += incr;
    return (void*) prev_heap_end;
}

// _close: We don't have any filesystem, so close can't really fail
int _close(int file) {
    return -1;
}

// _write: Transfer data from memory to a peripheral
int _write(int file, char* ptr, int len) {
    int todo;

    for (todo = 0; todo < len; todo++) {
       /* Write char */
    }

    return len;
}

// _fstat: Status of an open file
int _fstat(int file, struct stat* st) {
    st->st_mode = S_IFCHR;
    return 0;
}

// _lseek: Set position in a file
int _lseek(int file, int ptr, int dir) {
    return 0;
}

// _read: Read from a file
int _read(int file, char* ptr, int len) {
    return 0;
}

// _exit: Exit a program without cleaning up files
void _exit(int status) {
    while (1) {
        /* Infinite loop */
    }
}