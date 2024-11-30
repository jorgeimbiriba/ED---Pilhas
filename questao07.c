#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 32  // Tamanho m�ximo da pilha (suficiente para n�meros de 32 bits)

typedef struct{
    int itens[MAX];
    int topo;
}Pilha;

// Fun��o para inicializar a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

// Fun��o para verificar se a pilha est� cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Fun��o para verificar se a pilha est� vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Fun��o para empilhar um elemento
void empilhar(Pilha *p, int elemento) {
    if (pilhaCheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = elemento; //Incremento para empilhar
}

// Fun��o para desempilhar um elemento
int desempilhar(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;  // Retorna -1 em caso de erro
    }
    return p->itens[(p->topo)--];
}

// Fun��o principal para converter decimal para bin�rio
void decimalParaBinario(int numero) {
	setlocale(LC_ALL,"Portuguese");
    Pilha pilha;
    inicializaPilha(&pilha);

    // Caso especial para o n�mero zero
    if (numero == 0) {
        printf("O n�mero bin�rio �: 0\n");
        return;
    }

    // Empilha os restos da divis�o por 2
    while (numero > 0) {
        empilhar(&pilha, numero % 2);
        numero /= 2;
    }

    // Desempilha e imprime os valores na ordem correta
    printf("O n�mero bin�rio �: ");
    while (!pilhaVazia(&pilha)) {
        printf("%d", desempilhar(&pilha));
    }
    printf("\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    int numero;

    printf("Digite um n�mero decimal para converter em bin�rio: ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Por favor, insira um n�mero inteiro n�o negativo.\n");
    } else {
        decimalParaBinario(numero);
    }

    return 0;
}

