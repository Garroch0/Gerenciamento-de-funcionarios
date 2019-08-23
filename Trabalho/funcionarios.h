#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

typedef struct Funcionario{

    long id;
    char matricula[10];
    char nome[60];
    char dataNascimento[11];
    char CPF[11];
    long id_departamento;
    float salario;
    char rua[40];
    char bairro[30];
    unsigned int Numero;
    char complemento[30];
    char cidade[40];
    char UF[3];
    char CEP[9];
    char email[40];

}t_funcionario;

typedef struct HistoricoFuncionario{

    long id_funcionario;
    long id_departamento;
    char data[11];

}t_historicoFuncionario;

typedef struct Departamento{

    long id;
    char nome[40];
    long id_gerente;
    char sigla[10];
    unsigned short int ramal;

}t_departamento;

typedef struct HistoricoDepartamento{

    long id_departamento;
    long id_gerente;
    char data[11];
}t_historicoDepartamento;

typedef struct HistoricoSalario{

    long id_funcionario;
    float salario;
    unsigned short int mes;
    unsigned short int ano;

}t_historicoSalario;

char menu();
int verificaNome(char *palavra);
int verificaDigito();
int verificaData(char *data);
int verificaCpf(char *cpf);
void cadastroDapartamento();
void cadastroFuncionario();
void alterarFuncionario();
void alterarDepartamento();
void alterarGerente();
void consultaFuncionario();
void folhaPagamento();
void alterarSalarioF();
void relatorioFuncionario();
void historicoSalario();
void gerenteDepartamento();



#endif // CABECALHO_H_INCLUDED

