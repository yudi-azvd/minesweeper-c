#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "defs.h"
#include <stdio.h>
#include <string.h>

#define FIELD_BUFFER 600

char visible_field_buffer[FIELD_BUFFER];
char hidden_field_buffer[FIELD_BUFFER];
char merged_buffer[FIELD_BUFFER];

void buffer_concat(int offset, char* buffer, char* data) {
    strcat(buffer, data);
}

int strcatcat(char* buffer, char* data) {
    int len = strlen(data);
    strcat(buffer, data);
    return len;
}

void merge_visible_hidden_buffers(char* buffer, char* visible, char* hidden) {
    int i = 0, vi = 0, line_start = 0, n;

    while (visible[i] != '\0') {
        if (visible[i] != '\n') {
            buffer[i] = visible[vi];
            i++;
            vi++;
        } else {
            n = 0;
            n += strcatcat(buffer, "@@");
            n += strcatcat(buffer, "\n");
            i += n;
        }
    }
    // int len = strlen(buffer);
    // buffer[len] = '\0';
    // printf("*** \n[%s]", buffer);
}

void print_field(char field[][FIELD_SIZE], char hidden[][FIELD_SIZE], int debug) {
    int i, j;
    char str[4];

    visible_field_buffer[0] = '\0';
    buffer_concat(0, visible_field_buffer, "\t -----------------\n");
    for (i = 0; i < FIELD_SIZE; i++) {
        buffer_concat(0, visible_field_buffer, "\t|");
        for (j = 0; j < FIELD_SIZE; j++) {
            sprintf(str, "%c ", field[i][j]);
            buffer_concat(0, visible_field_buffer, str);
        }
        buffer_concat(0, visible_field_buffer, "|\n");
    }
    buffer_concat(0, visible_field_buffer, "\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");

    hidden_field_buffer[0] = '\0';
    buffer_concat(0, hidden_field_buffer, "\t -----------------\n");
    for (i = 0; i < FIELD_SIZE; i++) {
        buffer_concat(0, hidden_field_buffer, "\t|");
        for (j = 0; j < FIELD_SIZE; j++) {
            sprintf(str, "%c ", hidden[i][j]);
            buffer_concat(0, hidden_field_buffer, str);
        }
        buffer_concat(0, hidden_field_buffer, "|\n");
    }
    buffer_concat(0, hidden_field_buffer, "\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");

    merge_visible_hidden_buffers(merged_buffer, visible_field_buffer, hidden_field_buffer);
    puts(merged_buffer);
}

void debug_print_field(char hidden[][FIELD_SIZE], char visible[][FIELD_SIZE], int debug) {
    int i, j;
    char str[4];

    visible_field_buffer[0] = '\0';

    buffer_concat(0, visible_field_buffer, "\t -----------------");
    buffer_concat(0, visible_field_buffer, "  ------------------\n");

    for (i = 0; i < FIELD_SIZE; i++) {
        buffer_concat(0, visible_field_buffer, "\t｜");
        for (j = 0; j < FIELD_SIZE; j++) {
            sprintf(str, "%c ", visible[i][j]);
            buffer_concat(0, visible_field_buffer, str);
        }
        buffer_concat(0, visible_field_buffer, "| |");
        for (j = 0; j < FIELD_SIZE; j++) {
            sprintf(str, "%c ", hidden[i][j]);
            buffer_concat(0, visible_field_buffer, str);
        }
        buffer_concat(0, visible_field_buffer, "|\n");
    }
    buffer_concat(0, visible_field_buffer, "\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
    buffer_concat(0, visible_field_buffer, "  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
    puts(visible_field_buffer);
}

#endif // UI_H_INCLUDED