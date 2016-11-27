#include "hospital.h"

int main () {
	int med, mdc, pac, op, op2, cod, i;
	Medico *medicos;
	Paciente *pacientes;
	Medicamento *medicamentos;
	
	med = mdc = pac = 0;
	
	op = Menu_Principal();
	
	do{
		switch(op){
			case 1:
				op2 = Menu_Comum("Registro Paciente");
				break;
		
			case 2:
				op2 = Menu_Comum("Registro Médico");
				break;
		
			case 3:
				op2 = Menu_Comum("Registro Medicamento");
				break;
				
			case 4:
				return 0; 
		
			default:
				printf("Opção Inválida!\n");
		}
		
		switch(op2){
			case 1:
				if(op == 1){
					
					pac = Cadastrar_Paciente(pacientes+pac, pac);
				}
				else if(op == 2){
					if(med == 0)
						medicos = (Medico*) malloc(1*sizeof(Medico));
                	else
                    	medicos = (Medico*) realloc(medicos, (med+1)*sizeof(Medico));
                
		            if(!medicos){
		                printf("Memória não realocada!\n");
		                exit(1);
		            }
		            med = Cadastrar_Medico(medicos+med, med);
				}
				else if(op == 3){
					mdc = Cadastrar_Medicamento(medicamentos+mdc, mdc);
				}
				printf("\n|5| Menu Anterior\n|6| Sair\n\nDigite a opção desejada: ");
		        scanf("%d", &op2);
				break;
		
			case 2:
				if(op == 1) pac = Remover_Paciente();
				else if(op == 2) med = Remover_Medico(medicos, med);
				else if(op == 3) mdc = Remover_Medicamento();
				printf("\n|5| Menu Anterior\n|6| Sair\n\nDigite a opção desejada: ");
		        scanf("%d", &op2);
				break;
		
			case 3:
				if(op == 1) Buscar_Paciente();
				else if(op == 2) {
					printf("Insira o código referente ao médico: ");
					scanf("%d", &cod);
					Buscar_Medico(medicos, med, cod);
				}
				else if(op == 3) Buscar_Medicamento();
				printf("\n|5| Menu Anterior\n|6| Sair\n\nDigite a opção desejada: ");
		        scanf("%d", &op2);
				break;
				
			case 4:
				if(op == 1) Alterar_Medico();
				else if(op == 2) Alterar_Paciente();
				else if(op == 3) Alterar_Medicamento();
				break;
		
			case 5:
				op = Menu_Principal();
				break;
				
			case 6:
				if(op == 1) Imprimir_Paciente();
				else if(op == 2){
					for(i=0; i<med; i++){
						Imprimir_Medico(medicos+i);
						printf("\n\n");
					}
				}
				else if(op == 3) Imprimir_Medicamento();
				printf("\n|5| Menu Anterior\n|6| Sair\n\nDigite a opção desejada: ");
		        scanf("%d", &op2);
				break;
				
			case 7:
				return 0;
		
			default:
				printf("Opção Inválida!\n");
		}
	}while(op2 == 5);
	
	free(medicos);
	return 0;
}
