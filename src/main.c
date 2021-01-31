#include <stdio.h>
#include <stdlib.h>

#include "minefield.h"

// colocar em algum arquivo de UI
void clear_screen() {
  system("clear");
}

int main() {
  int remaining_mines = MINES_TO_START;

  init_fields(minefield_hidden, minefield_visible);
  
  int i, j;
  while(remaining_mines > 0) {
    clear_screen();
    // print_field(minefield_visible);
    debug_print_field(minefield_hidden, minefield_visible);

    scanf("%d %d", &i, &j);
    // validar 

    if(minefield_hidden[i][j] == MINE_SYMBOL) {
      // game over
      // revelar posições das minas restantes
      break;
    }
    else {
      // revelar mais área
      remaining_mines--;
    }
  }

  if(remaining_mines <= 0) {
    printf("\n\n\tParabéns, você venceu!!!\n\n");
  }
  else {
    printf("\n\n\tVocê acertou uma mina... T-T\n\n");
  }
  return 0;
}