#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "defs.h"
#include <stdio.h>
#include <string.h>

#define FIELD_BUFFER 600

char visible_field_buffer[FIELD_BUFFER];
char hidden_field_buffer[FIELD_BUFFER];
char merged_buffer[FIELD_BUFFER*3];

void buffer_concat(int offset, char* buffer, char* data) {
    strcat(buffer, data);
}

int strcatcat_n(char* buffer, char* data) {
    int i, len = strlen(data);
    int buffer_len = strlen(buffer);
    for (i = 0; data[i] != '\n' || data[i] != '\0'; i++) {
        buffer[buffer_len + i] = data[i];
    }

    buffer[buffer_len + i++] = '\n';
    return i;
}

void merge_visible_hidden_buffers(char* buffer, char* visible, char* hidden) {
    int i_buff = 0, i_visible = 0, line_start = 0, n;

    buffer[0] = '\0';
    while (visible[i_visible] != '\0' && i_buff < FIELD_BUFFER) {
        if (visible[i_visible] != '\n') {
            buffer[i_buff] = visible[i_visible];
            i_buff++;
            i_visible++;
        } else {
            n = 0;
            // n += strcatcat_n(buffer, "   ");
            // n += strcatcat_n(buffer, hidden + i_visible);
            n += strcatcat_n(buffer, "#\n");
            i_buff += n;
            i_visible++;
        }
    }
    buffer[i_buff] = '\0';
}

void render_field(char field[][FIELD_SIZE], char hidden[][FIELD_SIZE], int debug) {
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

void debug_render_field(char hidden[][FIELD_SIZE], char visible[][FIELD_SIZE], int debug) {
    int i, j;
    char str[4];

    visible_field_buffer[0] = '\0';

    buffer_concat(0, visible_field_buffer, "\t -----------------");
    buffer_concat(0, visible_field_buffer, "  ------------------\n");

    for (i = 0; i < FIELD_SIZE; i++) {
        buffer_concat(0, visible_field_buffer, "\t|");
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