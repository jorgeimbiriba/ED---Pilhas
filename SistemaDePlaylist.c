//Sistema de Playlist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura de um nó da lista
typedef struct Node {
    char musica[100];       // Nome da música
    struct Node *next;      // Ponteiro para a próxima música
    struct Node *prev;      // Ponteiro para a música anterior
} NODE;

// Funções para manipulação da playlist
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
    NODE *playlist = NULL;   // Cabeça da lista circular
    NODE *atual = NULL;      // Música atual

    int opcao;
    char nomeMusica[100];

    do {
        printf("\n--- Sistema de Playlist ---\n");
        printf("1. Adicionar música\n");
        printf("2. Remover música\n");
        printf("3. Tocar música atual\n");
        printf("4. Avançar para a próxima música\n");
        printf("5. Voltar para a música anterior\n");
        printf("6. Exibir playlist\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome da música: ");
                scanf(" %[^\n]s", nomeMusica); // Ler string com espaços
                playlist = adicionarMusica(playlist, nomeMusica);
                if (atual == NULL) {
                    atual = playlist; // Define a primeira música como atual
                }
                break;
            case 2:
                printf("Digite o nome da música para remover: ");
                scanf(" %[^\n]s", nomeMusica);
                playlist = removerMusica(playlist, nomeMusica);
                if (atual != NULL && strcmp(atual->musica, nomeMusica) == 0) {
                    atual = playlist; // Atualiza a música atual
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
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}

// Cria um novo nó com o nome da música
NODE *criarNo(char *musica) {
    NODE *novoNo = (NODE *)malloc(sizeof(NODE));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->musica, musica);
    novoNo->next = novoNo;
    novoNo->prev = novoNo;
    return novoNo;
}

// Adiciona uma música à playlist
NODE *adicionarMusica(NODE *head, char *musica) {
    NODE *novoNo = criarNo(musica);

    if (head == NULL) {
        return novoNo; // Primeiro nó na lista
    }

    NODE *ultimo = head->prev; // Último nó da lista
    ultimo->next = novoNo;
    novoNo->prev = ultimo;
    novoNo->next = head;
    head->prev = novoNo;

    return head;
}

// Remove uma música da playlist
NODE *removerMusica(NODE *head, char *musica) {
    if (head == NULL) {
        printf("Erro: Playlist vazia.\n");
        return NULL;
    }

    NODE *temp = head;

    do {
        if (strcmp(temp->musica, musica) == 0) {
            if (temp->next == temp) { // Caso especial: único nó na lista
                free(temp);
                return NULL;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            if (temp == head) {
                head = temp->next; // Atualiza o head se necessário
            }

            free(temp);
            printf("Música '%s' removida com sucesso.\n", musica);
            return head;
        }
        temp = temp->next;
    } while (temp != head);

    printf("Música '%s' não encontrada na playlist.\n", musica);
    return head;
}

// Toca a música atual
void tocarMusicaAtual(NODE *current) {
    if (current == NULL) {
        printf("Erro: Nenhuma música na playlist.\n");
        return;
    }
    printf("Tocando agora: %s\n", current->musica);
}

// Avança para a próxima música
NODE *avancarMusica(NODE *current) {
    printf("Avançando para: %s\n", current->next->musica);
    return current->next;
}

// Volta para a música anterior
NODE *voltarMusica(NODE *current) {
    printf("Voltando para: %s\n", current->prev->musica);
    return current->prev;
}

// Exibe todas as músicas na playlist
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

// Libera toda a memória alocada para a playlist
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
