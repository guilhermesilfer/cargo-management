#include <stdio.h>
#include <stdbool.h>
#include "headers/structs.h"
#include "headers/funcs.h"
#include "headers/utils.h"

int main()
{
  Fila *fila = create_queue();
  fila = load_data(fila);
  // while para a execução continua do programa
  while (true)
  {
    print_menu();

    // continua até uma entrada válida ser inserida
    int input;
    printf("(Digite o número da opção que deseja)\n");
    printf("input: ");
    while (scanf("%d", &input) != 1 && input != 0 && input != 1 && input != 2)
    {
      printf("Digite um inteiro válido\n");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');
    printf("\n");

    switch (input) {
      case 0:
        return 0;
      case 1:
        Carga *carga = create_cargo(fila);
        enqueue(fila, carga);
        break;
      case 2:
        dequeue(fila);
        break;
      case 3:
        show_cargos(fila);
        break;
      case 4:
        show_by_id(fila);
        break;
    }
  }
}
