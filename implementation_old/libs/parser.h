#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include "jsmn/jsmn.h"

typedef struct {
    int16_t* i;
    int16_t* q;
    int8_t* ant;
} aoa_enclosure_t;


aoa_enclosure_t* parseInput(char *fileName);

int getJsonString(const char *fileName, char **json_str);

int parseJsonString(char **json_str, jsmntok_t **tokens, int json_size);

#endif // PARSER_H
