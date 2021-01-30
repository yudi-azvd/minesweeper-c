#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define FIELD_SIZE 8
#define MINE_SYMBOL '*'
#define EMPTY_POSITION ' '
// #define INITIAL_SYMBOL_

char minefield_visible[FIELD_SIZE][FIELD_SIZE];
char minefield_hidden[FIELD_SIZE][FIELD_SIZE];


void print_field(char field[][FIELD_SIZE]);


/**
 * se o jogo resetar sem terminar, srand(time(NULL)) vai dar ruim?
 */
void place_mines(char field[][FIELD_SIZE], int mines_to_place) {
  int i, j, has_to_place_mine = 0;
  for (i = 0; i < FIELD_SIZE; i++) {
    for ( j = 0; j < FIELD_SIZE; j++) {
      field[i][j] = EMPTY_POSITION;
    }
  }

  srand(time(NULL));
  int x, y;
  while (mines_to_place > 0) {
    x = rand() % FIELD_SIZE;
    y = rand() % FIELD_SIZE;

    print_field(field);
    printf("x: %d, y: %d\n", x, y);
    if (field[y][x] != MINE_SYMBOL) {
      field[y][x] = MINE_SYMBOL;
      mines_to_place--;
    }
  }

  // printf("mines to place: %d \n", mines_to_place);
  printf("\n");
}


void init_field_hidden(char field[][FIELD_SIZE]) {
  // place mines
  place_mines(field, 6);
  // count for each position
}

void init_field_visible(char field[][FIELD_SIZE]) {
  int i, j;

  for (i = 0; i < FIELD_SIZE; i++) {
    for ( j = 0; j < FIELD_SIZE; j++) {
      field[i][j] = '#';
    }
  }
}


void init_fields(char hidden[][FIELD_SIZE], char visible[][FIELD_SIZE]) {
  init_field_hidden(hidden);
  init_field_visible(visible);
}

void print_field(char field[][FIELD_SIZE]) {
  int i, j;

  printf("\t ---------------\n");
  for (i = 0; i < FIELD_SIZE; i++) {
    printf("\t｜");
    for (j = 0; j < FIELD_SIZE-1; j++) {
      printf("%c ", field[i][j]);
    }
    printf("|\b\n");
  }
  printf("\t ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
  
}

#endif // MINEFIED_H