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

    long id_departamento;
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

// Função que irá iniciar o programa.
// Retorna 0 para o main.
int iniciar();

// Função que irá verificar se o nome está vázio ou se é um dígito.
// Parâmetro: Ponteiro de char.
// Retorna verdadeiro caso dê tudo certo.
int verificaNome(char *palavra);


int verificaDigito();

// Função para verificação de datas.
// Parâmetro: Ponteiro de char.
// Retorna verdadeiro caso dê tudo certo.
int verificaData(char *data);

// Função para verificar um CPF.
// Parâmetro: Ponteiro de char.
// Retorna verdadeiro caso dê tudo certo.
int verificaCpf(char *cpf);

// Função para verificar o ID de um departamento em um arquivo.
// Parâmetro: Ponteiro para o arquivo e um long para o ID.
// Retorna a posição do id no arquivo caso dê tudo certo.
long existeDepartamento(FILE *arq_departamento, long id_departamento);

// Função para a matrícula de um funcionário em um arquivo.
// Parâmetro: Ponteiro para o arquivo e um ponteiro de char.
// Retorna a posição da matrícula no arquivo caso dê tudo certo.
int existeFuncionario(FILE *arq_funcionario, char *mat);

// Função que cadastra um departamento no arquivo.
void cadastroDepartamento();

// Função que cadastra um funcionário no arquivo.
void cadastroFuncionario();

// Função que altera um Funcionário buscando pela matrícula.
void alterarFuncionario();

// Função que altera um Departamento de um funcionário buscando pelo ID do departamento.
void alterarDepartamento();

void alterarGerente();
void consultaFuncionario();
void folhaPagamento();
void alterarSalarioF();
void relatorioFuncionario();
void historicoSalario();
void gerenteDepartamento();



#endif // CABECALHO_H_INCLUDED

