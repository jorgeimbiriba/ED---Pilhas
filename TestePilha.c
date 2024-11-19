#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct listNode {
    char data;
    struct listNode *nextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void criarLista(LISTNODEPTR *sPtr);
void inserirNoInicio(LISTNODEPTR *sPtr, char value);
void inserirNoFim(LISTNODEPTR *sPtr, char value);
void inserirNoMeio(LISTNODEPTR *sPtr, char value, int posicao);
char excluirNoInicio(LISTNODEPTR *sPtr);
char excluirNoFim(LISTNODEPTR *sPtr);
char excluirElemento(LISTNODEPTR *sPtr, char value);
LISTNODEPTR buscar(LISTNODEPTR sPtr, char value);
void exibirPrimeiro(LISTNODEPTR sPtr);
void exibirUltimo(LISTNODEPTR sPtr);
void exibirTodos(LISTNODEPTR sPtr);
int tamanhoLista(LISTNODEPTR sPtr);
void instructions(void);

int main() {
    LISTNODEPTR startPtr = NULL;
    int choice, posicao;
    char item;
    // Define o locale para português do Brasil
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    instructions();
    printf("? ");
    scanf("%d", &choice);

    while (choice != 0) {
        switch (choice) {
            case 1:
                criarLista(&startPtr);
                break;
            case 2:
                printf("Digite um caractere: ");
                scanf(" %c", &item);
                inserirNoInicio(&startPtr, item);
                exibirTodos(startPtr);
                break;
            case 3:
                printf("Digite um caractere: ");
                scanf(" %c", &item);
                inserirNoFim(&startPtr, item);
                exibirTodos(startPtr);
                break;
            case 4:
                printf("Digite um caractere: ");
                scanf(" %c", &item);
                printf("Digite a posição para inserir: ");
                scanf("%d", &posicao);
                inserirNoMeio(&startPtr, item, posicao);
                exibirTodos(startPtr);
                break;
            case 5:
                exibirPrimeiro(startPtr);
                break;
            case 6:
                exibirUltimo(startPtr);
                break;
            case 7:
                exibirTodos(startPtr);
                break;
            case 8:
                printf("Tamanho da lista: %d\n", tamanhoLista(startPtr));
                break;
            case 9:
                excluirNoInicio(&startPtr);
                exibirTodos(startPtr);
                break;
            case 10:
                excluirNoFim(&startPtr);
                exibirTodos(startPtr);
                break;
            case 11:
                printf("Digite o caractere a ser removido: ");
                scanf(" %c", &item);
                excluirElemento(&startPtr, item);
                exibirTodos(startPtr);
                break;
            case 12:
                printf("Digite o caractere para buscar: ");
                scanf(" %c", &item);
                LISTNODEPTR encontrado = buscar(startPtr, item);
                if (encontrado) {
                    printf("Elemento %c encontrado.\n", item);
                } else {
                    printf("Elemento %c não encontrado.\n", item);
                }
                break;
            default:
                printf("Escolha inválida!\n");
                break;
        }
        printf("? ");
        scanf("%d", &choice);
    }

    printf("Fim do Programa.\n");
    return 0;
}

/* Funções de manipulação da lista */
void criarLista(LISTNODEPTR *sPtr) {
    *sPtr = NULL;
    printf("Lista criada.\n");
}

void inserirNoInicio(LISTNODEPTR *sPtr, char value) {
    LISTNODEPTR newPtr = malloc(sizeof(LISTNODE));
    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextPtr = *sPtr;
        *sPtr = newPtr;
    } else {
        printf("Erro ao inserir no início.\n");
    }
}

void inserirNoFim(LISTNODEPTR *sPtr, char value) {
    LISTNODEPTR newPtr = malloc(sizeof(LISTNODE));
    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        if (*sPtr == NULL) {
            *sPtr = newPtr;
        } else {
            LISTNODEPTR current = *sPtr;
            while (current->nextPtr != NULL) {
                current = current->nextPtr;
            }
            current->nextPtr = newPtr;
        }
    } else {
        printf("Erro ao inserir no fim.\n");
    }
}

void inserirNoMeio(LISTNODEPTR *sPtr, char value, int posicao) {
    if (posicao <= 0) {
        inserirNoInicio(sPtr, value);
    } else {
        LISTNODEPTR newPtr = malloc(sizeof(LISTNODE));
        if (newPtr != NULL) {
            newPtr->data = value;
            LISTNODEPTR current = *sPtr;
            int i;

            for (i = 1; i < posicao && current != NULL; i++) {
                current = current->nextPtr;
            }

            if (current == NULL) {
                inserirNoFim(sPtr, value);
            } else {
                newPtr->nextPtr = current->nextPtr;
                current->nextPtr = newPtr;
            }
        } else {
            printf("Erro ao inserir no meio.\n");
        }
    }
}

void exibirPrimeiro(LISTNODEPTR sPtr) {
    if (sPtr != NULL) {
        printf("Primeiro elemento: %c\n", sPtr->data);
    } else {
        printf("A lista está vazia.\n");
    }
}

void exibirUltimo(LISTNODEPTR sPtr) {
    if (sPtr != NULL) {
        while (sPtr->nextPtr != NULL) {
            sPtr = sPtr->nextPtr;
        }
        printf("Último elemento: %c\n", sPtr->data);
    } else {
        printf("A lista está vazia.\n");
    }
}

void exibirTodos(LISTNODEPTR sPtr) {
    if (sPtr == NULL) {
        printf("A lista está vazia.\n");
    } else {
        printf("Lista: ");
        while (sPtr != NULL) {
            printf("%c -> ", sPtr->data);
            sPtr = sPtr->nextPtr;
        }
        printf("NULL\n");
    }
}

int tamanhoLista(LISTNODEPTR sPtr) {
    int count = 0;
    while (sPtr != NULL) {
        count++;
        sPtr = sPtr->nextPtr;
    }
    return count;
}

char excluirNoInicio(LISTNODEPTR *sPtr) {
    if (*sPtr == NULL) {
        printf("A lista está vazia.\n");
        return '\0';
    } else {
        LISTNODEPTR tempPtr = *sPtr;
        char valorRemovido = tempPtr->data;
        *sPtr = (*sPtr)->nextPtr;
        free(tempPtr);
        return valorRemovido;
    }
}

char excluirNoFim(LISTNODEPTR *sPtr) {
    if (*sPtr == NULL) {
        printf("A lista está vazia.\n");
        return '\0';
    } else {
        LISTNODEPTR current = *sPtr;
        LISTNODEPTR previous = NULL;

        while (current->nextPtr != NULL) {
            previous = current;
            current = current->nextPtr;
        }

        char valorRemovido = current->data;

        if (previous == NULL) {
            *sPtr = NULL;
        } else {
            previous->nextPtr = NULL;
        }

        free(current);
        return valorRemovido;
    }
}

char excluirElemento(LISTNODEPTR *sPtr, char value) {
    if (*sPtr == NULL) {
        printf("A lista está vazia.\n");
        return '\0';
    } else {
        LISTNODEPTR current = *sPtr;
        LISTNODEPTR previous = NULL;

        while (current != NULL && current->data != value) {
            previous = current;
            current = current->nextPtr;
        }

        if (current == NULL) {
            printf("Elemento %c não encontrado.\n", value);
            return '\0';
        } else {
            char valorRemovido = current->data;

            if (previous == NULL) {
                *sPtr = current->nextPtr;
            } else {
                previous->nextPtr = current->nextPtr;
            }

            free(current);
            return valorRemovido;
        }
    }
}

LISTNODEPTR buscar(LISTNODEPTR sPtr, char value) {
    while (sPtr != NULL && sPtr->data != value) {
        sPtr = sPtr->nextPtr;
    }
    return sPtr;
}

void instructions(void) {
    printf("Escolha uma opção:\n"
           "1 - Criar lista vazia\n"
           "2 - Inserir no início\n"
           "3 - Inserir no fim\n"
           "4 - Inserir no meio (posição)\n"
           "5 - Exibir primeiro elemento\n"
           "6 - Exibir último elemento\n"
           "7 - Exibir todos os elementos\n"
           "8 - Exibir tamanho da lista\n"
           "9 - Excluir primeiro elemento\n"
           "10 - Excluir último elemento\n"
           "11 - Excluir elemento específico\n"
           "12 - Buscar elemento\n"
           "0 - Sair\n");
}
