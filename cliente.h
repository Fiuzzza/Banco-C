#ifndef CLIENTE_H
#define CLIENTE_H

// Declaração da estrutura 'Cliente' que armazena informações sobre um cliente do banco.
struct Cliente {
    char cpf[12];
    char nome[50];
    float saldo;
    char senha[50];
    char tipo_conta[10];
    float saldo_poupanca;
};

// Declaração das funções que operam em clientes.
void novo_cliente(struct Cliente *clientes, int *numClientes);
void apaga_cliente(struct Cliente *clientes, int *numClientes);
void listar_clientes(struct Cliente *clientes, int numClientes);
void debito(struct Cliente *clientes, int numClientes);
void deposito(struct Cliente *clientes, int numClientes);
void extrato(struct Cliente *clientes, int numClientes);
void transferencia(struct Cliente *clientes, int numClientes);
void operacao_poupanca(struct Cliente *clientes, int numClientes);

#endif