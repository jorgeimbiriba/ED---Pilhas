#include <stdio.h>
#include <stdlib.h>

struct stackNode { /* estrutura auto-referenciada */
    int data;
    struct stackNode *nextPtr;
};

typedef struct stackNode STACKNODE;
typedef STACKNODE *STACKNODEPTR;

void push(STACKNODEPTR *, int);
int pop(STACKNODEPTR *);
int isEmpty(STACKNODEPTR);
void printStack(STACKNODEPTR);
void instructions(void);

int main() {
    STACKNODEPTR stackPtr = NULL; /* Ponteiro para o topo da pilha */
    int choice, value;

    instructions();
    printf("? ");
    scanf("%d", &choice);

    while (choice != 3) {
        switch (choice) {
            case 1: /* Coloca valor na pilha */
                printf("Digite um inteiro: ");
                scanf("%d", &value);
                push(&stackPtr, value);
                printStack(stackPtr);
                break;
            case 2: /* Retira valor da pilha */
                if (!isEmpty(stackPtr)) {
                    printf("O valor retirado é %d.\n", pop(&stackPtr));
                } else {
                    printf("A pilha está vazia.\n");
                }
                printStack(stackPtr);
                break;
            default:
                printf("Escolha inválida.\n\n");
                instructions();
                break;
        }
        printf("? ");
        scanf("%d", &choice);
    }

    printf("Fim do programa.\n");
    return 0;
}

/* Imprime as instruções */
void instructions(void) {
    printf("Digite uma escolha:\n"
           "1 para colocar um valor na pilha\n"
           "2 para retirar um valor da pilha\n"
           "3 para finalizar o programa\n");
}

/* Insere um valor no topo da pilha */
void push(STACKNODEPTR *topPtr, int info) {
    STACKNODEPTR newPtr;
    newPtr = malloc(sizeof(STACKNODE));

    if (newPtr != NULL) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else {
        printf("%d não foi inserido. Não existe memória disponível.\n", info);
    }
}

/* Remove um valor do topo da pilha */
int pop(STACKNODEPTR *topPtr) {
    STACKNODEPTR tempPtr;
    int popValue;

    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
}

/* Imprime a pilha */
void printStack(STACKNODEPTR currentPtr) {
    if (currentPtr == NULL) {
        printf("A pilha está vazia.\n\n");
    } else {
        printf("A pilha é:\n");
        while (currentPtr != NULL) {
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        printf("NULL\n\n");
    }
}

/* A pilha está vazia? */
int isEmpty(STACKNODEPTR topPtr) {
    return topPtr == NULL;
}
