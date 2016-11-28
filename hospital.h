#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX	101
#define ALEATORIO (rand()%MAX)+1
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
	char nome[50];
	char endereco[20];
	long int telefone;
	char relacao[10];
} Responsavel;

typedef struct {
	char nome[50];
	char especialidade[20];
	int codigo;
	char telefone[15];
} Medico;
	
typedef struct {
	char nome[50];
	Data nascimento;
	Responsavel responsavel;
	int cod;
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

typedef struct pac{ 
	Paciente paciente;
	struct pac *Prox;
}Pac;

typedef Pac *Ponteiro_pac;

typedef struct {
	Ponteiro_pac Prim, Ult;
	int Tam;
}Lista_enc_pac;

/************************************************************************/
/*VARIAVEIS GLOBAIS*/
FILE *arq;
Lista_enc_pac L;
Paciente X;


/************************************************************************/
/*DECLARAÇÃO FUNÇÕES*/
int Gerar_Codigo_Medico ();
int Buscar_Medico (Medico *medico, int i, int cod);
void Imprimir_Medico (Medico *medico);
int Cadastrar_Medico (Medico *medico, int i);
int Remover_Medico (Medico *medico, int i);
void Alterar_Medico ();
int Remover_Paciente ();
void Alterar_Paciente ();
void Buscar_Paciente ();
void Imprimir_Paciente ();
int Cadastrar_Medicamento (Medicamento *medico, int i);
int Remover_Medicamento ();
void Alterar_Medicamento ();
void Buscar_Medicamento ();
void Imprimir_Medicamento ();
int Codigo_Repetido_Paciente (int codigo, Paciente paciente);
int Gerar_Codigo_Paciente (Paciente paciente);
void Criar_Lista_Vazia_pac(Lista_enc_pac *L);
int Verifica_Lista_Vazia_pac(Lista_enc_pac L);
void Insere_Elemento_Lista_pac(Lista_enc_pac *L, Paciente X);
void Exibir_Elemento_pac(Paciente X);
void Remove_Elemento_Lista_pac(Lista_enc_pac *L, Paciente *X);
void Exibir_Lista_pac(Lista_enc_pac L);
void Consulta_Elemento_pac(Lista_enc_pac L, int cod);
void Ler_pac(Paciente *X);
void Menu_pac();
void Gravar_Arquivo_Pac (Ponteiro_pac P);
void Carregar_Arquivo_Pac (Paciente X);

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

int Codigo_Repetido_Paciente (int codigo, Paciente paciente) {
	Ponteiro_pac P;
	int i = 0;
	P = L.Prim;
	while(P!=L.Ult) {
		if (codigo == P->Prox->paciente.cod) i++;
		P=P->Prox;
	}
	if (i != 0) return 1;
	else return 0;
}
int Gerar_Codigo_Paciente (Paciente paciente) {
	int codigo;
	srand(time(NULL));
	codigo = ALEATORIO;
	if (Codigo_Repetido_Paciente (codigo, paciente)) {
		return Gerar_Codigo_Paciente (paciente);
	}
	else 
		return codigo;
}

void Criar_Lista_Vazia_pac(Lista_enc_pac *L) {
	Ponteiro_pac P;
	P = (Ponteiro_pac) malloc(sizeof (Pac));
	L->Prim = P;
    L->Ult = L->Prim;
    L->Tam = 0;
 }

int Verifica_Lista_Vazia_pac(Lista_enc_pac L) {  
	   return(L.Prim == L.Ult);
}

void Insere_Elemento_Lista_pac(Lista_enc_pac *L, Paciente X) {
 	 Ponteiro_pac P, A;
	 P = (Ponteiro_pac) malloc(sizeof (Pac));
	 P->paciente = X;
	 A = L->Prim;
	 while((A!=L->Ult)&&(X.cod>A->Prox->paciente.cod))
	    A = A->Prox;
	  P->Prox = A->Prox;
	  A->Prox = P;
	  if(A==L->Ult)
		 L->Ult = P;
	  L->Tam++;
}
	 
void Exibir_Elemento_pac(Paciente X) {
	printf("\nNome: %s\n", X.nome);
	printf("Data de Nasciento: %2d/%2d/%4d\n", X.nascimento.dia, X.nascimento.mes, X.nascimento.ano);
	printf ("Tipo sanguíneo: %s\n", X.tipo_sangue);
	printf ("Quadro clínico: %s\n", X.quadro_clinico);
	printf ("Tipo de pagamento: %s\n", X.pagamento);  
	printf ("Codigo: %d\n\n", X.cod);
}
	 
void Remove_Elemento_Lista_pac(Lista_enc_pac *L, Paciente *X) {
	Ponteiro_pac P, A;
	if(Verifica_Lista_Vazia_pac (*L))
		printf("A Lista esta vazia - remove\n");
	else { 
		P = L->Prim;
        while((P!=L->Ult)&&(X->cod > P->Prox->paciente.cod))
        	P=P->Prox;
        if ((P==L->Ult)||(X->cod!=P->Prox->paciente.cod))
        	printf("Paciente NAO EXISTE na lista - Remove\n");
        else {
        	*X = P->Prox->paciente;
			printf("\n Cadastro removido : \n");
			Exibir_Elemento_pac(*X);
            A = P->Prox;
            if (A==L->Ult)
            	L->Ult = P;
				P->Prox=A->Prox;
				free(A);
				L->Tam--;
		}
	}
}
   
void Exibir_Lista_pac(Lista_enc_pac L) {
	system ("clear");
	Ponteiro_pac P;
	if(Verifica_Lista_Vazia_pac(L))
		printf("Lista Vazia - nada para exibir \n\n");
	else { 
	  	P = L.Prim;
		while(P!=L.Ult) {
			Exibir_Elemento_pac(P->Prox->paciente);
			P=P->Prox;
		}
	}
	getchar();
}
 
void Consulta_Elemento_pac(Lista_enc_pac L, int cod) { 
	Ponteiro_pac P;
    if(Verifica_Lista_Vazia_pac (L))
    	printf("A Lista esta vazia - consulta\n");
    else { 
    	P = L.Prim->Prox;
        while((P!=NULL)&&(cod > P->paciente.cod))
        	P=P->Prox;
        if ((P==NULL)||(cod!=P->paciente.cod))
        	printf("Paciente NAO foi encontrado para consulta\n");
        else  Exibir_Elemento_pac(P->paciente);   
	}
}
  
void Ler_pac(Paciente *X) {
	system ("clear");
	printf("Nome: ");
	scanf(" %[^\n]s", X->nome);
	printf("Dia de Nasciento <dd>: ");
	scanf("%d", &(X->nascimento.dia));
	printf("Mês de Nasciento <mm>: ");
	scanf("%d", &(X->nascimento.mes));
	printf("Ano de Nasciento <aaaa>: ");
	scanf("%d", &(X->nascimento.ano));
	printf ("Tipo sanguíneo: ");
	scanf (" %[^\n]s", X->tipo_sangue);
	printf ("Quadro clínico: ");
	scanf (" %[^\n]s", X->quadro_clinico);
	printf ("Tipo de pagamento: ");
	scanf (" %[^\n]s", X->pagamento);
	X->cod = Gerar_Codigo_Paciente (*X);
	printf ("Código gerado: %d\n", X->cod);
}


void Menu_pac() {
	printf("\t\t\t|Menu Paciente|\t\t\t\n\n");
	printf("\t|1| Cadastrar paciente\n");
	printf("\t|2| Remover cadastro\n");
	printf("\t|3| Acessar lista\n");
	printf("\t|4| Alterar\n");
	printf("\t|5| Menu Principal\n");
	printf("\t|6| Exibir cadastros\n");
	printf("\t|7| Sair\n");
	printf("\n Digite a opção desejada: ");
}
   
void Gravar_Arquivo_Pac (Ponteiro_pac P) {
	arq = fopen("arquivo_paciente.bin", "wb");
	if(arq!=NULL) { 
		P=L.Prim->Prox;
		while(P!=NULL) {
			fwrite(&(P->paciente), sizeof(Paciente),1,arq);
			P=P->Prox;						
		}  
		fclose(arq);    
	}
}

void Carregar_Arquivo_Pac (Paciente X) {
	arq = fopen("arquivo_paciente.bin", "rb"); 
	if (arq!=NULL) {
		Criar_Lista_Vazia_pac(&L);
		X.cod=0;
		while (!feof(arq)) {
			if(X.cod!=0)
				Insere_Elemento_Lista_pac(&L,X);
			fread(&X, sizeof(Paciente), 1, arq);   //fechamento
		}      
		fclose(arq);
	}
}      

/************************************************************************/
/* MEDICAMENTO */

int Cadastrar_Medicamento (Medicamento *medico, int i) {
		
		printf ("\t\t\t|Cadastro Paciente|\t\t\t\n");
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

/************************************************************************/
/*COMUM*/

void Gravar_Arquivo (int tipo) {

}

void Codigo_Repetido (int cod) {

}
