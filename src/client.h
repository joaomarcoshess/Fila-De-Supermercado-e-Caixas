#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>

typedef short int si;

typedef struct Client {
	char nome[102];
	char cpf[13];
	si prioridade;
	si itens;
	struct Client *prox;
} Client;

void esvaziar();
void cadnome(Client *c);
void cadcpf(Client *c);
void cadprior(Client *c);
void caditens(Client *c);

#endif