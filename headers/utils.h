#ifndef UTILS_H
#define UTILS_H

#include "structs.h"
#include "stdbool.h"

void print_menu();

char *remove_newline(char *string);

void print_cargo(Carga *carga);

void write_data(int id, char tipo[], float peso, char prioridade[], char descricao[]);

// função de carregamento dos dados do arquivo
Fila *load_data(Fila *fila);

bool check_id(Fila *fila, int id);

#endif