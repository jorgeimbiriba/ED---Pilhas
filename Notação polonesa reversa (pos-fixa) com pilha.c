#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct stackNode {
    float data;                 // Armazena n�meros em ponto flutuante
    struct stackNode *nextPtr;  // Ponteiro para o pr�ximo n�
};

typedef struct stackNode STACKNODE;
typedef STACKNODE *STACKNODEPTR;

// Prototipos
void push(STACKNODEPTR *topPtr, float value);
float pop(STACKNODEPTR *topPtr);
int isEmpty(STACKNODEPTR topPtr);
void instructions(void);
float evaluateRPN(char *expression);

int main() {
    char expression[100];

    printf("Digite uma express�o em nota��o p�s-fixada (ex: 5 3 + 2 *):\n");
    fgets(expression, sizeof(expression), stdin);

    // Remover o caractere de nova linha, se existir
    expression[strcspn(expression, "\n")] = '\0';

    float result = evaluateRPN(expression);

    printf("O resultado da express�o �: %.2f\n", result);

    return 0;
}

/* Insere um valor no topo da pilha */
void push(STACKNODEPTR *topPtr, float value) {
    STACKNODEPTR newPtr = malloc(sizeof(STACKNODE));

    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else {
        printf("Erro: Mem�ria insuficiente para inserir %.2f.\n", value);
        exit(EXIT_FAILURE);
    }
}

/* Remove e retorna o valor do topo da pilha */
float pop(STACKNODEPTR *topPtr) {
    if (isEmpty(*topPtr)) {
        printf("Erro: Tentativa de pop em uma pilha vazia.\n");
        exit(EXIT_FAILURE);
    }

    STACKNODEPTR tempPtr = *topPtr;
    float popValue = tempPtr->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
}

/* Verifica se a pilha est� vazia */
int isEmpty(STACKNODEPTR topPtr) {
    return topPtr == NULL;
}

/* Avalia uma express�o em nota��o p�s-fixada usando pilha */
float evaluateRPN(char *expression) {
    STACKNODEPTR stack = NULL;
    char *token = strtok(expression, " ");  // Divide a string por espa�os

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Token � um n�mero (positivo ou negativo)
            float value = atof(token);
            push(&stack, value);
        } else if (strchr("+-*/", token[0]) && strlen(token) == 1) {
            // Token � um operador (+, -, *, /)
            if (stack == NULL || stack->nextPtr == NULL) {
                printf("Erro: Express�o inv�lida.\n");
                exit(EXIT_FAILURE);
            }

            float operand2 = pop(&stack);
            float operand1 = pop(&stack);
            float result;

            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Erro: Divis�o por zero.\n");
                        exit(EXIT_FAILURE);
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Erro: Operador inv�lido '%s'.\n", token);
                    exit(EXIT_FAILURE);
            }

            push(&stack, result);
        } else {
            printf("Erro: Token inv�lido '%s'.\n", token);
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");  // Pr�ximo token
    }

    if (stack == NULL || stack->nextPtr != NULL) {
        printf("Erro: Express�o mal formada.\n");
        exit(EXIT_FAILURE);
    }

    return pop(&stack);  // O resultado final
}
