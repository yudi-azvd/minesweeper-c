#include <stdio.h>
#include <stdlib.h>

#include "minesweeper.h"
#include "ui.h"

// colocar em algum arquivo de UI
void clear_screen() {
    system("clear");
}

int main() {
    clear_screen();
    // talvez first_i e first_j sejam melhores
    int i, j, not_allowed_i, not_allowed_j;
    int remaining_uncovered_spots = FIELD_SIZE * FIELD_SIZE - INITIAL_MINE_COUNT;

    init_field_visible(minefield_visible);

    // render_field(minefield_visible, minefield_hidden, 0);
    debug_render_field(minefield_visible, minefield_hidden, 0);
    scanf("%d %d", &not_allowed_i, &not_allowed_j);
    // validar

    init_field_hidden(minefield_hidden, not_allowed_i, not_allowed_j);
    reveal_zeros_at(not_allowed_i, not_allowed_j, minefield_hidden, minefield_visible);

    while (remaining_uncovered_spots) {
        clear_screen();
        // render_field(minefield_visible, minefield_hidden, 0);
        debug_render_field(minefield_hidden, minefield_visible, 0);

        scanf("%d %d", &i, &j);
        // validar

        if (minefield_hidden[i][j] == MINE_SYMBOL) {
            // game over
            // revelar posições das minas restantes
            break;
        } else {
            // revelar mais área
            reveal_zeros_at(i, j, minefield_hidden, minefield_visible);
            remaining_uncovered_spots--;
        }
    }

    if (remaining_uncovered_spots <= 0) {
        printf("\n\n\tParabéns, você venceu!!!\n\n");
    } else {
        printf("\n\n\tVocê acertou uma mina... T-T\n\n");
    }

    return 0;
}