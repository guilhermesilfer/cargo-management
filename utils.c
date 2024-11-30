#include <stdio.h>
#include <string.h>
#include "headers/structs.h"

void print_menu()
{
  printf("======================\n");
  printf("== GESTOR DE CARGAS ==\n");
  printf("======================\n\n");
  printf("[0] Sair\n");
  printf("[1] Inserir carga\n");
  printf("[2] \n");
  printf("[3] \n");
  printf("[4] \n");
}

char *remove_newline(char *string)
{
  int tamanho = strlen(string);

  for (int i = 0; i < tamanho; i++)
    if (string[i] == '\n') string[i] = '\0';

  return string;
}

void print_cargo(Carga *carga)
{
  printf("\n   [ ID: %d | Tipo: %s | Peso: %.2f | Prioridade: %s | Descrição: %s ]\n",
    carga->id,
    carga->tipo,
    carga->peso,
    carga->prioridade,
    carga->descricao);
  printf("\n");
}
