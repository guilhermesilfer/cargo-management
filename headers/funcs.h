#ifndef FUNCS_H
#define FUNCS_H

#include "structs.h"

Carga *create_cargo();

No *create_node(Carga *carga);

Fila *create_queue();

void enqueue(Fila *fila);

void dequeue(Fila *fila);

#endif
