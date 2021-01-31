#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define FIELD_SIZE 8
#define INITIAL_MINE_COUNT 6
#define MINE_SYMBOL '*'
#define EMPTY_POSITION ' '
#define VISITED_POSITION ' '
#define INITIAL_SYMBOL_FIELD_VISIBLE '#'


char minefield_visible[FIELD_SIZE][FIELD_SIZE];
char minefield_hidden[FIELD_SIZE][FIELD_SIZE];

void print_field(char field[][FIELD_SIZE]);

// reveal_area_starting_from?
void reveal_zeros_at(int i, int j, char field_hidden[][FIELD_SIZE], char field_visible[][FIELD_SIZE]) {
  int dy, dx, dump;

  for(dy = -1; dy <= 1; dy++) {
    for(dx = -1; dx <= 1; dx++) {
      if(0 <= i+dy && i+dy < FIELD_SIZE && 0 <= j+dx && j+dx < FIELD_SIZE) {
        if(field_hidden[i+dy][j+dx] != MINE_SYMBOL) { // precisa dessa verificação?
          if(field_hidden[i+dy][j+dx] == '0' && field_visible[i+dy][j+dx] != VISITED_POSITION) {
            field_visible[i+dy][j+dx] = VISITED_POSITION;
            reveal_zeros_at(i+dy, j+dx, field_hidden, field_visible);
          }

          if(field_visible[i+dy][j+dx] == INITIAL_SYMBOL_FIELD_VISIBLE 
            && ('1' <= field_hidden[i+dy][j+dx] && field_hidden[i+dy][j+dx] <= '9')
            && field_hidden[i][j] == '0'
          ) {
            field_visible[i+dy][j+dx] = field_hidden[i+dy][j+dx];
          }

          if('1' <= field_hidden[i][j] && field_hidden[i][j] <= '9') {
            field_visible[i][j] = field_hidden[i][j];
          }
        }
      }
    }
  }
}


/**
 * Quem chama essa função garante que não há mina em i, j. Isso é 
 * aconsnelhável?
 */
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
 * 
 * not_allowed_i e not_allowed_j é a primeira posição chutada pelo jogador
 * e lá não é permitido colocar uma mina
 */
void place_mines(char field_hidden[][FIELD_SIZE], int mines_to_place, int not_allowed_i, int not_allowed_j, int seed) {
  int i, j;
  // provavelmente eu deveria colocar essa parte em uma função
  for(i = 0; i < FIELD_SIZE; i++) {
    for(j = 0; j < FIELD_SIZE; j++) {
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

    if(y != not_allowed_i && x != not_allowed_i 
      && field_hidden[y][x] != MINE_SYMBOL
    ) {
      field_hidden[y][x] = MINE_SYMBOL;
      mines_to_place--;
    }
  }
}


void init_field_hidden(char field[][FIELD_SIZE], int i, int j) {
  int seed = 0; // 0 é usado para seed aleatória
  place_mines(field, INITIAL_MINE_COUNT, i, j, seed);
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