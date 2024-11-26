//Sistema de Playlist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura de um n� da lista
typedef struct Node {
    char musica[100];       // Nome da m�sica
    struct Node *next;      // Ponteiro para a pr�xima m�sica
    struct Node *prev;      // Ponteiro para a m�sica anterior
} NODE;

// Fun��es para manipula��o da playlist
NODE *criarNo(char *musica);
NODE *adicionarMusica(NODE *head, char *musica);
NODE *removerMusica(NODE *head, char *musica);
void tocarMusicaAtual(NODE *current);
NODE *avancarMusica(NODE *current);
NODE *voltarMusica(NODE *current);
void exibirPlaylist(NODE *head);
void liberarPlaylist(NODE **head);

int main() {
	setlocale(LC_ALL,"Portuguese");
    NODE *playlist = NULL;   // Cabe�a da lista circular
    NODE *atual = NULL;      // M�sica atual

    int opcao;
    char nomeMusica[100];

    do {
        printf("\n--- Sistema de Playlist ---\n");
        printf("1. Adicionar m�sica\n");
        printf("2. Remover m�sica\n");
        printf("3. Tocar m�sica atual\n");
        printf("4. Avan�ar para a pr�xima m�sica\n");
        printf("5. Voltar para a m�sica anterior\n");
        printf("6. Exibir playlist\n");
        printf("7. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome da m�sica: ");
                scanf(" %[^\n]s", nomeMusica); // Ler string com espa�os
                playlist = adicionarMusica(playlist, nomeMusica);
                if (atual == NULL) {
                    atual = playlist; // Define a primeira m�sica como atual
                }
                break;
            case 2:
                printf("Digite o nome da m�sica para remover: ");
                scanf(" %[^\n]s", nomeMusica);
                playlist = removerMusica(playlist, nomeMusica);
                if (atual != NULL && strcmp(atual->musica, nomeMusica) == 0) {
                    atual = playlist; // Atualiza a m�sica atual
                }
                break;
            case 3:
                tocarMusicaAtual(atual);
                break;
            case 4:
                if (atual != NULL) {
                    atual = avancarMusica(atual);
                }
                break;
            case 5:
                if (atual != NULL) {
                    atual = voltarMusica(atual);
                }
                break;
            case 6:
                exibirPlaylist(playlist);
                break;
            case 7:
                printf("Encerrando o programa...\n");
                liberarPlaylist(&playlist);
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}

// Cria um novo n� com o nome da m�sica
NODE *criarNo(char *musica) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Mem�ria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->musica, musica);
    novoNo->next = novoNo;
    novoNo->prev = novoNo;
    return novoNo;
}

// Adiciona uma m�sica � playlist
NODE *adicionarMusica(NODE *head, char *musica) {
    NODE *novoNo = criarNo(musica);

    if (head == NULL) {
        return novoNo; // Primeiro n� na lista
    }

    NODE *ultimo = head->prev; // �ltimo n� da lista
    ultimo->next = novoNo;
    novoNo->prev = ultimo;
    novoNo->next = head;
    head->prev = novoNo;

    return head;
}

// Remove uma m�sica da playlist
NODE *removerMusica(NODE *head, char *musica) {
    if (head == NULL) {
        printf("Erro: Playlist vazia.\n");
        return NULL;
    }

    NODE *temp = head;

    do {
        if (strcmp(temp->musica, musica) == 0) {
            if (temp->next == temp) { // Caso especial: �nico n� na lista
                free(temp);
                return NULL;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            if (temp == head) {
                head = temp->next; // Atualiza o head se necess�rio
            }

            free(temp);
            printf("M�sica '%s' removida com sucesso.\n", musica);
            return head;
        }
        temp = temp->next;
    } while (temp != head);

    printf("M�sica '%s' n�o encontrada na playlist.\n", musica);
    return head;
}

// Toca a m�sica atual
void tocarMusicaAtual(NODE *current) {
    if (current == NULL) {
        printf("Erro: Nenhuma m�sica na playlist.\n");
        return;
    }
    printf("Tocando agora: %s\n", current->musica);
}

// Avan�a para a pr�xima m�sica
NODE *avancarMusica(NODE *current) {
    printf("Avan�ando para: %s\n", current->next->musica);
    return current->next;
}

// Volta para a m�sica anterior
NODE *voltarMusica(NODE *current) {
    printf("Voltando para: %s\n", current->prev->musica);
    return current->prev;
}

// Exibe todas as m�sicas na playlist
void exibirPlaylist(NODE *head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    NODE *temp = head;
    printf("Playlist:\n");
    do {
        printf("- %s\n", temp->musica);
        temp = temp->next;
    } while (temp != head);
}

// Libera toda a mem�ria alocada para a playlist
void liberarPlaylist(NODE **head) {
    if (*head == NULL) {
        return;
    }

    NODE *temp = *head;
    NODE *prox;

    do {
        prox = temp->next;
        free(temp);
        temp = prox;
    } while (temp != *head);

    *head = NULL;
    printf("Playlist liberada com sucesso.\n");
}
