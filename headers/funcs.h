#ifndef FUNCS_H
#define FUNCS_H

#include "structs.h"

Carga *create_cargo(Fila *fila);

No *create_node(Carga *carga);

Fila *create_queue();

void enqueue(Fila *fila, Carga *carga);

void dequeue(Fila *fila);

void show_by_id(Fila *fila);

void show_cargos(Fila *fila);

bool check_id(Fila *fila, int id);

#endif
