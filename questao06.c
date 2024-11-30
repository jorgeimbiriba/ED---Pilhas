#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int dado;
	struct No *proximo; //Ponteiro que aponta pro próximo nó
}No;

// Função para criar um novo nó
No* criaNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No)); //Alocação Dinâmica
    
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

//Insere um nó no início da lista
void insereInicio(No** topo, int dado) {
    No* novoNo = criaNo(dado); // Cria o novo nó
    novoNo->proximo = *topo; // Aponta para o nó atual que é a cabeça
    *topo = novoNo;          // Atualiza a cabeça para o novo nó
}

// Função para exibir os elementos da lista
void exibeLista(No* topo) {
    No* atual = topo;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}


int main() {
    No* lista = NULL; // Inicializa a lista como vazia
    int valor;

    printf("Digite valores para inserir na lista (digite -1 para sair):\n");
    while (1) {
        printf("Digite um valor inteiro: ");
        scanf("%d", &valor);
        if (valor == -1) {
            break; // Encerra o programa se o usuário digitar -1
        }
        insereInicio(&lista, valor); // Insere o valor no início da lista
        exibeLista(lista);           // Exibe a lista atualizada
    }

    // Libera a memória dos nós antes de sair
    No* atual = lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    printf("Programa encerrado.\n");
    
    return 0;
}
