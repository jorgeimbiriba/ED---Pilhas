#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura Produto
struct Produto {
    int codigo;
    char nome[50];
    int quantidade;
    struct Produto *proximo;
};

typedef struct Produto PRODUTO;
typedef PRODUTO *PRODUTOPTR;

// Funções para o sistema de gerenciamento de estoque
void adicionarProduto(PRODUTOPTR *inicio, int codigo, char nome[], int quantidade);
void atualizarProduto(PRODUTOPTR inicio, int codigo, int novaQuantidade);
void listarProdutos(PRODUTOPTR inicio);
void removerProduto(PRODUTOPTR *inicio, int codigo);
PRODUTOPTR buscarProduto(PRODUTOPTR inicio, int codigo);
void exibirMenu();

int main() {
    PRODUTOPTR inicio = NULL;
    int escolha, codigo, quantidade;
    char nome[50];

    // Loop do menu principal
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o código do produto: ");
                scanf("%d", &codigo);
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]%*c", nome);  // Lê uma linha inteira incluindo espaços
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                adicionarProduto(&inicio, codigo, nome, quantidade);
                break;
            case 2:
                printf("Digite o código do produto para atualizar: ");
                scanf("%d", &codigo);
                printf("Digite a nova quantidade: ");
                scanf("%d", &quantidade);
                atualizarProduto(inicio, codigo, quantidade);
                break;
            case 3:
                listarProdutos(inicio);
                break;
            case 4:
                printf("Digite o código do produto para remover: ");
                scanf("%d", &codigo);
                removerProduto(&inicio, codigo);
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
    printf("\nSistema de Gerenciamento de Estoque\n");
    printf("1. Adicionar produto\n");
    printf("2. Atualizar quantidade de produto\n");
    printf("3. Listar todos os produtos\n");
    printf("4. Remover produto\n");
    printf("5. Sair\n");
}

// Adiciona um novo produto à lista
void adicionarProduto(PRODUTOPTR *inicio, int codigo, char nome[], int quantidade) {
    PRODUTOPTR novoProduto = malloc(sizeof(PRODUTO));
    if (novoProduto == NULL) {
        printf("Erro ao alocar memória para novo produto.\n");
        return;
    }
   
    novoProduto->codigo = codigo;
    strcpy(novoProduto->nome, nome);
    novoProduto->quantidade = quantidade;
    novoProduto->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novoProduto;
    } else {
        PRODUTOPTR atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoProduto;
    }
    printf("Produto adicionado com sucesso.\n");
}

// Atualiza a quantidade de um produto existente
void atualizarProduto(PRODUTOPTR inicio, int codigo, int novaQuantidade) {
    PRODUTOPTR produto = buscarProduto(inicio, codigo);
    if (produto != NULL) {
        produto->quantidade = novaQuantidade;
        printf("Quantidade do produto atualizado com sucesso.\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

// Lista todos os produtos no estoque
void listarProdutos(PRODUTOPTR inicio) {
    if (inicio == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    PRODUTOPTR atual = inicio;
    printf("\nLista de Produtos:\n");
    while (atual != NULL) {
        printf("Código: %d | Nome: %s | Quantidade: %d\n", atual->codigo, atual->nome, atual->quantidade);
        atual = atual->proximo;
    }
}

// Remove um produto da lista pelo código
void removerProduto(PRODUTOPTR *inicio, int codigo) {
    if (*inicio == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    PRODUTOPTR atual = *inicio;
    PRODUTOPTR anterior = NULL;

    // Verifica se o produto a ser removido é o primeiro
    if (atual->codigo == codigo) {
        *inicio = atual->proximo;
        free(atual);
        printf("Produto removido com sucesso.\n");
        return;
    }

    // Percorre a lista para encontrar o produto
    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Verifica se o produto foi encontrado
    if (atual == NULL) {
        printf("Produto não encontrado.\n");
        return;
    }

    anterior->proximo = atual->proximo;
    free(atual);
    printf("Produto removido com sucesso.\n");
}

// Busca um produto na lista pelo código
PRODUTOPTR buscarProduto(PRODUTOPTR inicio, int codigo) {
    PRODUTOPTR atual = inicio;
    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->proximo;
    }
    return atual;
}
