#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "client.h"

#define MAX_CAIXAS 4

typedef short int si;

typedef struct PriorQueue {
    Client *inicio;
    Client *fim;
} PriorQueue;

typedef struct Caixa {
    int id;
    bool estado;
    PriorQueue fila;
} Caixa;

    void initQueue(PriorQueue *fila);
    void initCaixa(Caixa *caixa, int id);
    si escolherCaixa(Caixa *caixas, si tipo);
    void cadastrar(PriorQueue *fila, Client* c);
    Client* remover(PriorQueue *fila);
    void imprimirfila(PriorQueue *fila);
    si EmptyQueue(PriorQueue *fila);
    si qteClients(PriorQueue *fila);
    bool existeCpf(Caixa *caixas, int numcaixas, char *cpf);
    void freeQueue(PriorQueue *fila);
    bool mercadoVazio(Caixa *caixas);

#endif