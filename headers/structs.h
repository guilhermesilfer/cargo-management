#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Carga
{
  int id;
  float peso;
  char tipo[15], prioridade[7], descricao[40];
} Carga;

typedef struct No
{
  Carga *carga;
  struct No *proximo;
} No;

typedef struct Fila
{
  No *primeiro, *ultimo;
} Fila;

#endif
