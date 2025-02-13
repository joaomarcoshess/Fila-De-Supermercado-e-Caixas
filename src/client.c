#include "client.h"
#include <string.h>
#include <ctype.h>

// Limpa o buffer de entrada para evitar problemas com entradas inválidas.
void esvaziar() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Solicita e valida o nome do cliente.
void cadnome(Client *c) {
    while (1) {
        printf("Nome do cliente: ");
        fgets(c->nome, 102, stdin);
        if (c->nome[strlen(c->nome) - 1] == '\n') {
            c->nome[strlen(c->nome) - 1] = '\0';
        } else {
            esvaziar(); 
        }
        if (strlen(c->nome) == 0) {
            printf("Erro: O nome não pode ser vazio. Tente novamente.\n");
        } else {
            break;
        }
    }
}

// Solicita e valida o CPF do cliente.
void cadcpf(Client *c) {
    while (1) {
        printf("CPF do cliente (apenas números): ");
        fgets(c->cpf, 13, stdin);
        if (c->cpf[strlen(c->cpf) - 1] == '\n') {
            c->cpf[strlen(c->cpf) - 1] = '\0';
        } else {
            esvaziar(); 
        }
        int valido = 1;
        if (strlen(c->cpf) != 11) {
            valido = 0;
        } else {
            for (int i = 0; i < 11; i++) {
                if (!isdigit(c->cpf[i])) {
                    valido = 0;
                    break;
                }
            }
        }

        if (!valido) {
            printf("Erro: CPF deve ter exatamente 11 dígitos numéricos. Tente novamente.\n");
        } else {
            break;
        }
    }
}

// Solicita e valida a prioridade do cliente.
void cadprior(Client *c) {
    while (1) {
        printf("Prioridade (1-Alta, 2-Média, 3-Baixa): ");
        int resultado = scanf("%hd", &c->prioridade);

        if (resultado != 1 || c->prioridade < 1 || c->prioridade > 3) {
            printf("Erro: Prioridade deve ser 1, 2 ou 3. Tente novamente.\n");
            esvaziar(); 
        } else {
            break;
        }
    }
}

// Solicita e valida a quantidade de itens do cliente.
void caditens(Client *c) {
    while (1) {
        printf("Quantidade de itens (1 a 300): ");
        int resultado = scanf("%hd", &c->itens);

        if (resultado != 1 || c->itens < 1 || c->itens > 300) {
            printf("Erro: A quantidade deve ser entre 1 e 300. Tente novamente.\n");
            esvaziar(); 
        } else {
            break;
        }
    }
}