#include "queue.h"

// Inicializa uma fila de prioridade, definindo o início e o fim como NULL.
void initQueue(PriorQueue *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Inicializa um caixa, definindo seu ID, estado (aberto) e inicializando sua fila de clientes.
void initCaixa(Caixa *caixa, int id) {
    caixa->id = id;
    caixa->estado = true;
    initQueue(&(caixa->fila));
}

// Permite ao usuário escolher um caixa com base no tipo de operação (inserir cliente, atender, fechar ou abrir caixa).
si escolherCaixa(Caixa *caixas, si tipo) {
    int resultado;
    si numcaixa;

    do {
        if (tipo == 4) {
            printf("\nCaixas fechados: ");
            for (int i=0; i < MAX_CAIXAS; i++)
            {
                if (!caixas[i].estado)
                    printf("%d   ",i+1);
            }
        }
        else if (tipo == 2) {
            printf("\nCaixas com clientes em espera: ");
            for (int i=0; i < MAX_CAIXAS; i++)
            {
                if (caixas[i].estado && qteClients(&caixas[i].fila) > 0)
                    printf("%d  ",i+1);
            }
        }
        else {
            printf("\nCaixas abertos: ");
            for (int i=0; i < MAX_CAIXAS; i++)
            {
                if (caixas[i].estado)
                    printf("%d  ",i+1);
            }
        }

        if (tipo == 1)
            printf("\nEscolha um caixa para inserir cliente: ");
        else if (tipo == 2)
            printf("\nEscolha um caixa para fazer atendimento: ");
        else if (tipo == 3)
            printf("\nEscolha um caixa para fechar: ");
        else
            printf("\nEscolha um caixa para abrir: ");
        resultado = scanf("%hd", &numcaixa);

        if (tipo == 4) {
            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n');
            } else if (caixas[numcaixa-1].estado || numcaixa < 1 || numcaixa > 5) {
                printf("Erro: Escolha um caixa disponivel.\n");
                resultado = 0;
            }
        }
        else if (tipo == 2) {
            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n');
            } else if (!caixas[numcaixa-1].estado || qteClients(&caixas[numcaixa-1].fila) == 0 || numcaixa < 1 || numcaixa > 5) {
                printf("Erro: Escolha um caixa disponivel.\n");
                resultado = 0;
            }
        }
        else {
            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n');
            } else if (!caixas[numcaixa-1].estado || numcaixa < 1 || numcaixa > 5) {
                printf("Erro: Escolha um caixa disponivel.\n");
                resultado = 0;
            }
        }
    } while (resultado != 1);

    return numcaixa-1;
}

// Cadastra um cliente na fila de prioridade, inserindo-o na posição correta com base na prioridade.
void cadastrar(PriorQueue *fila, Client *c) {
    Client *f = (Client*) malloc(sizeof(Client));
    Client *aux = fila->inicio;
    strcpy(f->nome, c->nome);
    strcpy(f->cpf, c->cpf);
    f->prioridade = c->prioridade;
    f->itens = c->itens;
    f->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = f;
        fila->fim = f;
    }
    else if (fila->fim->prioridade == 1) {
        fila->fim->prox = f;
        fila->fim = f;
    }
    else if (fila->fim->prioridade == 2) {
        if (c->prioridade == 2 || c->prioridade == 3) {
            fila->fim->prox = f;
            fila->fim = f;
        }
        else {
            while (aux != NULL)
            {
                if (aux->prioridade == 2 && aux == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (aux->prox->prioridade == 2) {
                    f->prox = aux->prox;
                    aux->prox = f;
                    break;
                }
                aux = aux->prox;
            }
        }
    }
    else {
        if (c->prioridade == 3) {
            fila->fim->prox = f;
            fila->fim = f;
        }
        else if (c->prioridade == 2) {
            while (aux != NULL)
            {
                if (aux->prioridade == 3 && aux == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (aux->prox->prioridade == 3) {
                    f->prox = aux->prox;
                    aux->prox = f;
                    break;
                }
                aux = aux->prox;
            }
        }
        else {
            while (aux != NULL)
            {
                if (aux->prioridade == 2 && aux == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (aux->prioridade == 3 && aux == fila->inicio) {
                    f->prox = fila->inicio;
                    fila->inicio = f;
                    break;
                }
                else if (aux->prox->prioridade == 2) {
                    f->prox = aux->prox;
                    aux->prox = f;
                    break;
                }
                else if (aux->prox->prioridade == 3) {
                    f->prox = aux->prox;
                    aux->prox = f;
                    break;
                }
                aux = aux->prox;
            }
        }
    }
}

// Imprime todos os clientes na fila, mostrando suas informações (prioridade, nome, CPF e quantidade de itens).
void imprimirfila(PriorQueue *fila) {
    Client *aux = fila->inicio;
    si cl = 1;
    while (aux != NULL) {
        printf("\nCliente número %hd -> ",cl);
        printf("Prioridade: %hd / ",aux->prioridade);
        printf("Nome: %s / ",aux->nome);
        printf("CPF: %c%c%c.%c%c%c.%c%c%c-%c%c / ", 
               aux->cpf[0], aux->cpf[1], aux->cpf[2], 
               aux->cpf[3], aux->cpf[4], aux->cpf[5], 
               aux->cpf[6], aux->cpf[7], aux->cpf[8], 
               aux->cpf[9], aux->cpf[10]);
        printf("Itens: %hd\n",aux->itens);
        aux = aux->prox;
        cl++;
    }
    printf("\n");
}

// Remove o primeiro cliente da fila e retorna seus dados.
Client* remover(PriorQueue *fila) {
    Client *f = (Client*) malloc(sizeof(Client));
    Client *removido = fila->inicio;
    strcpy(f->nome, removido->nome);
    strcpy(f->cpf, removido->cpf);
    f->prioridade = removido->prioridade;
    f->itens = removido->itens;
    fila->inicio = removido->prox;
    
    free(removido);
    return f;
}

// Verifica se a fila está vazia.
si EmptyQueue(PriorQueue *fila) {
    return fila->inicio == NULL;
}

// Retorna a quantidade de clientes na fila.
si qteClients(PriorQueue *fila) {
    Client *aux = fila->inicio;
    si cl = 0;
    while (aux != NULL) {
        aux = aux->prox;
        cl++;
    }
    return cl;
}

// Verifica se um CPF já existe em qualquer uma das filas dos caixas.
bool existeCpf(Caixa *caixas, int numcaixas, char *cpf) {
    for (int i = 0; i < numcaixas; i++) {
        Client *aux = caixas[i].fila.inicio;
        
        while (aux != NULL) {
            if (strcmp(cpf, aux->cpf) == 0) {
                return true;
            }
            aux = aux->prox;
        }
    }
    return false;
}

// Libera toda a memória alocada para a fila, removendo todos os clientes.
void freeQueue(PriorQueue *fila) {
    Client *aux = fila->inicio;
    while (aux != NULL) {
        Client *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Verifica se todos os caixas estão vazios (sem clientes em espera).
bool mercadoVazio(Caixa* caixas) {
    int quant = 0;
    for (int i = 0; i < MAX_CAIXAS; i++) {
        quant = qteClients(&caixas[i].fila);
        if (quant > 0) {
            return false;
        }
    }
    return true;
}