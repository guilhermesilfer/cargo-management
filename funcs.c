#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "headers/structs.h"
#include "headers/utils.h"

//typedef struct Carga                              //typedef struct No         //typedef struct Fila
//{                                                 //{                         //{
//  int id;                                         //  Carga *carga;            //  No *primeiro, *ultimo;
//  float peso;                                     //  struct No *proximo;     //} Fila;
//  char tipo[15], prioridade[7], descricao[40];    //} No;
//} Carga;

Carga *create_cargo()
{
  Carga *nova_carga = malloc(sizeof(Carga));

  printf("\n(Digite as informações a seguir)\n");
// pega o id
  printf("(Necessário ser inteiro)\n");
  printf("ID: ");
  while (scanf("%d", &nova_carga->id) != 1)
  {
    printf("Digite um inteiro\n");
    printf("ID: ");
    while (getchar() != '\n');
  }
  while (getchar() != '\n');
  printf("\n");

// pega o tipo da carga
  int input = 0;
  printf("(Digite o número correspondente ao tipo da carga)\n");
  printf("[1] Container | [2] Granel sólido | [3] Granel líquido\n");
  printf("Tipo: ");
  while (input != 1 && input != 2 && input != 3)
  {
    // checa se foi digitado um número
    while (scanf("%d", &input) != 1)
    {
      printf("Digite um inteiro\n");
      printf("Tipo: ");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');
    // checa se o número digitado é válido
    if (input != 1 && input != 2 && input != 3)
    {
      printf("Digite um número válido\n");
      printf("Tipo: ");
      continue;
    }
  }
  printf("\n");

  // inicializa o tipo da carga
  if (input == 1) strcpy(nova_carga->tipo, "Container");
  if (input == 2) strcpy(nova_carga->tipo, "Granel sólido");
  if (input == 3) strcpy(nova_carga->tipo, "Granel líquido");

// pega o peso
  printf("(Em (kg), se necessário separe a parte decimal com ponto)\n");
  printf("Peso: ");
  // checa se foi digitado um número
  while (scanf("%f", &nova_carga->peso) != 1)
  {
    while (getchar() != '\n');
    printf("Entrada inválida\n");
    printf("Peso: ");
  }
  while (getchar() != '\n');
  printf("\n");

// pega a prioridade da carga
  input = 0;
  printf("(Digite o número correspondente à prioridade da carga)\n");
  printf("[1] Baixa | [2] Normal | [3] Alta\n");
  printf("Tipo: ");
  while (input != 1 && input != 2 && input != 3)
  {
    // checa se foi digitado um número
    while (scanf("%d", &input) != 1)
    {
      printf("Digite um inteiro\n");
      printf("Tipo: ");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');
    // checa se o número digitado é válido
    if (input != 1 && input != 2 && input != 3)
    {
      printf("Digite um número válido\n");
      printf("Tipo: ");
      continue;
    }
  }
  printf("\n");

  // inicializa o tipo da carga
  if (input == 1) strcpy(nova_carga->prioridade, "Baixa");
  if (input == 2) strcpy(nova_carga->prioridade, "Normal");

  if (input == 3) strcpy(nova_carga->prioridade, "Alta");
// pega a descrição
  while (true)
  {
    char *string_ptr;
    string_ptr = malloc(sizeof(char) * 42);
    printf("Descrição: ");
    fgets(string_ptr, 42, stdin);
    if (strlen(string_ptr) > 40)
    {
      printf("O tamanho máximo para descrição é 40\n");
      continue;
    }

    strcpy(nova_carga->descricao, remove_newline(string_ptr));
    break;
  }

  // imprime a nova carga

  return nova_carga;
}

No *create_node(Carga *carga)
{
  No *novo_no = malloc(sizeof(No));
  novo_no->carga = carga;
  novo_no->proximo = NULL;
  return novo_no;
}

Fila *create_queue()
{
  Fila *nova_fila = malloc(sizeof(Fila));
  nova_fila->primeiro = NULL;
  nova_fila->ultimo = NULL;
  return nova_fila;
}

void enqueue(Fila *fila)
{
  Carga *nova_carga = create_cargo();
  No *novo_no = create_node(nova_carga);

  if (fila->ultimo == NULL)
  {
    fila->primeiro = novo_no;
    fila->ultimo = novo_no;
    return;
  }

  fila->ultimo->proximo = NULL;
  fila->ultimo = novo_no;
}
//void enqueue(Queue* q, int new_data)
//{
//
//    // Create a new linked list node
//    Node* new_node = createNode(new_data);
//
//    // If queue is empty, the new node is both the front
//    // and rear
//    if (q->rear == NULL) {
//        q->front = q->rear = new_node;
//        return;
//    }
//
//    // Add the new node at the end of the queue and
//    // change rear
//    q->rear->next = new_node;
//    q->rear = new_node;
//}

void dequeue(Fila *fila)
{
  No *atual = fila->primeiro;
  do
  {
    // procura pela primeira carga com prioridade alta, se houver, remove
    if (strcmp(atual->carga->prioridade, "Alta") == 0)
    {
      No *tmp_atual = atual;
      atual = atual->proximo;
      free(tmp_atual);
      printf("Item de prioridade alta removido com sucesso.\n");
      return;
    }
    atual = atual->proximo;
  } while (atual->proximo != NULL);

  // caso não ache nenhuma carga com prioridade alta, remove o primeiro
  No *cabeca = fila->primeiro;
  No *tmp_cabeca = cabeca;
  cabeca = cabeca->proximo;
  free(tmp_cabeca);
  printf("Item removido com sucesso.\n");
  return;
}
