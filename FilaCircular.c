#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define MAX 5 // Tamanho máximo da fila

typedef struct {
    int data[MAX];  // Array fixo para armazenar os elementos
    int front;      // Índice do início da fila
    int rear;       // Índice do final da fila
    int size;       // Número atual de elementos na fila
} FilaCircular;

// Funções da Fila Circular
FilaCircular *criarFila();
bool isFull(FilaCircular *fila);
bool isEmpty(FilaCircular *fila);
void enqueue(FilaCircular *fila, int valor);
int dequeue(FilaCircular *fila);
void exibirFila(FilaCircular *fila);

int main() {
	setlocale(LC_ALL,"Portuguese");
    FilaCircular *fila = criarFila();

    // Testando a fila circular
    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    enqueue(fila, 40);
    enqueue(fila, 50);

    printf("Estado da fila após inserções:\n");
    exibirFila(fila);

    printf("\nRemovendo dois elementos...\n");
    dequeue(fila);
    dequeue(fila);
    exibirFila(fila);

    printf("\nInserindo mais dois elementos (30 e 40)...\n");
    enqueue(fila, 60);
    enqueue(fila, 70);
    exibirFila(fila);

    return 0;
}

// Cria uma nova fila circular vazia
FilaCircular *criarFila() {
    FilaCircular *fila = (FilaCircular *)malloc(sizeof(FilaCircular));
    if (fila == NULL) {
        printf("Erro: Memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    fila->front = 0;
    fila->rear = 0;
    fila->size = 0;
    return fila;
}

// Verifica se a fila está cheia
bool isFull(FilaCircular *fila) {
    return fila->size == MAX;
}

// Verifica se a fila está vazia
bool isEmpty(FilaCircular *fila) {
    return fila->size == 0;
}

// Adiciona um elemento ao final da fila
void enqueue(FilaCircular *fila, int valor) {
    if (isFull(fila)) {
        printf("Erro: Fila cheia, não é possível adicionar %d.\n", valor);
        return;
    }
    fila->data[fila->rear] = valor;
    fila->rear = (fila->rear + 1) % MAX; // Movimento circular
    fila->size++;
}

// Remove e retorna o elemento do início da fila
int dequeue(FilaCircular *fila) {
    if (isEmpty(fila)) {
        printf("Erro: Fila vazia, não é possível remover elementos.\n");
        return -1;
    }
    int valor = fila->data[fila->front];
    fila->front = (fila->front + 1) % MAX; // Movimento circular
    fila->size--;
    return valor;
}

// Exibe o estado atual da fila
void exibirFila(FilaCircular *fila) {
    int i, pos;
    if (isEmpty(fila)) {
        printf("Fila está vazia.\n");
        return;
    }

    printf("Fila: ");
    for (i = 0, pos = fila->front; i < fila->size; i++) {
        printf("%d ", fila->data[pos]);
        pos = (pos + 1) % MAX; // Movimento circular
    }
    printf("\n");
}
