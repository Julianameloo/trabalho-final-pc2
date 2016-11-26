#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALEATORIO rand()%31

/************************************************************************/
/* MENUS */

int Menu_Principal () {
	int op;
	system ("clear");
	printf ("\n\t\t\t\t|Menu principal|\t\t\t\n\n");
	printf ("\t|1| Pacientes\n\t|2| Médicos\n\t|3| Medicamentos\n\t|4| Sair\n\n");
	printf (" Digite a opção desejada: ");
	scanf ("%d", &op);
	return op;
}

int Menu_Comum (char str[]) {
	int op;
	system ("clear");
	printf ("\n\t\t\t\t|%s|\t\t\t\n\n", str);
	printf ("\t|1| Cadastrar\n\t|2| Remover\n\t|3| Buscar\n\t|4| Alterar\n\t|5| Menu Principal\n\t|6| Imprimir Cadastros\n\t|7| Sair\n\n");
	printf (" Digite a opção desejada: ");
	scanf ("%d", &op);
	system ("clear");
	return op;
}

/************************************************************************/
/* ESTRUTURAS */

typedef struct {
	int dia, mes, ano;
} Data;

typedef struct {
	char nome[20];
	char endereco[20];
	long int telefone;
	char relacao[10];
} Responsavel;

typedef struct {
	char nome[20];
	char especialidade[20];
	int codigo;
	char telefone[15];
} Medico;
	
typedef struct {
	char nome[20];
	Data nascimento;
	Responsavel responsavel;
	int codigo;
	char tipo_sangue[5];
	char quadro_clinico[200];
	char pagamento[20];
	int motivo;
	Medico codMedico;
} Paciente;

typedef struct {
	char nome[30];
	char lab[20];
	Data validade;
} Medicamento;

/************************************************************************/
/* MEDICO */

int Gerar_Codigo_Medico () {
	int codigo;
	srand(time(NULL));
	codigo = ALEATORIO;
	return codigo;
}

int Buscar_Medico(Medico *medico, int i, int cod){
	if(i == 0) return -1;
	else if(medico[i-1].codigo == cod) return i-1;
	else Buscar_Medico(medico, i-1, cod);	
}

void Imprimir_Medico(Medico *medico){
	printf("\n\nCódigo: %d\n", medico->codigo);
	printf("Nome: %s\n", medico->nome);
	printf("Especialidade: %s\n", medico->especialidade);
	printf("Telefone: %s\n\n", medico->telefone);
}

int Cadastrar_Medico (Medico *medico, int i) {
	system ("clear");
	printf ("\t\t\t|Adicionar Médico|\t\t\t\n");
	printf ("Nome: ");
	scanf(" %[^\n]s", medico->nome);
	printf ("Especialidade: ");
	scanf(" %[^\n]s", medico->especialidade);
	printf ("Telefone: ");
	scanf(" %[^\n]s", medico->telefone);
	medico->codigo = Gerar_Codigo_Medico();
	printf("Código do médico: %d\n", medico->codigo);
	i++;
	return i;
}

int Remover_Medico (Medico *medico, int i){
	int cod, c, busca;
	char op;
	printf("Informe o código do médico: ");
	scanf("%d", &cod);
	busca = Buscar_Medico(medico, i, cod);
	if(busca == -1)
		printf("\nMédico não encontrado!\n");
	else{
		Imprimir_Medico(medico+busca);
		fflush(stdin);	
		printf("Deseja realmente excluir? s/n ");
		scanf("%c", &op);
		scanf("%c", &op);
		if(op == 's'){
			printf("O médico foi removido!\n");
			for(c=0; c<i; c++)
				medico[c] = medico[c+1];
		
			i--;
		}
	}
	
	return i;
}

void Alterar_Medico(){

}

/************************************************************************/
/* PACIENTE */

int Cadastrar_Paciente (Paciente *medico, int i) {
		
		printf ("\t\t\t|Adicionar Médico|\t\t\t\n");
		printf ("Nome: ");
		return i;
		
}

int Remover_Paciente (){

}

void Alterar_Paciente(){

}

void Buscar_Paciente(){

}

void Imprimir_Paciente(){

}

int Gerar_Codigo_Paciente (Paciente *paciente) {
	int codigo;
	srand(time(NULL));
	codigo = ALEATORIO;
}

/************************************************************************/
/* MEDICAMENTO */

int Cadastrar_Medicamento (Medicamento *medico, int i) {
		
		printf ("\t\t\t|Adicionar Médico|\t\t\t\n");
		printf ("Nome: ");
		return i;
		
}

int Remover_Medicamento (){

}

void Alterar_Medicamento(){

}

void Buscar_Medicamento(){

}

void Imprimir_Medicamento(){

}

