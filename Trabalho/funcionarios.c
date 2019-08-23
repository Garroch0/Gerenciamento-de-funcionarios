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

int verificaNome(char *palavra){
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
int verificaDigito(char *entrada){
    int i;
    for(i=0;i!=strlen(entrada);i++){
        if(isdigit(entrada[i])==0)
            return 0;
    }
    return 1;
}
int verificaData(char *data){
    int dia, mes, ano;

    sscanf(data,"%d%*c%d%*c%d",&dia,&mes,&ano);
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1800 && ano <= 2020)){ //verifica se os numeros sao validos
        if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano é bissexto
            return 1;
        if (dia <= 28 && mes == 2) //verifica o mês de fevereiro
            return 1;
        if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11))//verifica os meses de 30 dias
            return 1;
        if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)){ //verifica os meses de 31 dias
            return 1;
        }else
            return 0;
    }
    return 0;
}
int verificaCpf(char *cpf){
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

void cadastroDepartamento()
{
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
	/*
		NÃO é interessante que o usuário digite o ID do departamento
    , esse
		ID tem que ser gerado automático, então temos que pegar o
		ID do último usuário cadastrado
	*/
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
		// cont_bytes - sizeof(t_departamento) serve para posicionar
		// para que possamos pegar o último departamento cadastrado
		fseek(arq_departamento, cont_bytes - sizeof(t_departamento), SEEK_SET);

		// ler o departamento
		fread(&ultimo_departamento, sizeof(t_departamento), 1, arq_departamento);

		// o ID do departamento é o ID do último departamento acrescido em 1
		departamento.id = ultimo_departamento.id + 1;
	}
	// obtém o nome do filme
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
    do
    {
    setbuf(stdin, NULL);
    printf("\nDigite o nome do departamento: ");
	scanf("%40[^\n]%*c", departamento.nome);
    if (verificaNome(departamento.nome))
        break;
    else
    {
        printf("\nNome inválido insira novamente");
    }} while (1);


    setbuf(stdin, NULL);
    printf("\nDigite a sigla: ");
	scanf("%10[^\n]%*c", departamento.sigla);

    setbuf(stdin, NULL);
    printf("\nDigite o ramal: ");
    scanf("%hu", &departamento.ramal);


	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_departamento, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&departamento, sizeof(t_departamento), 1, arq_departamento);

	// fecha o arquivo
	fclose(arq_departamento);

    setbuf(stdin, NULL);
	printf("\ndepartamento \"%s\" cadastrado com sucesso!\n", departamento.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
}
void cadastroFuncionario(){
     // abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_funcionario = fopen("funcionario.bin", "a+b");

	// testa a abertura do arquivo
	if(arq_funcionario == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}

	int cont_bytes = 0;
	// cont irá guardar o número total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_funcionario, 0, SEEK_END);
	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_funcionario);
	t_funcionario funcionario;

	if(cont_bytes == 0)
	{
		// se for 0, então não existe funcionario cadastrado
		// coloco o ID começando de 1
		funcionario.id = 1;
	}
	else
	{
		t_funcionario ultimo_funcionario;

		// utilizo a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(t_funcionario) serve para posicionar o ponteiro
		// para que possamos pegar o último funcionario cadastrado
		fseek(arq_funcionario, cont_bytes - sizeof(t_funcionario), SEEK_SET);

		// ler o funcionario
		fread(&ultimo_funcionario, sizeof(t_funcionario), 1, arq_funcionario);

		// o ID do funcionario é o ID do último funcionario acrescido em 1
		funcionario.id = ultimo_funcionario.id + 1;
	}
	// obtém a matrícula do funcionario
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
	setbuf(stdin, NULL);
    printf("\nInsira a matricula: ");
    scanf("%9[^\n]%*c", funcionario.matricula);

    // obtém o nome do funcionario
    do
    {
    setbuf(stdin, NULL);
    printf("\nDigite o nome do funcionario: ");
    scanf("%40[^\n]%*c", funcionario.nome);
    if (verificaNome(funcionario.nome))
        break;
    else
    {
        printf("\nNome inválido insira novamente");
    }} while (1);

    do
    {
        setbuf(stdin, NULL);
        printf("\nInsira a data de nascimento no estilo DD/MM/AAAA: ");
        scanf("%11[^\n]%*c", funcionario.dataNascimento);
        //fgets(funcionario.dataNascimento,11,stdin);
        if (verificaData(funcionario.dataNascimento)){
            break;
        }
        else
            printf("\nData inválida insira novamente");
    }while(1);

    do
    {
        setbuf(stdin, NULL);
        printf("\nInsira um CPF válido: ");
        // fgets(funcionario.CPF,12,stdin);
        scanf("%12[^\n]%*c", funcionario.CPF);
        printf("\n%d", strlen(funcionario.CPF));
        if(verificaCpf(funcionario.CPF)){
            break;
        }
        else{
            printf("\nCPF inválido insira novamente abaixo.");
        }}while (1);

    setbuf(stdin, NULL);
    printf("\nDigite o ID do departamento: ");
    scanf("%d",&funcionario.id_departamento);

    setbuf(stdin, NULL);
    printf("\nDigite o salario do funcionario: ");
    scanf("%f",&funcionario.salario);

    setbuf(stdin, NULL);
    printf("\nDigite a rua do funcionario: ");
    scanf("%40[^\n]%*c", funcionario.rua);

    setbuf(stdin, NULL);
    printf("\nDigite o bairro do funcionario: ");
    scanf("%30[^\n]%*c", funcionario.bairro);

    setbuf(stdin, NULL);
    printf("\nDigite o numero: ");
    scanf("%ld", &funcionario.Numero);

    setbuf(stdin, NULL);
    printf("\nDigite o complemento: ");
    scanf("%30[^\n]%*c", funcionario.complemento);

    setbuf(stdin, NULL);
    printf("\nDigite a cidade do funcionario: ");
    scanf("%40[^\n]%*c", funcionario.cidade);

    setbuf(stdin, NULL);
    printf("\nDigite o UF: ");
    scanf("%3[^\n]%*c", funcionario.UF);

    setbuf(stdin, NULL);
    printf("\nDigite o CEP: ");
    scanf("%9[^\n]%*c", funcionario.CEP);

    setbuf(stdin, NULL);
    printf("\nDigite o email do funcionario: ");
    scanf("%40[^\n]%*c", funcionario.email);

    // uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_funcionario, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&funcionario, sizeof(t_funcionario), 1, arq_funcionario);

	// fecha o arquivo
	fclose(arq_funcionario);

	printf("\nfuncionario \"%s\" cadastrado com sucesso!\n", funcionario.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
}