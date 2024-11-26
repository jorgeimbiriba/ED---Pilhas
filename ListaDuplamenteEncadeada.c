#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó na lista duplamente encadeada
typedef struct Node {
    int data;
    struct Node *next; // Ponteiro para o próximo nó
    struct Node *prev; // Ponteiro para o nó anterior
} NODE;

// Função para criar um novo nó
NODE *criarNo(int valor) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->data = valor;
    novoNo->next = NULL;
    novoNo->prev = NULL;
    return novoNo;
}

//Inserir no início
NODE *inserirNoInicio(NODE *head, int valor) {
    NODE *novoNo = criarNo(valor);
    if (head != NULL) {
        head->prev = novoNo;
    }
    novoNo->next = head;
    return novoNo; // O novo nó se torna o head
}

//Inserir no fim
NODE *inserirNoFim(NODE *head, int valor) {
    NODE *novoNo = criarNo(valor);
    if (head == NULL) {
        return novoNo; // Lista estava vazia
    }
    NODE *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = novoNo;
    novoNo->prev = temp;
    return head; // O head não muda
}

//Remover do início
NODE *removerDoInicio(NODE *head) {
    if (head == NULL) {
        printf("Erro: Lista vazia.\n");
        return NULL;
    }
    NODE *temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    return head;
}

//Remover do final
NODE *removerDoFim(NODE *head) {
    if (head == NULL) {
        printf("Erro: Lista vazia.\n");
        return NULL;
    }
    NODE *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        head = NULL; // Lista fica vazia
    }
    free(temp);
    return head;
}

//Exibir na ordem normal
void exibirLista(NODE *head) {
    printf("Lista: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

//Exibir na ordem reversa
void exibirListaReversa(NODE *head) {
    if (head == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    // Ir até o último nó
    while (head->next != NULL) {
        head = head->next;
    }
    // Exibir da direita para a esquerda
    printf("Lista (reversa): ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->prev;
    }
    printf("\n");
}

int main() {
    NODE *head = NULL;

    printf("Inserindo elementos no início:\n");
    head = inserirNoInicio(head, 10);
    head = inserirNoInicio(head, 20);
    head = inserirNoInicio(head, 30);
    exibirLista(head);

    printf("\nInserindo elementos no fim:\n");
    head = inserirNoFim(head, 40);
    head = inserirNoFim(head, 50);
    exibirLista(head);

    printf("\nRemovendo elemento do início:\n");
    head = removerDoInicio(head);
    exibirLista(head);

    printf("\nRemovendo elemento do fim:\n");
    head = removerDoFim(head);
    exibirLista(head);

    printf("\nExibindo lista na ordem reversa:\n");
    exibirListaReversa(head);

    return 0;
}
