#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"  // Inclui o cabeçalho do arquivo "cliente.h" para ter acesso à definição da estrutura Cliente.

// Função para adicionar um novo cliente ao vetor de clientes.
void novo_cliente(struct Cliente *clientes, int *numClientes) {
    if (*numClientes < 100) {  // Verifica se o número de clientes não atingiu o limite de 100.
        struct Cliente novo;  // Declara uma variável 'novo' do tipo Cliente para armazenar o novo cliente.
        printf("CPF: ");
        scanf("%s", novo.cpf);
        printf("Nome: ");
        scanf("%s", novo.nome);
        printf("Saldo inicial: ");
        scanf("%f", &novo.saldo);
        printf("Senha: ");
        scanf("%s", novo.senha);
        printf("Tipo de conta (Comum ou Plus): ");
        scanf("%s", novo.tipo_conta);

        clientes[*numClientes] = novo;  // Adiciona o novo cliente ao vetor de clientes na posição indicada por 'numClientes'.
        (*numClientes)++;  // Incrementa o número de clientes.

        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Limite de clientes atingido.\n");  // Mensagem de erro se o limite de clientes for atingido.
    }
}

// Função para remover um cliente com base no CPF fornecido.
void apaga_cliente(struct Cliente *clientes, int *numClientes) {
    char cpf[12];
    printf("CPF do cliente a ser removido: ");
    scanf("%s", cpf);

    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  // Verifica se o CPF fornecido coincide com o CPF de algum cliente.
            for (int j = i; j < *numClientes - 1; j++) {
                clientes[j] = clientes[j + 1];  // Move os clientes seguintes para ocupar a posição do cliente removido.
            }
            (*numClientes)--;  // Decrementa o número de clientes.
            printf("Cliente removido com sucesso!\n");
            return;
        }
    }
    printf("CPF não encontrado.\n");  // Mensagem de erro se o CPF não for encontrado.
}

// Função para listar todos os clientes e seus dados.
void listar_clientes(struct Cliente *clientes, int numClientes) {
    printf("Lista de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
        printf("Saldo: R$ %.2f\n", clientes[i].saldo);
        printf("Saldo da conta poupança: R$ %.2f\n", clientes[i].saldo_poupanca);
        printf("------------------\n");
    }
}

// Função para realizar um débito na conta de um cliente.
void debito(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  // Verifica se o CPF fornecido coincide com o CPF de algum cliente.
            char senha[50];
            printf("Senha: ");
            scanf("%s", senha);

            if (strcmp(clientes[i].senha, senha) == 0) {  // Verifica se a senha fornecida coincide com a senha do cliente.
                float valor;
                printf("Valor do débito: ");
                scanf("%f", &valor);

                if (valor > clientes[i].saldo) {
                    printf("Saldo insuficiente.\n");  // Mensagem de erro se o saldo for insuficiente.
                } else {
                    char tipo_conta[10];
                    strcpy(tipo_conta, clientes[i].tipo_conta);

                    float saldo_atual = clientes[i].saldo;

                    if (strcmp(tipo_conta, "Plus") == 0) {
                        if (saldo_atual - valor < -5000) {
                            printf("Limite de saldo negativo excedido.\n");  // Mensagem de erro se o limite de saldo negativo for excedido.
                        } else {
                            float taxa = valor * 0.03;
                            clientes[i].saldo = saldo_atual - valor - taxa;  // Atualiza o saldo com o débito e a taxa.
                            printf("Débito realizado com sucesso!\n");
                        }
                    } else if (strcmp(tipo_conta, "Comum") == 0) {
                        if (saldo_atual - valor < -1000) {
                            printf("Limite de saldo negativo excedido.\n");  // Mensagem de erro se o limite de saldo negativo for excedido.
                        } else {
                            float taxa = valor * 0.05;
                            clientes[i].saldo = saldo_atual - valor - taxa;  // Atualiza o saldo com o débito e a taxa.
                            printf("Débito realizado com sucesso!\n");
                        }
                    }
                }
                return;
            } else {
                printf("Senha incorreta.\n");  // Mensagem de erro se a senha estiver incorreta.
                return;
            }
        }
    }
    printf("CPF não encontrado.\n");  // Mensagem de erro se o CPF não for encontrado.
}

// Função para realizar um depósito na conta de um cliente.
void deposito(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  // Verifica se o CPF fornecido coincide com o CPF de algum cliente.
            char senha[50];
            printf("Senha: ");
            scanf("%s", senha);

            if (strcmp(clientes[i].senha, senha) == 0) {  // Verifica se a senha fornecida coincide com a senha do cliente.
                float valor;
                printf("Valor do depósito: ");
                scanf("%f", &valor);

                clientes[i].saldo += valor;  // Adiciona o valor ao saldo do cliente.
                printf("Depósito realizado com sucesso!\n");
                return;
            } else {
                printf("Senha incorreta.\n");
                return;
            }
        }
    }
    printf("CPF não encontrado.\n");

}

// Função para exibir o extrato de um cliente.
void extrato(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    float valor;  // Declaração da variável 'valor'
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  // Verifica se o CPF fornecido coincide com o CPF de algum cliente.
            char senha[50];
            printf("Senha: ");
            scanf("%s", senha);

            if (strcmp(clientes[i].senha, senha) == 0) {  // Verifica se a senha fornecida coincide com a senha do cliente.
                printf("Extrato do cliente %s:\n", clientes[i].nome);
                printf("Saldo: R$%.2f\n", clientes[i].saldo);
                printf("Histórico de Operações:\n");
                for (int j = 0; j < numClientes; j++) {
                    char data[100];
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    sprintf(data, "%02d/%02d/%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                            tm.tm_hour, tm.tm_min, tm.tm_sec);

                    char tipo_operacao[20];
                    char valor_operacao[20];

                    if (strcmp(clientes[i].tipo_conta, "Plus") == 0) {
                        sprintf(tipo_operacao, "Débito");
                        sprintf(valor_operacao, "%.2f", valor);  // Deve ser obtido o valor da operação do depósito.
                    } else if (strcmp(clientes[i].tipo_conta, "Comum") == 0) {
                        sprintf(tipo_operacao, "Débito");
                        sprintf(valor_operacao, "%.2f", valor);  // Deve ser obtido o valor da operação do depósito.
                    }

                    printf("%s - %s - Valor: R$%s\n", data, tipo_operacao, valor_operacao);  // Exibe informações do extrato.
                }
                printf("==== Opções do Extrato ====\n");
                printf("1. Extrato da Conta Poupança\n");
                printf("2. Voltar\n");
                int opcao;
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Extrato da Conta Poupança do cliente %s:\n", clientes[i].nome);
                    for (int j = 0; j < numClientes; j++) {
                        char data[100];
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        sprintf(data, "%02d/%02d/%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                                tm.tm_hour, tm.tm_min, tm.tm_sec);

                        char tipo_operacao[20];
                        char valor_operacao[20];

                        if (strcmp(clientes[i].tipo_conta, "Plus") == 0) {
                            sprintf(tipo_operacao, "Débito");
                            sprintf(valor_operacao, "%.2f", valor);  // Deve ser obtido o valor da operação do depósito.
                        } else if (strcmp(clientes[i].tipo_conta, "Comum") == 0) {
                            sprintf(tipo_operacao, "Débito");
                            sprintf(valor_operacao, "%.2f", valor);  // Deve ser obtido o valor da operação do depósito.
                        }

                        printf("%s - %s - Valor: R$%s\n", data, tipo_operacao, valor_operacao);  // Exibe informações do extrato.
                    }
                }
                return;
            } else {
                printf("Senha incorreta.\n");
                return;
            }
        }
    }
    printf("CPF não encontrado.\n");
}

// Função para realizar uma transferência entre contas.
void transferencia(struct Cliente *clientes, int numClientes) {
    char cpf_origem[12];
    printf("CPF do cliente que deseja transferir: ");
    scanf("%s", cpf_origem);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0) {  // Verifica se o CPF de origem coincide com o CPF de algum cliente.
            char cpf_destino[12];
            printf("CPF do cliente que irá receber a transferência: ");
            scanf("%s", cpf_destino);

            for (int j = 0; j < numClientes; j++) {
                if (strcmp(clientes[j].cpf, cpf_destino) == 0) {  // Verifica se o CPF de destino coincide com o CPF de algum cliente.
                    char senha[50];
                    printf("Senha: ");
                    scanf("%s", senha);

                    if (strcmp(clientes[i].senha, senha) == 0) {  // Verifica se a senha fornecida coincide com a senha do cliente de origem.
                        float valor;  // Declaração da variável 'valor'
                        printf("Valor da transferência: ");
                        scanf("%f", &valor);

                        if (valor > clientes[i].saldo) {
                            printf("Saldo insuficiente.\n");
                        } else {
                            char tipo_conta_origem[10];
                            strcpy(tipo_conta_origem, clientes[i].tipo_conta);

                            float saldo_atual_origem = clientes[i].saldo;

                            if (strcmp(tipo_conta_origem, "Plus") == 0) {
                                if (saldo_atual_origem - valor < -5000) {
                                    printf("Limite de saldo negativo excedido.\n");
                                } else {
                                    float taxa = valor * 0.03;
                                    clientes[i].saldo = saldo_atual_origem - valor - taxa;  // Atualiza o saldo da conta de origem com a transferência e a taxa.
                                    clientes[j].saldo += valor;  // Atualiza o saldo da conta de destino com a transferência.
                                    printf("Transferência realizada com sucesso!\n");
                                }
                            } else if (strcmp(tipo_conta_origem, "Comum") == 0) {
                                if (saldo_atual_origem - valor < -1000) {
                                    printf("Limite de saldo negativo excedido.\n");
                                } else {
                                    float taxa = valor * 0.05;
                                    clientes[i].saldo = saldo_atual_origem - valor - taxa;  // Atualiza o saldo da conta de origem com a transferência e a taxa.
                                    clientes[j].saldo += valor;  // Atualiza o saldo da conta de destino com a transferência.
                                    printf("Transferência realizada com sucesso!\n");
                                }
                            }
                        }
                        return;
                    } else {
                        printf("Senha incorreta.\n");
                        return;
                    }
                }
            }
            printf("CPF de destino não encontrado.\n");
            return;
        }
    }
    printf("CPF de origem não encontrado.\n");
}

// Função para realizar operações na conta poupança de um cliente.
void operacao_poupanca(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  // Verifica se o CPF fornecido coincide com o CPF de algum cliente.
            int opcao;
            printf("Escolha uma opção:\n");
            printf("1. Depósito\n");
            printf("2. Saque\n");
            printf("3. Voltar\n");
            printf("Opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1: {
                    float valor;
                    printf("Valor do depósito: ");
                    scanf("%f", &valor);

                    if (valor <= 0) {
                        printf("Valor inválido. O valor do depósito deve ser maior que zero.\n");
                        return;
                    }

                    if (valor > clientes[i].saldo) {
                        printf("Saldo insuficiente na conta normal.\n");
                        return;
                    }

                    clientes[i].saldo -= valor;
                    clientes[i].saldo_poupanca += valor;  // Atualiza os saldos da conta normal e da conta poupança com o depósito.
                    printf("Depósito realizado com sucesso!\n");
                    break;
                }
                case 2: {
                    float valor;
                    printf("Valor do saque: ");
                    scanf("%f", &valor);

                    if (valor <= 0) {
                        printf("Valor inválido. O valor do saque deve ser maior que zero.\n");
                        return;
                    }

                    if (valor > clientes[i].saldo_poupanca) {
                        printf("Saldo insuficiente na conta poupança.\n");
                        return;
                    }

                    clientes[i].saldo_poupanca -= valor;
                    clientes[i].saldo += valor;  // Atualiza os saldos da conta poupança e da conta normal com o saque.
                    printf("Saque realizado com sucesso!\n");
                    break;
                }
                case 3:
                    return;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
            return;
        }
    }
    printf("CPF não encontrado.\n");
}
