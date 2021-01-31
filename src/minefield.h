#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define FIELD_SIZE 8
#define MINES_TO_START 6
#define MINE_SYMBOL '*'
#define EMPTY_POSITION ' '
#define INITIAL_SYMBOL_FIELD_VISIBLE '#'


char minefield_visible[FIELD_SIZE][FIELD_SIZE];
char minefield_hidden[FIELD_SIZE][FIELD_SIZE];

void print_field(char field[][FIELD_SIZE]);

int count_mines_for_this_position(char field[][FIELD_SIZE], int i, int j) {
  int dx, dy, mines_count = 0;

  for(dy = -1; dy <= 1; dy++) {
    for(dx = -1; dx <= 1; dx++) {
      if(0 <= i+dy && i+dy < FIELD_SIZE && 0 <= j+dx && j+dx < FIELD_SIZE) {
        if(field[i+dy][j+dx] == MINE_SYMBOL) {
          mines_count++;
        }
      }
    }
  }

  return mines_count;
}

void write_mine_count_for_each_position(char field_hidden[][FIELD_SIZE]) {
  int i, j, mines_count;
  for(i = 0; i < FIELD_SIZE; i++) {
    for(j = 0; j < FIELD_SIZE; j++) {
      if(field_hidden[i][j] != MINE_SYMBOL) {
        mines_count = count_mines_for_this_position(field_hidden, i, j);
        field_hidden[i][j] = '0' + mines_count;
      }
    }
  }
}

/**
 * se o jogo resetar sem terminar, srand(time(NULL)) vai dar ruim?
 */
void place_mines(char field_hidden[][FIELD_SIZE], int mines_to_place, int seed) {
  int i, j ;
  // provavelmente eu deveria colocar essa parte em uma função
  for(i = 0; i < FIELD_SIZE; i++) {
    for( j = 0; j < FIELD_SIZE; j++) {
      field_hidden[i][j] = EMPTY_POSITION;
    }
  }

  if(seed == 0) {
    srand(time(NULL));
  }
  else {
    srand(seed);
  }

  int x, y;
  while(mines_to_place > 0) {
    x = rand() % FIELD_SIZE;
    y = rand() % FIELD_SIZE;

    if(field_hidden[y][x] != MINE_SYMBOL) {
      field_hidden[y][x] = MINE_SYMBOL;
      mines_to_place--;
    }
  }
}

void init_field_hidden(char field[][FIELD_SIZE]) {
  int mines_to_place = 6, seed = 0;
  place_mines(field, mines_to_place, seed);
  write_mine_count_for_each_position(field);
}

void init_field_visible(char field[][FIELD_SIZE]) {
  int i, j;

  for(i = 0; i < FIELD_SIZE; i++) {
    for( j = 0; j < FIELD_SIZE; j++) {
      field[i][j] = INITIAL_SYMBOL_FIELD_VISIBLE;
    }
  }
}


void init_fields(char hidden[][FIELD_SIZE], char visible[][FIELD_SIZE]) {
  init_field_hidden(hidden);
  init_field_visible(visible);
}

void print_field(char field[][FIELD_SIZE]) {
  int i, j;

  printf("\t -----------------\n");
  for(i = 0; i < FIELD_SIZE; i++) {
    printf("\t｜");
    for(j = 0; j < FIELD_SIZE; j++) {
      printf("%c ", field[i][j]);
    }
    printf("|\n");
  }
  printf("\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
}

void debug_print_field(char hidden[][FIELD_SIZE], char visible[][FIELD_SIZE]) {
    int i, j;

  printf("\t -----------------");
  printf("  ------------------\n");
  for(i = 0; i < FIELD_SIZE; i++) {
    printf("\t｜");
    for(j = 0; j < FIELD_SIZE; j++) {
      printf("%c ", visible[i][j]);
    }
    printf("| |");
    for(j = 0; j < FIELD_SIZE; j++) {
      printf("%c ", hidden[i][j]);
    }
    printf("|\n");
  }
  printf("\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
  printf("  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
}

#endif // MINEFIED_H