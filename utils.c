#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "headers/structs.h"
#include "headers/funcs.h"

void print_menu()
{
  printf("======================\n");
  printf("== GESTOR DE CARGAS ==\n");
  printf("======================\n\n");
  printf("[0] Sair\n");
  printf("[1] Inserir carga\n");
  printf("[2] Remover carga\n");
  printf("[3] Mostrar cargas\n");
  printf("[4] Procurar carga\n");
  printf("\n");
}

// remove \n do fim de uma string
char *remove_newline(char *string)
{
  int tamanho = strlen(string);

  for (int i = 0; i < tamanho; i++)
    if (string[i] == '\n') string[i] = '\0';

  return string;
}

// imprime uma carga
void print_cargo(Carga *carga)
{
  printf("   [ ID: %d | Tipo: %s | Peso: %.2f | Prioridade: %s | Descrição: %s ]\n",
    carga->id,
    carga->tipo,
    carga->peso,
    carga->prioridade,
    carga->descricao);
}

// escreve os dados no arquivo csv
void write_data(int id, char tipo[], float peso, char prioridade[], char descricao[])
{
  FILE *arquivo;
  arquivo = fopen("cargas.csv", "a");


  fprintf(arquivo, "%d,%s,%f,%s,%s\n", id, tipo, peso, prioridade, descricao);

  fclose(arquivo);
}

// função para carregar dados do arquivo .csv
Fila *load_data(Fila *nova_fila) {
  FILE *arquivo = fopen("cargas.csv", "r");
  nova_fila = create_queue();
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo cargas.csv\n");
    exit(EXIT_FAILURE);
  }

  char linha[200];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    // ignora linhas vazias
    if (linha[0] == '\n' || linha[0] == '\0') {
        continue;
    }

    // aloca a memória para nova carga
    Carga *nova_carga = malloc(sizeof(Carga));
    if (nova_carga == NULL)
    {
      printf("Deu merda\n");
      exit(EXIT_FAILURE);
    }
    // preencher os dados da carga
    printf("oi\n");
    sscanf(linha, "%d,%49[^,],%f,%19[^,],%99[^\n]",
      &nova_carga->id,
      nova_carga->tipo,
      &nova_carga->peso,
      nova_carga->prioridade,
      nova_carga->descricao);
    print_cargo(nova_carga);

    No *novo_no = create_node(nova_carga);
    if (novo_no == NULL) {
      printf("Erro ao alocar memória para o nó\n");
      free(nova_carga);
      fclose(arquivo);
      exit(EXIT_FAILURE);
    }

    enqueue(nova_fila, nova_carga);
  }

    fclose(arquivo);
    printf("Dados carregados com sucesso.\n\n");
    return nova_fila;
}

bool check_id(Fila *fila, int id){
  // testa se já existe elemento na fila
  if (fila->primeiro == NULL){
    return false;
  }

  No *atual = fila->primeiro;
  while(atual != NULL){
    if(atual->carga->id == id){
      return true;
    }
    atual = atual->proximo;
  }  
  return false;
}
