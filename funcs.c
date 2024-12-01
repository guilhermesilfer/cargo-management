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

// cria uma carga
Carga *create_cargo(Fila *fila)
{
  Carga *nova_carga = malloc(sizeof(Carga));

  printf("\n(Digite as informações a seguir)\n");

// pega o id
  printf("(Necessário ser inteiro)\n");
  printf("ID: ");
  while (true)
  {
    while (scanf("%d", &nova_carga->id) != 1)
    {
      printf("Digite um inteiro\n");
      printf("ID: ");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');

    if(check_id(fila, nova_carga->id)){
      printf("O ID já existe, digite outro ID\n");
      printf("ID: ");
      continue;
    }
    break;
  }
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
    printf("\n");

    strcpy(nova_carga->descricao, remove_newline(string_ptr));
    break;
  }

  // escreve a nova carga no arquivo cargas.csv
  write_data(nova_carga->id, nova_carga->tipo, nova_carga->peso, nova_carga->prioridade, nova_carga->descricao);

  return nova_carga;
}

// cria um nó
No *create_node(Carga *carga)
{
  No *novo_no = malloc(sizeof(No));
  novo_no->carga = carga;
  novo_no->proximo = NULL;
  return novo_no;
}

// cria uma fila
Fila *create_queue()
{
  Fila *nova_fila = malloc(sizeof(Fila));
  nova_fila->primeiro = NULL;
  nova_fila->ultimo = NULL;
  return nova_fila;
}

// adiciona um novo nó no fim da fila
void enqueue(Fila *fila, Carga *nova_carga)
{
  // coleta as informações da carga e cria
  // novo nó com as informações coletadas
  No *novo_no = create_node(nova_carga);

  // se a fila estirver vazia, o novo nó
  // vai ser o primeiro e último da lista
  if (fila->ultimo == NULL)
  {
    fila->primeiro = novo_no;
    fila->ultimo = novo_no;
    return;
  }

  // se não estiver vazia, o proximo do ultimo
  // deixa de ser NULL e passa a ser o novo nó
  fila->ultimo->proximo = novo_no;
  // agora o ultimo passa a ser o novo nó
  fila->ultimo = novo_no;
}

// remove o ultimo nó da lista
void dequeue(Fila *fila)
{
  if (fila->primeiro == NULL)
  {
    printf("Fila vazia, impossível remover\n\n");
    return;
  }

  No *atual = fila->primeiro;
  No *anterior = NULL;

  // procura pelo primeiro nó com prioridade alta
  while (atual != NULL)
  {
    if (strcmp(atual->carga->prioridade, "Alta") == 0)
    {
      // remove o nó com prioridade alta
      if (anterior == NULL)
      {
        // se o nó com prioridade alta é o primeiro
        fila->primeiro = atual->proximo;
      }
      else
      {
        // se está no meio ou no final
        anterior->proximo = atual->proximo;
      }

      // se preciso, ajusta o ultimo nó 
      if (atual == fila->ultimo)
      {
        fila->ultimo = anterior;
      }

      free(atual);
      printf("Carga de prioridade alta removida com sucesso.\n");
      return;
    }

    // avança pro próximo nó
    anterior = atual;
    atual = atual->proximo;
  }

  // se nao encontrar no com prioridade alta, remove o primeiro nó
  No *tmp = fila->primeiro;
  fila->primeiro = fila->primeiro->proximo;

  // se preciso, ajusta o ultimo nó 
  if (fila->primeiro == NULL)
  {
    fila->ultimo = NULL;
  }

  free(tmp);
  printf("Carga removida com sucesso.\n");
}

// mostra carga de acordo com o id
void show_by_id(Fila *fila){
  int id;
  printf("ID: ");
  while (scanf("%d", &id) != 1)
  {
    while (getchar() != '\n');
    printf("Digite um ID válido\n");
    printf("ID: ");
  }
  printf("\n");

  if (fila->primeiro == NULL){
    printf("A fila está vazia. Não foi encontrada nenhuma carga.\n");
    return;
  }

  No *atual  = fila->primeiro;
  do{
    if(atual->carga->id == id){
      printf("\n\n");
      return;
    }
    atual = atual->proximo;
  }while (atual != NULL);
  printf("Nenhuma carga com o ID %d foi encontrada.\n", id);
}

// mostra todos os cargos do inicio ao fim
void show_cargos(Fila *fila)
{
  No *atual = fila->primeiro;

  if (fila->primeiro == NULL)
  {
    printf("Nenhuma carga a ser exibida.\n\n");
    return;
  }

  do
  {
    print_cargo(atual->carga);
    atual = atual->proximo;
  } while (atual != NULL);
  printf("\n");
  return;
}
