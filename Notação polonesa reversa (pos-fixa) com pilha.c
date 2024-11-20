#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

struct stackNode {
    float data;                 // Armazena números em ponto flutuante
    struct stackNode *nextPtr;  // Ponteiro para o próximo nó
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

    printf("Digite uma expressao em notação pos-fixada (ex: 5 3 + 2 *):\n");
    fgets(expression, sizeof(expression), stdin);

    // Remover o caractere de nova linha, se existir
    expression[strcspn(expression, "\n")] = '\0';

    float result = evaluateRPN(expression);

    printf("O resultado da expressão : %#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>

// Estrutura da pilha
struct stackNode {
    float data;                 // Armazena números em ponto flutuante
    struct stackNode *nextPtr;  // Ponteiro para o próximo nó
};

typedef struct stackNode STACKNODE;
typedef STACKNODE *STACKNODEPTR;

// Funções da pilha
void push(STACKNODEPTR *topPtr, float value);
float pop(STACKNODEPTR *topPtr);
int isEmpty(STACKNODEPTR topPtr);

// Funções principais
float evaluateRPN(char *expression);
void basicOperator(char *token, STACKNODEPTR *stack);
void calcFunction(char *token, STACKNODEPTR *stack);

int main() {
	setlocale(LC_ALL,"Portuguese");
    char expression[100];

    printf("Digite uma expressão em notação pós-fixada (ex: 5 3 + 2 ^):\n");
    fgets(expression, sizeof(expression), stdin);

    // Remove o caractere de nova linha, se existir
    expression[strcspn(expression, "\n")] = '\0';

    float result = evaluateRPN(expression);

    printf("O resultado da expressão é: %.2f\n", result);

    return 0;
}

// Avalia uma expressão em notação pós-fixada usando pilha
float evaluateRPN(char *expression) {
    STACKNODEPTR stack = NULL; // Inicializa a pilha
    char *token = strtok(expression, " "); // Divide a string por espaços

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Token é um número (positivo ou negativo)
            float value = atof(token);
            push(&stack, value);
        } else if (strchr("+-*/^", token[0]) && strlen(token) == 1) {
            // Token é um operador de um caractere
            basicOperator(token, &stack);
        } else if (strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 ||
                   strcmp(token, "tan") == 0 || strcmp(token, "sqrt") == 0 ||
                   strcmp(token, "log") == 0) {
            // Token é uma função matemática
            calcFunction(token, &stack);
        } else {
            printf("Erro: Token inválido '%s'.\n", token);
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " "); // Próximo token
    }

    if (stack == NULL || stack->nextPtr != NULL) {
        printf("Erro: Expressão mal formada.\n");
        exit(EXIT_FAILURE);
    }

    return pop(&stack); // Retorna o resultado final
}

// Insere um valor no topo da pilha
void push(STACKNODEPTR *topPtr, float value) {
    STACKNODEPTR newPtr = malloc(sizeof(STACKNODE));

    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else {
        printf("Erro: Memória insuficiente para inserir %.2f.\n", value);
        exit(EXIT_FAILURE);
    }
}

// Manipula valor do topo da pilha
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

//Verifica se a pilha está vazia
int isEmpty(STACKNODEPTR topPtr) {
    return topPtr == NULL;
}

// Função para as operadores básicas
void basicOperator(char *token, STACKNODEPTR *stack) {
    float operand2 = pop(stack);
    float operand1 = pop(stack);
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
                printf("Erro: Divisão por zero.\n");
                exit(EXIT_FAILURE);
            }
            result = operand1 / operand2;
            break;
        case '^':
            result = pow(operand1, operand2);
            break;
        default:
            printf("Erro: Operador inválido '%s'.\n", token);
            exit(EXIT_FAILURE);
    }

    push(stack, result);
}

// Função para as funções matemáticas
void calcFunction(char *token, STACKNODEPTR *stack) {
    float operand = pop(stack);
    float result;

    if (strcmp(token, "sin") == 0) {
        result = sin(operand);
    } else if (strcmp(token, "cos") == 0) {
        result = cos(operand);
    } else if (strcmp(token, "tan") == 0) {
        result = tan(operand);
    } else if (strcmp(token, "sqrt") == 0) {
        if (operand < 0) {
            printf("Erro: Raiz quadrada de número negativo.\n");
            exit(EXIT_FAILURE);
        }
        result = sqrt(operand);
    } else if (strcmp(token, "log") == 0) {
        if (operand <= 0) {
            printf("Erro: Logaritmo de valor não positivo.\n");
            exit(EXIT_FAILURE);
        }
        result = log(operand);
    } else {
        printf("Erro: Função matemática inválida '%s'.\n", token);
        exit(EXIT_FAILURE);
    }
    push(stack, result);
}
