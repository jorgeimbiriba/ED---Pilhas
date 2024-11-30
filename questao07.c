#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 32  // Tamanho máximo da pilha (suficiente para números de 32 bits)

typedef struct{
    int itens[MAX];
    int topo;
}Pilha;

// Função para inicializar a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

// Função para verificar se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Função para empilhar um elemento
void empilhar(Pilha *p, int elemento) {
    if (pilhaCheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = elemento; //Incremento para empilhar
}

// Função para desempilhar um elemento
int desempilhar(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;  // Retorna -1 em caso de erro
    }
    return p->itens[(p->topo)--];
}

// Função principal para converter decimal para binário
void decimalParaBinario(int numero) {
	setlocale(LC_ALL,"Portuguese");
    Pilha pilha;
    inicializaPilha(&pilha);

    // Caso especial para o número zero
    if (numero == 0) {
        printf("O número binário é: 0\n");
        return;
    }

    // Empilha os restos da divisão por 2
    while (numero > 0) {
        empilhar(&pilha, numero % 2);
        numero /= 2;
    }

    // Desempilha e imprime os valores na ordem correta
    printf("O número binário é: ");
    while (!pilhaVazia(&pilha)) {
        printf("%d", desempilhar(&pilha));
    }
    printf("\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    int numero;

    printf("Digite um número decimal para converter em binário: ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Por favor, insira um número inteiro não negativo.\n");
    } else {
        decimalParaBinario(numero);
    }

    return 0;
}

