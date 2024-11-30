#include <stdio.h>
#include <stdbool.h>
#include "headers/structs.h"
#include "headers/funcs.h"

int main()
{
  Fila *fila = create_queue();

  // while para a execução continua do programa
  while (true)
  {
    int input;
    // continua até uma entrada válida ser inserida
    printf("(Digite o número da opção que deseja)\n");
    printf("input: ");
    while (scanf("%d", &input) != 1 && input != 0 && input != 1)
    {
      printf("Digite um inteiro válido\n");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');

    switch (input) {
      case 0:
        return 0;
      case 1:
        enqueue(fila);
        break;
    }
  }
}
