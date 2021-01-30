#include <stdio.h>
#include "minefield.h"

int main() {
  int remaining_mines = 6;

  init_fields(minefield_hidden, minefield_visible);
  // print_field(minefield_visible);
  print_field(minefield_hidden);
  /* inicializar campos */
  /*    posicionar bombas */
  
  /* enquanto todas as minas não foram econtradas */
  /*    imprimir campo   */
  /*    pedir ao jogador por uma posição   */
  /*    validar entrada   */
  /*    verificar se há mina na posição   */
  /*        se houver   */
  /*            finalizar jogo   */
  /*            jogador perdeu   */
  /*            revelar as posições das minas restantes   */
  /*        se não houver   */
  /*            revelar mais área (aqueles númerozinhos)   */



  return 0;
}