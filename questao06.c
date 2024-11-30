#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int dado;
	struct No *proximo; //Ponteiro que aponta pro pr�ximo n�
}No;

// Fun��o para criar um novo n�
No* criaNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No)); //Aloca��o Din�mica
    
    if (novoNo == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(1);
    }
    
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

//Insere um n� no in�cio da lista
void insereInicio(No** topo, int dado) {
    No* novoNo = criaNo(dado); // Cria o novo n�
    novoNo->proximo = *topo; // Aponta para o n� atual que � a cabe�a
    *topo = novoNo;          // Atualiza a cabe�a para o novo n�
}

// Fun��o para exibir os elementos da lista
void exibeLista(No* topo) {
    No* atual = topo;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}


int main() {
    No* lista = NULL; // Inicializa a lista como vazia
    int valor;

    printf("Digite valores para inserir na lista (digite -1 para sair):\n");
    while (1) {
        printf("Digite um valor inteiro: ");
        scanf("%d", &valor);
        if (valor == -1) {
            break; // Encerra o programa se o usu�rio digitar -1
        }
        insereInicio(&lista, valor); // Insere o valor no in�cio da lista
        exibeLista(lista);           // Exibe a lista atualizada
    }

    // Libera a mem�ria dos n�s antes de sair
    No* atual = lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    printf("Programa encerrado.\n");
    
    return 0;
}
