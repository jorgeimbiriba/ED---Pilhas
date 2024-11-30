#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct No {
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;

// Fun��o para criar um novo n�
No* criaNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

// Adicionar um n� ao final da lista
void insereNoFinal(No **inicio, int valor) {
    No *novo = criaNo(valor);
    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        No *temp = *inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
        novo->anterior = temp;
    }
}

// Exibir os valores da lista
void exibeLista(No *inicio) {
    No *temp = inicio;
    printf("Lista: ");
    while (temp != NULL) {
        printf("%d ", temp->valor);
        temp = temp->proximo;
    }
    printf("\n");
}

// Fun��o para remover um n� com um valor espec�fico
void removeNo(No **inicio, int valor) {
	setlocale(LC_ALL,"Portuguese");
    if (*inicio == NULL) {
        printf("A lista est� vazia.\n");
        return;
    }

    No *temp = *inicio;

    // Procurar o n� com o valor
    while (temp != NULL && temp->valor != valor) {
        temp = temp->proximo;
    }

    // Se o n� n�o for encontrado
    if (temp == NULL) {
        printf("Valor %d n�o encontrado na lista.\n", valor);
        return;
    }

    // Se o n� encontrado for o in�cio da lista
    if (temp == *inicio) {
        *inicio = temp->proximo;
        if (*inicio != NULL) {
            (*inicio)->anterior = NULL;
        }
    } else {
        // Ajustar os ponteiros do n� anterior
        temp->anterior->proximo = temp->proximo;

        // Ajustar os ponteiros do n� seguinte
        if (temp->proximo != NULL) {
            temp->proximo->anterior = temp->anterior;
        }
    }

    free(temp); // Liberar a mem�ria do n� removido
    printf("Valor %d removido da lista.\n", valor);
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    No *inicio = NULL;
    int escolha, valor;

    do {
        printf("\n--- Menu de Gerenciamento da Lista Duplamente Encadeada ---\n");
        printf("1. Inserir valor na lista\n");
        printf("2. Exibir lista\n");
        printf("3. Remover valor da lista\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                insereNoFinal(&inicio, valor);
                printf("Valor %d inserido na lista.\n", valor);
                break;

            case 2:
                exibeLista(inicio);
                break;

            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removeNo(&inicio, valor);
                break;

            case 4:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}

