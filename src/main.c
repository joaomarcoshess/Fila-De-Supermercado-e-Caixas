#include "queue.h"
#include "client.h"

int main() {
    
    printf("Sistema de caixa para supermercado\n");
    printf("O sistema inicial começa com 4 caixas, sendo necessario pelo menos 1 funcionando.\n");
    if (MAX_CAIXAS <= 0) {
        printf("O supermercado deve ter ao menos 1 caixa. Altere o valor de MAX_CAIXAS.\n");
        return 0;
    }
    Caixa caixas[MAX_CAIXAS];
    for (int i = 0; i < MAX_CAIXAS; i++) {
        initCaixa(&caixas[i], i+1);
    }
    
    printf("\n");
    si opcao, caixa, resultado=0, caixasAtivos = MAX_CAIXAS;
    int destino;
    Client *novo = (Client*) malloc(sizeof(Client));

    while (1) {
        do {
            printf("\n~~~~~ Menu de Opçoes ~~~~~\n");
            printf("1. Cadastrar Novo Cliente\n");
            printf("2. Chamar Próximo Cliente\n");
            printf("3. Encerrar Expediente do Caixa\n");
            printf("4. Iniciar Expediente do Caixa\n");
            printf("5. Ver Lista de Clientes Aguardando\n");
            printf("6. Ver Situação dos Caixas\n");
            printf("0. Sair do Sistema\n");
            printf("\nDigite a opção desejada: ");
            resultado = scanf("%hd", &opcao);

            if (resultado != 1) {
                printf("Erro: Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); 
            }
        } while (resultado != 1);

        switch(opcao) {
            case 1:
                esvaziar();
                printf("\n");
                cadnome(novo);
                do {
                    cadcpf(novo);
                    resultado = 2;
                    if (existeCpf(caixas, MAX_CAIXAS, novo->cpf)) {
                        printf ("O cpf %s ja foi cadastrado. Insira outro valor.\n",novo->cpf);
                        resultado = 1;
                    }
                } while (resultado !=2);
                cadprior(novo);
                caditens(novo);
                caixa = escolherCaixa(caixas, 1);
                cadastrar(&caixas[caixa].fila, novo);
                printf("\nCliente cadastrado\nNome: %s // CPF: %s // ",novo->nome,novo->cpf);
                printf("Prioridade: %hd // Itens: %hd // Caixa: %hd\n",novo->prioridade,novo->itens,caixa+1);
                break;
            case 2:
                if (mercadoVazio(caixas))
                    printf("\nNao ha clientes em espera para serem atendidos no mercado.\n");
                else {
                    caixa = escolherCaixa(caixas, 2);
                    novo = remover(&caixas[caixa].fila);
                    printf("\nCliente atendido\nNome: %s // CPF: %s, ",novo->nome,novo->cpf);
                    printf("Prioridade: %hd, Itens: %hd, Caixa: %hd\n",novo->prioridade,novo->itens,caixa+1);
                }
                break;
            case 3:
                if (caixasAtivos == 1)
                    printf("Ha ao menos um caixa ativo.\n");
                else {
                    caixa = escolherCaixa(caixas, 3);
                    caixasAtivos--;
                    caixas[caixa].estado = false;
                    if (EmptyQueue(&caixas[caixa].fila))
                        printf("\nCaixa %hd fechado, sem clientes.\n",caixa+1);
                    else {
                        destino = -1;
                        for (int i=0; i<MAX_CAIXAS; i++) {
                            if (caixas[i].estado) {
                                if (destino == -1 || qteClients(&caixas[i].fila) < qteClients(&caixas[destino].fila)) {
                                    destino = i;
                                }
                            }
                        }
                        while (!EmptyQueue(&caixas[caixa].fila)) {
                            cadastrar(&caixas[destino].fila, remover(&caixas[caixa].fila));
                        }
                        printf("\nCaixa %hd fechado e os clientes ordenados pra fila do caixa %d.\n",caixa+1,destino+1);
                    }
                }
                break;
            case 4:
                if (caixasAtivos == MAX_CAIXAS)
                    printf("\nTodos os caixas ja estao abertos.\n");
                else {
                    caixa = escolherCaixa(caixas, 4);
                    caixasAtivos++;
                    caixas[caixa].estado = true;
                    printf("\nO caixa %hd foi aberto.\n",caixa+1);
                }
                break;
            case 5:
                printf("\n~~~ Dados dos clientes esperando: ~~~\n");
                if (mercadoVazio(caixas))
                    printf("\n~~~ Sem clientes em espera no mercado. ~~~\n");
                else {
                    for (int i=0; i<MAX_CAIXAS; i++) {
                        if (caixas[i].estado && caixas[i].fila.inicio != NULL) {
                            printf("\n------ CAIXA %hd ------\n",caixas[i].id);
                            imprimirfila(&caixas[i].fila);
                        }
                    }
                }
                break;
            case 6:
                printf("\nStatus - Caixas\n");
                for (int i=0; i<MAX_CAIXAS; i++) {
                    if (!caixas[i].estado)
                        printf("\n~~~ Caixa %hd fechado, sem clientes esperando. ~~~\n",caixas[i].id);
                    else if (caixas[i].fila.inicio == NULL)
                        printf("\n~~~ Caixa %hd aberto, sem clientes. ~~~\n",caixas[i].id);
                    else {
                        if (qteClients(&caixas[i].fila) == 1) {
                            printf("\n~~~ Caixa %hd aberto, %hd cliente. ~~~\n",caixas[i].id,qteClients(&caixas[i].fila));
                        }
                        else {
                            printf("\n~~~ Caixa %hd aberto, %hd clientes. ~~~\n",caixas[i].id,qteClients(&caixas[i].fila));
                        }
                    }
                }
                break;
            case 0:
                for (int i = 0; i < MAX_CAIXAS; i++) {
                    freeQueue(&caixas[i].fila);
                }
                return 0;
            default:
                printf("Erro. Escolha um número entre 0 a 6.\n");
                break;
        }
    }
}
