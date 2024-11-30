#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 5  // Tamanho m�ximo da fila

typedef struct {
    int itens[MAX];
    int inicio;
    int fim;
    int tamanho;
} FilaCircular;

// Fun��o para inicializar a fila
void inicializaFila(FilaCircular *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
}

// Fun��o para verificar se a fila est� cheia
int filaCheia(FilaCircular *fila) {
    return fila->tamanho == MAX;
}

// Fun��o para verificar se a fila est� vazia
int filaVazia(FilaCircular *fila) {
    return fila->tamanho == 0;
}

// Fun��o para adicionar uma senha na fila
void enfileirar(FilaCircular *fila, int senha) {
	setlocale(LC_ALL,"Portuguese");
    if (filaCheia(fila)) {
        printf("Fila cheia! N�o � poss�vel adicionar novas senhas.\n");
        return;
    }
    fila->fim = (fila->fim + 1) % MAX;
    fila->itens[fila->fim] = senha;
    fila->tamanho++;
    printf("Senha %d adicionada � fila.\n", senha);
}

// Fun��o para remover uma senha da fila
int desenfileirar(FilaCircular *fila) {
	setlocale(LC_ALL,"Portuguese");
    if (filaVazia(fila)) {
        printf("\nFila vazia! N�o h� senhas para atendimento.\n");
        return -1;
    }
    int senha = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->tamanho--;
    printf("\nSenha %d atendida.\n", senha);
    return senha;
}

// Fun��o para exibir as senhas na fila
void exibirFila(FilaCircular *fila) {
	setlocale(LC_ALL,"Portuguese");
    if (filaVazia(fila)) {
        printf("\nA fila est� vazia.\n");
        return;
    }
    printf("Senhas na fila: ");
    int count = fila->tamanho;
    int i = fila->inicio;
    while (count > 0) {
        printf("%d ", fila->itens[i]);
        i = (i + 1) % MAX;
        count--;
    }
    printf("\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    FilaCircular fila;
    inicializaFila(&fila);

    int escolha, senha = 0;

    do {
        printf("\n--- Gerenciamento de Senhas de Atendimento ---\n");
        printf("1. Gerar nova senha\n");
        printf("2. Atender pr�xima senha\n");
        printf("3. Exibir senhas na fila\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                senha++;
                enfileirar(&fila, senha);
                break;
            case 2:
                desenfileirar(&fila);
                break;
            case 3:
                exibirFila(&fila);
                break;
            case 4:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("\nOp��o inv�lida! Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}

