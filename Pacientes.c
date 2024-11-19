#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura Paciente
struct Paciente {
    int id;
    char nome[50];
    char dataNascimento[11]; // Formato: "DD/MM/AAAA"
    struct Paciente *proximo;
};

typedef struct Paciente PACIENTE;
typedef PACIENTE *PACIENTEPTR;

// Funções para o sistema de registro de pacientes
void cadastrarPaciente(PACIENTEPTR *inicio, int id, char nome[], char dataNascimento[]);
PACIENTEPTR buscarPaciente(PACIENTEPTR inicio, int id);
void removerPaciente(PACIENTEPTR *inicio, int id);
void listarPacientes(PACIENTEPTR inicio);
void exibirMenu();

int main() {
    PACIENTEPTR inicio = NULL;
    int escolha, id;
    char nome[50];
    char dataNascimento[11];

    // Loop do menu principal
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                printf("Digite o nome do paciente: ");
                scanf(" %[^\n]%*c", nome); // Lê uma linha inteira incluindo espaços
                printf("Digite a data de nascimento (DD/MM/AAAA): ");
                scanf("%s", dataNascimento);
                cadastrarPaciente(&inicio, id, nome, dataNascimento);
                break;
            case 2:
                printf("Digite o ID do paciente para busca: ");
                scanf("%d", &id);
                PACIENTEPTR pacienteEncontrado = buscarPaciente(inicio, id);
                if (pacienteEncontrado) {
                    printf("Paciente encontrado:\n");
                    printf("ID: %d | Nome: %s | Data de Nascimento: %s\n",
                           pacienteEncontrado->id, pacienteEncontrado->nome, pacienteEncontrado->dataNascimento);
                } else {
                    printf("Paciente com ID %d não encontrado.\n", id);
                }
                break;
            case 3:
                listarPacientes(inicio);
                break;
            case 4:
                printf("Digite o ID do paciente para remover: ");
                scanf("%d", &id);
                removerPaciente(&inicio, id);
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 5);

    return 0;
}

// Exibe o menu de opções
void exibirMenu() {
    printf("\nSistema de Registro de Pacientes\n");
    printf("1. Cadastrar paciente\n");
    printf("2. Buscar paciente por ID\n");
    printf("3. Listar todos os pacientes\n");
    printf("4. Remover paciente\n");
    printf("5. Sair\n");
}

// Cadastra um novo paciente na lista
void cadastrarPaciente(PACIENTEPTR *inicio, int id, char nome[], char dataNascimento[]) {
    PACIENTEPTR novoPaciente = malloc(sizeof(PACIENTE));
    if (novoPaciente == NULL) {
        printf("Erro ao alocar memória para novo paciente.\n");
        return;
    }
   
    novoPaciente->id = id;
    strcpy(novoPaciente->nome, nome);
    strcpy(novoPaciente->dataNascimento, dataNascimento);
    novoPaciente->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novoPaciente;
    } else {
        PACIENTEPTR atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoPaciente;
    }
    printf("Paciente cadastrado com sucesso.\n");
}

// Busca um paciente na lista pelo ID
PACIENTEPTR buscarPaciente(PACIENTEPTR inicio, int id) {
    PACIENTEPTR atual = inicio;
    while (atual != NULL && atual->id != id) {
        atual = atual->proximo;
    }
    return atual;
}

// Remove um paciente da lista pelo ID
void removerPaciente(PACIENTEPTR *inicio, int id) {
    if (*inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    PACIENTEPTR atual = *inicio;
    PACIENTEPTR anterior = NULL;

    // Verifica se o paciente a ser removido é o primeiro
    if (atual->id == id) {
        *inicio = atual->proximo;
        free(atual);
        printf("Paciente removido com sucesso.\n");
        return;
    }

    // Percorre a lista para encontrar o paciente
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Verifica se o paciente foi encontrado
    if (atual == NULL) {
        printf("Paciente não encontrado.\n");
        return;
    }

    anterior->proximo = atual->proximo;
    free(atual);
    printf("Paciente removido com sucesso.\n");
}

// Lista todos os pacientes cadastrados
void listarPacientes(PACIENTEPTR inicio) {
    if (inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    PACIENTEPTR atual = inicio;
    printf("\nLista de Pacientes:\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s | Data de Nascimento: %s\n", atual->id, atual->nome, atual->dataNascimento);
        atual = atual->proximo;
    }
}
