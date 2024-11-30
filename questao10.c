#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;


No* criaNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->anterior = novo;
    novo->proximo = novo;
    return novo;
}


void insereNoFinal(No **inicio, int valor) {
    No *novo = criaNo(valor);
    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        No *temp = *inicio;
        while (temp->proximo != *inicio) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
        novo->anterior = temp;
        novo->proximo = *inicio;
        (*inicio)->anterior = novo;
    }
}


void exibeListaNormal(No *inicio) {
    if (inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    No *temp = inicio;
    printf("Lista (ordem normal): ");
    do {
        printf("%d ", temp->valor);
        temp = temp->proximo;
    } while (temp != inicio);
    printf("\n");
}


void exibeListaReversa(No *inicio) {
	setlocale(LC_ALL,"Portuguese");
    if (inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    No *temp = inicio;
    // Vai até o último nó
    while (temp->proximo != inicio) {
        temp = temp->proximo;
    }

    // Exibe os elementos em ordem reversa
    printf("Lista (ordem reversa): ");
    No *primeiro = temp;
    do {
        printf("%d ", temp->valor);
        temp = temp->anterior;
    } while (temp != primeiro);
    printf("\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    No *inicio = NULL;
    int escolha, valor;

    do {
        printf("\n--- Menu de Gerenciamento da Lista Circular Duplamente Encadeada ---\n");
        printf("1. Inserir valor na lista\n");
        printf("2. Exibir lista (ordem normal)\n");
        printf("3. Exibir lista (ordem reversa)\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                insereNoFinal(&inicio, valor);
                printf("Valor %d inserido na lista.\n", valor);
                break;

            case 2:
                exibeListaNormal(inicio);
                break;

            case 3:
                exibeListaReversa(inicio);
                break;

            case 4:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}

