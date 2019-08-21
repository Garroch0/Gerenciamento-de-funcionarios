#include <stdio.h>
#include <stdlib.h>
#include "funcionarios.h"
#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

/*Sistema para gerenciamento de funcionários usando a linguagem C.
    Autores: Gustavo Garrocho e Leone.
    Professor:Wender Magno Cota - Estrutura de Dados I.
    IF SUDESTE MG - Campus Barbacena - 2ºSemestre 2019.*/

int main(){
    char resp;
	// loop infinito do programa
	while(1)
	{
		// obtém a escolha do usuário
		resp = menu();

		// testa o valor de "resp"
		if(resp == '1')
			cadastroDapartamento();
		else if(resp == '2')
			cadastroFuncionario();
		else if(resp == '3');
			//alterarFuncionario();
		else if(resp == '4');
			//alterarDepartamento();
		else if(resp == '5');
			//alterarGerente();
		else if(resp == '6');
			//consultaFuncionario();
		else if(resp == '7');
			//folhaPagamento();
		else if(resp == '8');
			//alterarSalarioF();
		else if(resp == '9');
			//relatorioFuncionario();
        else if(resp == '10');
			//historicoSalario();
        else if(resp == '11');
			//gerenteDepartamento();
		else if(resp == '0') // se for igual a 0, então sai do loop while
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
