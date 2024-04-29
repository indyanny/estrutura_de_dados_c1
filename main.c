#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct no {
    int dado;
    struct no *prox;
};

struct descritor {
    int dado;
    struct descritor *prox;
};

// Lista com descritor
struct descList {
    int count;
    struct descritor *d;
};

// Cria novo no
struct descritor *createNoDesc(int dado) {
    struct descritor *novoNo = malloc(sizeof(struct descritor));
    if (novoNo != NULL) {
        novoNo->dado = dado;
        novoNo->prox = NULL;
    }
    return novoNo;
}

// Coloca em ordem
void insertInList(struct descList *descList, int dado) {
    struct descritor *novoNo = createNoDesc(dado);
    if (novoNo == NULL) {
        printf("Erro: Memória não alocada!\n");
        return;
    }

    struct descritor *before = NULL;
    struct descritor *now = descList->d;

    while (now != NULL && now->dado < dado) {
        before = now;
        now = now->prox;
    }

    // Insere o elemento da lista
    if (before == NULL) {
        novoNo->prox = descList->d;
        descList->d = novoNo;
    } else {
        novoNo->prox = now;
        before->prox = novoNo;
    }

    descList->count++;
}

// Imprime listas
void printSimpleList(struct no *list){
    printf("\nElementos da lista encadeada: ");
    while(list != NULL){
        printf("%d ", list->dado);
        list = list->prox;
    }
    printf("\n");
}

void printList(struct descList *descList) {
    struct descritor *temp = descList->d;
    printf("Elementos da lista com descritor: ");
    while (temp != NULL) {
        printf("%d ", temp->dado);
        temp = temp->prox;
    }
    printf("\n");
}

// Libera memoria
void freeList(struct descList *descList) {
    struct descritor *temp;
    while (descList->d != NULL) {
        temp = descList->d;
        descList->d = descList->d->prox;
        free(temp);
    }
    descList->count = 0;
}

int main(int arg, char *argv[]) {
    int n, i;
    struct no *list = NULL;
    struct no *temp;
    struct descList descList;
    descList.d = NULL;
    descList.count = 0;

    srand(time(NULL));

    printf("Qual a quantidade de elementos que deseja inserir na lista? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        temp = malloc(sizeof(struct no));
        if (temp == NULL) {
            printf("Erro: Memória não alocada!\n");
            return 1;
        }

        temp->dado = rand() % 100;
        temp->prox = list;
        list = temp;
    }

    // Exporta
    temp = list;
    while (temp != NULL) {
        insertInList(&descList, temp->dado);
        temp = temp->prox;
    }

    printSimpleList(list);
    printList(&descList);

    // Calcula
    double sum = 0.0;
    temp = list;
    while (temp != NULL) {
        sum += temp->dado;
        temp = temp->prox;
    }
    double media = sum / descList.count;

    printf("Media da lista com descritor: %.2lf\n", media);

   //Remove
    struct descritor *before = NULL;
    struct descritor *now = descList.d;
    while (now != NULL && now->dado <= media) {
        before = now;
        now = now->prox;
    }
    if (before == NULL) {
        descList.d = now->prox;
    } else {
        before->prox = now->prox;
    }
    free(now);
    descList.count--;

    printList(&descList);
    freeList(&descList);

    //Libera memoria
    while (list != NULL) {
        temp = list;
        list = list->prox;
        free(temp);
    }

    return 0;
}

