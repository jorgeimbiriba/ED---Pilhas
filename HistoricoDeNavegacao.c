#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura do nó da lista duplamente encadeada
typedef struct Node {
    char url[100];         // URL da página
    struct Node *next;     // Ponteiro para o próximo nó
    struct Node *prev;     // Ponteiro para o nó anterior
} NODE;

// Funções para manipular o histórico
NODE *criarNo(char *url);
void visitarPagina(NODE **head, NODE **current, char *url);
void voltarPagina(NODE **current);
void avancarPagina(NODE **current);
void exibirPaginaAtual(NODE *current);
void liberarHistorico(NODE **head);

int main() {
	setlocale(LC_ALL,"Portuguese");
    NODE *head = NULL;    // Ponteiro para o início do histórico
    NODE *current = NULL; // Ponteiro para a página atual

    int opcao;
    char url[100];

    do {
        printf("\n--- Histórico de Navegação ---\n");
        printf("1. Visitar nova página\n");
        printf("2. Voltar\n");
        printf("3. Avançar\n");
        printf("4. Exibir página atual\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a URL da nova página: ");
                scanf("%s", url);
                visitarPagina(&head, &current, url);
                break;
            case 2:
                voltarPagina(&current);
                break;
            case 3:
                avancarPagina(&current);
                break;
            case 4:
                exibirPaginaAtual(current);
                break;
            case 5:
                printf("Saindo...\n");
                liberarHistorico(&head);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}

// Cria um novo nó com a URL fornecida
NODE *criarNo(char *url) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->url, url);
    novoNo->next = NULL;
    novoNo->prev = NULL;
    return novoNo;
}

// Visita uma nova página e adiciona ao histórico
void visitarPagina(NODE **head, NODE **current, char *url) {
    NODE *novoNo = criarNo(url);

    if (*current != NULL) {
        // Se já houver uma página atual, desconecta o histórico futuro
        (*current)->next = NULL;
        novoNo->prev = *current;
    } else if (*head == NULL) {
        // Caso seja a primeira página visitada
        *head = novoNo;
    }

    *current = novoNo; // Atualiza a página atual
    printf("Você visitou: %s\n", url);
}

// Volta para a página anterior, se existir
void voltarPagina(NODE **current) {
    if (*current == NULL || (*current)->prev == NULL) {
        printf("Não é possível voltar. Já está na primeira página.\n");
        return;
    }
    *current = (*current)->prev;
    printf("Você voltou para: %s\n", (*current)->url);
}

// Avança para a próxima página, se existir
void avancarPagina(NODE **current) {
    if (*current == NULL || (*current)->next == NULL) {
        printf("Não é possível avançar. Já está na última página.\n");
        return;
    }
    *current = (*current)->next;
    printf("Você avançou para: %s\n", (*current)->url);
}

// Exibe a página atual
void exibirPaginaAtual(NODE *current) {
    if (current == NULL) {
        printf("Nenhuma página visitada.\n");
        return;
    }
    printf("Página atual: %s\n", current->url);
}

// Libera toda a memória alocada para o histórico
void liberarHistorico(NODE **head) {
    NODE *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    printf("Histórico liberado com sucesso.\n");
}
