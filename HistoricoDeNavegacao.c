#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura do n� da lista duplamente encadeada
typedef struct Node {
    char url[100];         // URL da p�gina
    struct Node *next;     // Ponteiro para o pr�ximo n�
    struct Node *prev;     // Ponteiro para o n� anterior
} NODE;

// Fun��es para manipular o hist�rico
NODE *criarNo(char *url);
void visitarPagina(NODE **head, NODE **current, char *url);
void voltarPagina(NODE **current);
void avancarPagina(NODE **current);
void exibirPaginaAtual(NODE *current);
void liberarHistorico(NODE **head);

int main() {
	setlocale(LC_ALL,"Portuguese");
    NODE *head = NULL;    // Ponteiro para o in�cio do hist�rico
    NODE *current = NULL; // Ponteiro para a p�gina atual

    int opcao;
    char url[100];

    do {
        printf("\n--- Hist�rico de Navega��o ---\n");
        printf("1. Visitar nova p�gina\n");
        printf("2. Voltar\n");
        printf("3. Avan�ar\n");
        printf("4. Exibir p�gina atual\n");
        printf("5. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a URL da nova p�gina: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}

// Cria um novo n� com a URL fornecida
NODE *criarNo(char *url) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Mem�ria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->url, url);
    novoNo->next = NULL;
    novoNo->prev = NULL;
    return novoNo;
}

// Visita uma nova p�gina e adiciona ao hist�rico
void visitarPagina(NODE **head, NODE **current, char *url) {
    NODE *novoNo = criarNo(url);

    if (*current != NULL) {
        // Se j� houver uma p�gina atual, desconecta o hist�rico futuro
        (*current)->next = NULL;
        novoNo->prev = *current;
    } else if (*head == NULL) {
        // Caso seja a primeira p�gina visitada
        *head = novoNo;
    }

    *current = novoNo; // Atualiza a p�gina atual
    printf("Voc� visitou: %s\n", url);
}

// Volta para a p�gina anterior, se existir
void voltarPagina(NODE **current) {
    if (*current == NULL || (*current)->prev == NULL) {
        printf("N�o � poss�vel voltar. J� est� na primeira p�gina.\n");
        return;
    }
    *current = (*current)->prev;
    printf("Voc� voltou para: %s\n", (*current)->url);
}

// Avan�a para a pr�xima p�gina, se existir
void avancarPagina(NODE **current) {
    if (*current == NULL || (*current)->next == NULL) {
        printf("N�o � poss�vel avan�ar. J� est� na �ltima p�gina.\n");
        return;
    }
    *current = (*current)->next;
    printf("Voc� avan�ou para: %s\n", (*current)->url);
}

// Exibe a p�gina atual
void exibirPaginaAtual(NODE *current) {
    if (current == NULL) {
        printf("Nenhuma p�gina visitada.\n");
        return;
    }
    printf("P�gina atual: %s\n", current->url);
}

// Libera toda a mem�ria alocada para o hist�rico
void liberarHistorico(NODE **head) {
    NODE *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    printf("Hist�rico liberado com sucesso.\n");
}
