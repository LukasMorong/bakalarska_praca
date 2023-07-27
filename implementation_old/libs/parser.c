#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"
#include "jsmn/jsmn.h"

aoa_enclosure_t* parseInput(char *fileName){
    char *json_str = NULL;
    int json_size = 0;

    if((json_size = getJsonString(fileName, &json_str)) <= 0){
        printf("Not read well :/");
        if(json_str)
            free(json_str);
        return NULL;
    }

    printf("%s", json_str);

    jsmntok_t *tokens = NULL;

    int num_tokens = 0;

    if((num_tokens = parseJsonString(&json_str, &tokens, json_size)) <= 0){
        printf("Not parse well :/");
        if(json_str)
            free(json_str);

        if(tokens)
            free(tokens);
        return NULL;
    }

    //bool nextList = false;

    for (int i = 0; i < num_tokens; i++) {
        printf("Token %d: type=%d, start=%d, end=%d, size=%d\n", i, tokens[i].type, tokens[i].start, tokens[i].end, tokens[i].size);
        if(tokens[i].type == 4){

            for (int j = tokens[i].start; j < tokens[i].end; j++) {
                printf("%c", json_str[j]);
            }
            printf("\n");
        }
        // printf("\n");
    }

    free(json_str);
    free(tokens);

    return NULL;
}

int getJsonString(const char *fileName, char **json_str){
    FILE *fp;
    long json_size;

    fp = fopen(fileName, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    json_size = ftell(fp);
    rewind(fp);

    *json_str = (char *)malloc(json_size + 1);
    if (*json_str == NULL) {
        printf("Memory allocation error\n");
        return -1;
    }

    fread(*json_str, 1, json_size, fp);
    fclose(fp);

    (*json_str)[json_size] = '\0'; // null terminate the string

    return json_size;
}

int parseJsonString(char **json_str, jsmntok_t **tokens, int json_size){
    int r;
    jsmn_parser p;
    int num_tokens;

    jsmn_init(&p);

    // First, count the number of tokens needed to parse the JSON string
    num_tokens = jsmn_parse(&p, *json_str, json_size, NULL, 0);
    if (num_tokens < 0) {
        printf("JSON parsing error: %d\n", num_tokens);
        return -1;
    }

    // Allocate memory for the tokens
    *tokens = (jsmntok_t *)malloc(num_tokens * sizeof(jsmntok_t));
    if (tokens == NULL) {
        printf("Memory allocation error\n");
        return -1;
    }

    // Parse the JSON string into tokens
    jsmn_init(&p);
    r = jsmn_parse(&p, *json_str, json_size, *tokens, num_tokens);
    if (r < 0) {
        printf("JSON parsing error: %d\n", r);
        return -1;
    }

    return num_tokens;
}