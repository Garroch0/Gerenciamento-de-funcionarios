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

int iniciar(){
	
	// char resp;
	// loop infinito do programa
	while(1)
	{
		// obtém a escolha do usuário
		char resp[3];
    	printf("\n----------------------- Controle da Empresa Twomate --------------------------\n");
    	printf("1 - Cadastro de Dapartamento\n2 - Cadastro de Funcionário\n3 - Alterar Funcionário\n4 - Alterar Departamento Funcionário\n5 - Alterar o Gerente de um Funcinário\n6 - Consulta Funcionário Matrícula\n7 - Gerar Folha Pagamento\n8 - Alterar o salário de um funcionário\n9 - Reatório de Funcionários por departamento\n10 - Histórico Salário em um período\n11 - Gerentes de um departamento.\n0 - Sair");
    	printf("\nInsira a opção desejada: ");
    	scanf("%s%[^\n]*c", resp); // o *c pega o Enter e descarta
		// testa o valor de "resp"
		if(resp[1] == '0');
			//historicoSalario();
        else if(resp[1] == '1');
			//gerenteDepartamento();
		else if(resp[0] == '1')
			cadastroDepartamento();
		else if(resp[0] == '2')
			cadastroFuncionario();
		else if(resp[0] == '3')
			alterarFuncionario();
		else if(resp[0] == '4')
			alterarDepartamento();
		else if(resp[0] == '5');
			//alterarGerente();
		else if(resp[0] == '6');
			//consultaFuncionario();
		else if(resp[0] == '7');
			//folhaPagamento();
		else if(resp[0] == '8');
			//alterarSalarioF();
		else if(resp[0] == '9');
			//relatorioFuncionario();
        
		else if(resp[0] == '0') // se for igual a 0, então sai do loop while
			break;
		else
		{
			printf("\nOpcao invalida! Pressione <Enter> para continuar...\n");
			scanf("%*c");
			// uma forma de "limpar" o buffer de entrada
			fseek(stdin, 0, SEEK_END); // não recomendável o uso
		}
		system(limpar_tela);
	}
	return 0;
}
// Verifica se é um nome válido se o número de espaços for o mesmo tamanho da string é considerada vázia.
// isspace verifica se o caracter passado é um espaço e retorna true ou false
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
//verifica se uma string contem dígitos
int verificaDigito(char *entrada){
    int i;
    for(i=0;i!=strlen(entrada);i++){
        if(isdigit(entrada[i])==0)
            return 0;
    }
    return 1;
}

// função genérica para verificar datas
int verificaData(char *data){
    int dia, mes, ano;

    sscanf(data,"%d%*c%d%*c%d",&dia,&mes,&ano);
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1960 && ano <= 2020)){ //verifica se os numeros sao validos
		if(ano == 1960)
			if (dia <= 20 && mes <= 6) //verifica a data mínimima que é 20/06/1960
				return 0;
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

//função genérica para verificar um CPF
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

long existeDepartamento(FILE *arq_departamento, long id_departamento){
	// vai para o início do arquivo, pois não sabemos a posição do ponteiro no arquivo
	rewind(arq_departamento);
	long posicao;
	t_departamento departamento;
	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	while(1)
	{

		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&departamento, sizeof(t_departamento), 1, arq_departamento);
		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		// verifica se o ID é igual
		if(departamento.id_departamento == id_departamento)
			return posicao;
		else
			posicao++;
	}
	// se chegou aqui é porque NÃO existe o departamento, então retorna 0
	return -1;
}
int existeFuncionario(FILE *arq_funcionario, char *mat){
	// vai para o início do arquivo, pois não sabemos a posição do ponteiro no arquivo
	rewind(arq_funcionario);
	long posicao = 0;
	t_funcionario funcionario;
	// loop para percorrer o arquivo
	while(fread(&funcionario, sizeof(t_funcionario), 1, arq_funcionario))
	{
		// // fread retorna o número de elementos lidos com sucesso
		// size_t result = fread(&funcionario, sizeof(t_funcionario), 1, arq_funcionario);
		// // se for 0, é porque não há mais elemento, então sai do loop
		// if(result == 0)
		// 	break;
		// verifica se a matrícula é igual
		if(strcmp(funcionario.matricula,mat))
			posicao++;
		else
			return posicao;
	}
	// se chegou aqui é porque NÃO existe o funcionario, então retorna -1
	return -1;
}
//função que irá cadastrar os departamento e criar o arquivo departamento.bin caso não exista
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
	/*  ID tem que ser gerado automático, então temos que pegar o
		ID do último usuário cadastrado*/
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
		departamento.id_departamento = 1;
	}
	else
	{
		t_departamento ultimo_departamento;

		// utilizo a função fseek para posicionar o arquivo
		// para que possamos pegar o último departamento cadastrado
		// cont_bytes - sizeof(t_departamento) serve para posicionar
		fseek(arq_departamento, cont_bytes - sizeof(t_departamento), SEEK_SET);

		// ler o departamento
		fread(&ultimo_departamento, sizeof(t_departamento), 1, arq_departamento);

		// o ID do departamento é o ID do último departamento acrescido em 1
		departamento.id_departamento = ultimo_departamento.id_departamento + 1;
	}
	// obtém o nome do departamento
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
    do{
        setbuf(stdin, NULL);
        printf("\nDigite o nome do departamento: ");
        scanf("%40[^\n]%*c", departamento.nome);
        if (verificaNome(departamento.nome))
            break;
        else
            printf("\nNome inválido insira novamente");
    } while (1);


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
    // abre o arquivo "para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_funcionario = fopen("funcionario.bin", "a+b");
	FILE *arq_departamento = fopen("departamento.bin","rb+");
	FILE *arq_historicoFuncionario = fopen("historicoFuncionario.bin", "rb+");
	// testa a abertura do arquivo
	if(arq_funcionario == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}
	if(arq_departamento == NULL)
	{
		arq_departamento = fopen("departamento.bin", "wb+");
		if(arq_departamento == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}
	if(arq_departamento == NULL)
	{
		arq_departamento = fopen("historicoFuncionario.bin", "wb+");
		if(arq_departamento == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}

	int cont_bytes = 0;
	// cont irá guardar o número total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_funcionario, 0, SEEK_END);
	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_funcionario);
	
	t_historicoFuncionario historico;
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
	//atribui o ID do funcionário no histórico
	historico.id_funcionario = funcionario.id;
	
	// obtém a matrícula do funcionario
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
	do
	{
		setbuf(stdin, NULL);
		printf("\nInsira a matricula: ");
		scanf("%10[^\n]%*c", funcionario.matricula);
		printf("%d", existeFuncionario(arq_funcionario, funcionario.matricula));
		if (existeFuncionario(arq_funcionario, funcionario.matricula)==-1)
			break;
		else
			printf("Essa matricula ja esta sendo utilizada tente outra");
	} while (1);

    // obtém o nome do funcionario e verifica se o nome está vazio e se a entrada são dígitos.
    do
    {
    setbuf(stdin, NULL);
    printf("\nDigite o nome do funcionario: ");
    scanf("%40[^\n]%*c", funcionario.nome);
    if (verificaNome(funcionario.nome))
        break;
    else
        printf("\nNome inválido insira novamente");
    } while (1);

    //valida a data de nascimento.
    do
    {
        setbuf(stdin, NULL);
        printf("\nInsira a data de nascimento no estilo DD/MM/AAAA: ");
        scanf("%11[^\n]%*c", funcionario.dataNascimento);
        //fgets(funcionario.dataNascimento,11,stdin);
        if (verificaData(funcionario.dataNascimento))
            break;
        else
            printf("\nData inválida insira novamente");
    }while(1);


    //Valida o CPF do funcionário
    do
    {
        setbuf(stdin, NULL);historico.id_funcionario = funcionario.id;
        printf("\nInsira um CPF válido: ");
        scanf("%11[^\n]%*c", funcionario.CPF);
        if(verificaCpf(funcionario.CPF))
            break;
        else
            printf("\nCPF inválido insira novamente abaixo.");
        }while (1);

	long id;
	do
	{
		setbuf(stdin,NULL);
		printf("\nInsira o ID do departamento: ");
		scanf("%ld",&id);
		if (existeDepartamento(arq_departamento, id)!=-1)
		{
			funcionario.id_departamento = id;
			historico.id_departamento = id;
			break;
		}
		else{
			printf("\nDepartamento nao existe.\n");
			exit(1);
		}
	} while (1);


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
	do
	{
		setbuf(stdin, NULL);
		printf("\nInsira a data da criacao no estilo DD/MM/AAAA: ");
		scanf("%11[^\n]%*c", historico.data);
		if (verificaData(historico.data))
			break;
		else
			printf("\nData inválida insira novamente");
	}while(1);

    // uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_funcionario, 0, SEEK_END);
	fseek(arq_historicoFuncionario, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&funcionario, sizeof(t_funcionario), 1, arq_funcionario);
	fwrite(&historico, sizeof(historico), 1, arq_historicoFuncionario);

	// fecha o arquivo
	fclose(arq_funcionario);
	fclose(arq_departamento);
	fclose(arq_historicoFuncionario);

	printf("\nfuncionario \"%s\" cadastrado com sucesso!\n", funcionario.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta.
}
void alterarFuncionario(){

	char matricula[40];
    // rb+ abre para leitura/atualização
	FILE *arq_departamento = fopen("departamento.bin", "rb+");
	FILE *arq_funcionario = fopen("funcionario.bin", "rb+");
	FILE *arq_historicoFuncionario = fopen("historicoFuncionario.bin", "rb+");

	// se não conseguiu abrir, então cria o arquivo
	// wb+ abre para escrita/atualização (cria o arquivo se ele NÃO existir)
	if(arq_departamento == NULL)
	{
		arq_departamento = fopen("departamento.bin", "wb+");
		if(arq_departamento == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}

	if(arq_funcionario == NULL)
	{
		arq_funcionario = fopen("funcionario.bin", "wb+");
		if(arq_funcionario == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}
	if(arq_historicoFuncionario == NULL)
	{
		arq_funcionario = fopen("historicoFuncionario.bin", "wb+");
		if(arq_funcionario == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}

	t_funcionario funcionario;
	t_historicoFuncionario historico;
	long posicao;
	int sair;
	char data[11];
		do
		{

			printf("\nDigite a matricula do funcionario: ");
			scanf("%10[^\n]%*c", funcionario.matricula);
			posicao = existeFuncionario(arq_departamento, funcionario.matricula);
			if (posicao=-1){
				fseek(arq_funcionario,posicao*sizeof(t_funcionario),SEEK_SET);
				fread(&funcionario, sizeof(t_funcionario), 1, arq_funcionario);
				do
				{
				setbuf(stdin, NULL);
				printf("\nDigite o nome do funcionario: ");
				scanf("%40[^\n]%*c", funcionario.nome);
				if (verificaNome(funcionario.nome))
					break;
				else
					printf("\nNome inválido insira novamente");
				} while (1);

				//valida a data de nascimento.
				do
				{

					setbuf(stdin, NULL);
					printf("\nInsira a data de nascimento no estilo DD/MM/AAAA: ");
					scanf("%11[^\n]%*c", funcionario.dataNascimento);
					if (verificaData(funcionario.dataNascimento))
						break;
					else
						printf("\nData inválida insira novamente");
				}while(1);
				//Valida o CPF do funcionário
				do
				{
					setbuf(stdin, NULL);
					printf("\nInsira um CPF válido: ");
					scanf("%11[^\n]%*c", funcionario.CPF);
					if(verificaCpf(funcionario.CPF))
						break;
					else
						printf("\nCPF inválido insira novamente abaixo.");
					}while (1);

				long id;
				do
				{
					setbuf(stdin,NULL);
					printf("\nInsira o ID do departamento: ");
					scanf("%ld",&id);
					if (existeDepartamento(arq_departamento, id)!=-1)
					{
						funcionario.id_departamento = id;
						historico.id_funcionario = id;
						break;
					}
					else{
						printf("\nDepartamento nao existe.\n");
					}
				} while (1);


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

				do
				{
					setbuf(stdin, NULL);
					printf("\nInsira a data da alteracao no estilo DD/MM/AAAA: ");
					scanf("%11[^\n]%*c", historico.data);
					if (verificaData(historico.data))
						break;
					else
						printf("\nData inválida insira novamente");
				}while(1);
			}
			else
				printf("\nMatricula inexistente");
			printf("\nDeseja sair? 1-SIM 2-NAO \n:");
			scanf("%d",&sair);
			} while (sair!=1);

	// aponta para o final do arquivo do histórico
	fseek(arq_historicoFuncionario, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&funcionario, sizeof(t_funcionario), 1, arq_funcionario);
	fwrite(&historico, sizeof(t_historicoFuncionario),1,arq_historicoFuncionario);
	// fecha os arquivos
	fclose(arq_funcionario);
	fclose(arq_departamento);
	fclose(arq_historicoFuncionario);

	setbuf(stdin, NULL);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta
}

void alterarDepartamento(){

	long id_departamento;
    // rb+ abre para leitura/atualização
	FILE *arq_departamento = fopen("departamento.bin", "rb+");
	FILE *arq_funcionario = fopen("funcionario.bin", "rb+");
	FILE *arq_historicoDepartamento = fopen("historicoDepartamento.bin", "rb+");

	// se não conseguiu abrir, então cria o arquivo
	// wb+ abre para escrita/atualização (cria o arquivo se ele NÃO existir)
	if(arq_departamento == NULL)
	{
		arq_departamento = fopen("departamento.bin", "wb+");
		if(arq_departamento == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}

	if(arq_funcionario == NULL)
	{
		arq_funcionario = fopen("funcionario.bin", "wb+");
		if(arq_funcionario == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}
	if(arq_funcionario == NULL)
	{
		arq_funcionario = fopen("historicoDepartamento.bin", "wb+");
		if(arq_funcionario == NULL)
		{
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}


	t_funcionario funcionario;
	t_historicoDepartamento historico;
	long posicao;
	int sair;
	// obtém o ID do departamento
		do
		{
			printf("\nDigite o ID do departamento: ");
			scanf("%ld", &id_departamento);
			posicao = existeDepartamento(arq_departamento, id_departamento);
			if (posicao!=-1){
				setbuf(stdin,NULL);
				printf("Insira o novo ID do departamento: ");
				scanf("%ld",&id_departamento);
				posicao = existeDepartamento(arq_departamento, id_departamento);
				if (posicao!=-1){
					fseek(arq_departamento,posicao*sizeof(funcionario),SEEK_SET);
            		fread(&funcionario,sizeof(funcionario),1,arq_funcionario);
					funcionario.id_departamento = id_departamento;
					historico.id_departamento = id_departamento;
					printf("\nDepartamento alterado com sucesso!");
				}
				else
					printf("\nDepartamento inexistente");
			}
			else
				printf("\nDepartamento inexistente");
			do
			{
				setbuf(stdin, NULL);
				printf("\nInsira a data da alteracao no estilo DD/MM/AAAA: ");
				scanf("%11[^\n]%*c", historico.data);
				if (verificaData(historico.data))
					break;
				else
					printf("\nData inválida insira novamente");
			}while(1);

			printf("\nDeseja sair? 1-SIM 2-NAO \n:");
			scanf("%d",&sair);
		} while (sair!=1);

	fseek(arq_departamento,posicao*sizeof(funcionario),SEEK_SET);
	//escreve nos arquivos
	fwrite(&funcionario, sizeof(t_funcionario), 1, arq_funcionario);
	fwrite(&historico, sizeof(t_historicoDepartamento), 1 ,arq_historicoDepartamento);
	// fecha os arquivos
	fclose(arq_funcionario);
	fclose(arq_departamento);

	setbuf(stdin, NULL);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

}
