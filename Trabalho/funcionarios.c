#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcionarios.h"
#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

char menu(){

    char resp[2];
    printf("\n----------------------- Controle da Empresa Twomate --------------------------\n");
        printf("1 - Cadastro de Dapartamento\n2 - Cadastro de Funcionário\n3 - Alterar Funcionário\n4 - Alterar Departamento Funcionário\n5 - Alterar o Gerente de um Funcinário\n6 - Consulta Funcionário Matrícula\n7 - Gerar Folha Pagamento\n8 - Alterar o salário de um funcionário\n9 - Reatório de Funcionários por departamento\n10 - Histórico Salário em um período\n11 - Gerentes de um departamento.\n0 - Sair");
        printf("\nInsira a opção desejada: ");
        scanf("%1s%*c", resp); // o *c pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso

	// se chegou aqui, é porque a opção é válida
	return resp[0];
}

int verificaNome(char palavra[]){
    int i;
    int tamanho,cont=0;
    tamanho = strlen(palavra);
    for(i=0;palavra[i]!='\0'; i++){
        if (isspace(palavra[i])!=0){
            cont++;
        }
    }
    if (cont == tamanho){
        return 0;
    }
    for(i=0;i!=tamanho;i++){
        if(isdigit(palavra[i])!=0)
            return 0;
    }
    return 1;
}
int verificaDigito(char entrada[]){
    int i;
    for(i=0;i!=strlen(entrada);i++){
        if(isdigit(entrada[i])==0)
            return 0;
    }
    return 1;
}
int verificaData(char data[]){
    int dia, mes, ano;

    sscanf(data,"%d%*c%d%*c%d",&dia,&mes,&ano);
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1800 && ano <= 2020)){ //verifica se os numeros sao validos
        if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano é bissexto
            return 0;
        if (dia <= 28 && mes == 2) //verifica o mês de fevereiro
            return 0;
        if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11))//verifica os meses de 30 dias
            return 0;
        if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)){ //verifica os meses de 31 dias
            return 0;
        }else
            return 1;
    }
    return 1;
}
int verificaCpf(char cpf[]){
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}
void cadastroDapartamento(){
    // abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_departamento = fopen("departamento.bin", "a+b");
 
	// testa a abertura do arquivo
	if(arq_departamento == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}

	int cont_bytes = 0;
	// cont irá guardar o número total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_departamento, 0, SEEK_END);
	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_departamento);
	t_departamento departamento;
 
	if(cont_bytes == 0)
	{
		// se for 0, então não existe departamento cadastrado
		// coloco o ID começando de 1
		departamento.id = 1;
	}
	else
	{
		t_departamento ultimo_departamento;
 
		// utilizo a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(t_departamento) serve para posicionar o ponteiro
		// para que possamos pegar o último departamento cadastrado
		fseek(arq_departamento, cont_bytes - sizeof(t_departamento), SEEK_SET);
 
		// ler o departamento
		fread(&ultimo_departamento, sizeof(t_departamento), 1, arq_departamento);
 
		// o ID do departamento é o ID do último departamento acrescido em 1
		departamento.id = ultimo_departamento.id + 1;
	}
	// obtém o nome do departamento
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
	printf("\nDigite o nome do departamento: ");
	scanf("%39[^\n]%*c", departamento.nome);
 
	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
    
    printf("\nDigite a sigla: ");
	scanf("%9[^\n]%*c", departamento.sigla);
   
    // uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
    
    printf("\nDigite o ramal: ");
	scanf("%[^\n]%d", departamento.ramal);
 
	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
 
	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_departamento, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&departamento, sizeof(t_departamento), 1, arq_departamento);
 
	// fecha o arquivo
	fclose(arq_departamento);
 
	printf("\nDepartamento \"%s\" cadastrado com sucesso!\n", departamento.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta
 
	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
}
void cadastroFuncionario(){
    printf("\nInsira a matricula: ");
    printf("\nInsira o nome: ");
    printf("\nInsira a data de nascimento no estilo DD/MM/AAAA: ");
    printf("\nInsira o CPF: ");
    printf("\nInsira o ID do departamento: ");
    printf("\nInsira o salario: ");
    printf("\nInsira a rua: ");
    printf("\nInsira o bairro: ");
    printf("\nInsira o numero da casa: ");
    printf("\nInsira o complemento: ");
    printf("\nInsira a cidade: ");
    printf("\nInsira a UF: ");
    printf("\nInsira o CEP: ");
    printf("\nInsira o email: ");

}

