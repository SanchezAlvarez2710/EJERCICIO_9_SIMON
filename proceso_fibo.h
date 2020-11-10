
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <direct.h>

using namespace std;
const string YO = "\n\t\t\t\t\t\t\t\t\t         Desarrollado por SIMON SANCHEZ ALVAREZ\n\t\t\t\t\t\t\t\t\t                                Politecnico JIC\n\t\t\t\t\t\t\t\t\t                                           2020";

struct informacion{
	int i;				//VARIABLE QUE ALMACENA CUANTOS TERMINOS TIENE LA LISTA EN CASO DEL NODO CABEZA O ALMACENA LA SUMA DE LA SERIE FIBONACCI DEL SIGUIENTE TERMINO
	char letra;			//LETRA QUE EL USUARIO INGRESA O QUE SE ALMACENA UNA VEZ INGRESADO DOS NODOS CON CARACTERES APARTE DEL NODO CABEZA
};

struct nodo{
	informacion info;	//VARIABLE QUE INTERACTUA CON LA ESTRUCUTRA "informacion"
	nodo *li, *ld;
};

//PARAMETRIZACIONES DE FUNCIONES
void FIBO(nodo *&);
nodo *PROCESO_FIBO(nodo *);
int OPCIONES_FIBO(nodo *&);
nodo *PROCESO_OPC(int , nodo *);
void buscarTermino(nodo *&);
nodo *eliminarDato(nodo *, nodo *&);
nodo *adicionarDato(nodo *);
void guardarArchivo(nodo *);
void LISTA(nodo *);

void HOME(nodo *cabeza){			//INSERCION DE LOS DOS PRIMERO TERMINOS

	int cont = 1;					//CONTADOR QUE LLEGA A 2 PARA QUE SOLO SE INGRESEN LOS PRIMERO CARACTERES DE LA LISTA
	int cond;						//CONDICION DEL MENU DESPUES DE HECHA LA SERIE FIBONACCI
	if (cabeza == NULL){
		cabeza = new nodo();
		cabeza->info.i = 0;
		cabeza->info.letra = '#';
		cabeza->info.i = 2;
	}
	system("cls");
	cout << ME;	
	cout << " ------------------------------ S E R I E  F I B O N A C C I ----------------------------- \n" << endl;
	cout << "         BIENVENIDO!. DEBERA INGRESAR DOS LETRAS INCIALMENTE PARA QUE SE CREE LA LISTA\n" << endl;	
	do{
		nodo *x = new nodo(), *p = cabeza;
		cout << "\n         ==> INGRESE LETRA EN LA POSICION (" << cont << ") A LA LISTA: ";
		cin.get(x->info.letra);	
		fflush(stdin);	  																
		while(p->ld != NULL){
			p = p->ld;
		}
		p->ld = x;
		x->li = p;
		cont++;
	}while(cont < 3);	
	FIBO(cabeza);
	do{
		cond = OPCIONES_FIBO(cabeza);
	}while((cond != 3) && (cabeza->info.i != 0));
}
void FIBO(nodo *&cab){
	system("cls");
	cout << ME;	
	cab = PROCESO_FIBO(cab);
	system("cls");
	cout << ME;
	cout << "\n     LA LISTA FIBONACCI HA QUEDADO DE LA SIGUIENTE FORMA: ";
	LISTA(cab);																//MUESTRA COMO QUEDO LA TABLA EN PANTALLA
	cout << "\n\n     ";
	system("pause");
}
nodo *PROCESO_FIBO(nodo *cabeza){									//SERIE FIBONACCI PARA COMPLETAR LA LISTA
	short int n;											//LIMITE DEL NUMERO DE REPETICIONES QUE SE HARA LA SERIE
	int w = 0;
	unsigned int suma;												//AUXILIAR EL CUAL GUARDARA LA SUMA DE LOS CARCTERES 
	int ascii;												//VARIABLE QUE GUARDA EL VALOR ASCII DE CADA LETRA
	char aux_letra;
	nodo *p, *q;
	cout << "\n\tCUANTAS VECES DESEA QUE SE REALICE LA SERIE FIBONACCI?: ";
	cin >> n;								
	p = cabeza->ld;	
	while(p != NULL){							//ALMACENA EL VALOR ASCII DE LAS DOS PRIMERAS LETRAS INGRESADAS POR EL USUARIO
		aux_letra = p->info.letra;
		ascii = aux_letra;
		p->info.i = ascii;
		p = p->ld;
	}	
	p = cabeza->ld;
	nodo *aux = p;								//AUX VA ADELANTE DE p PARA SUMAR LOS DOS VALORES
	if(n > 0){									//PROCESO DE INSERCION POR MEDIO DE LA SERIE FIBONACCI			
		do{
			nodo *x = new nodo();
			while(aux->ld != NULL){
				aux = aux->ld;
			}												
			suma = (p->info.i) + (aux->info.i);
			x->info.i = suma;
			x->li = aux;
			aux->ld = x;
			p = aux;
			w++;
		}while(w != n);
		cabeza->info.i = n + 2; 
	}
	
	return cabeza;
}
int OPCIONES_FIBO(nodo *&cab){
	int opc;					//OPCION DEL MENU
	system("cls");
	cout << ME << endl;
	LISTA(cab);						//SE MUESTRA LA LISTA POR SEGUNDA VEZ PARA QUE EL USUARIO PUEDA ESTAR SEGURO DE LA INSERCION
	cout << "\n\n\tLA SERIE SE HA GENERADO CORRECTAMENTE...QUE DESEA HACER?";
	cout << "\n\t-----------------------------------------------------------------" << endl;
	cout << "\n\t(1) BUSCAR TERMINOS" << endl;
	cout << "\n\t(2) ADICIONAR TERMINOS A LA SERIE" << endl;
	cout << "\n\t(3) SALIR DEL PROGRAMA Y GUARDAR LA LISTA EN UN ARCHIVO" << endl;
	cout << "\n\t-----------------------------------------------------------------" << endl;
	cout << "\n\tESCOJA UNA OPCION: ";
	cin >> opc;
	cab = PROCESO_OPC(opc, cab);
	return opc;
}
nodo *PROCESO_OPC(int opcion, nodo *cab){
	switch (opcion){
		case 1:
			buscarTermino(cab);
		break;
		case 2:
			cab = adicionarDato(cab);
		break;
		default:
			if(opcion != 3){
				system("cls");
				cout << "\n\t\aERROR. INGRESE UNA OPCION CORRECTA!\n\n\t";
				system("pause");
			}
			else{
				system("cls");
				cout << ME;
				cout << "\a\n\tLA CARPETA CON EL ARCHIVO.txt SE GUARDARA EN (c:/Ejercicio_9_Simon_Sanchez)...";
				getch();
				guardarArchivo(cab);
			}
		break;	
	}
	return cab;
}
void buscarTermino(nodo *&cab){
	int term;									//VARIABLE QUE GUARDA EL DATO BUSCADO Y LA COMPARA CON CADA VALOR ASCII DE CADA NODO DE LA LISTA
	int op_buscar;								//VARIABLE QUE ALMACENA LA OPCION QUE DESEA EL USUARIO PARA EL CASO DE QUE QUIERA ELIMINAR EL DATO BUSCADO
	int i = 0;									//VARIABLE TIPO CONTADOR QUE GUARDARA CUANTOS DATOS A BUSCAR ESTAN EN LA LISTA
	nodo *p = cab->ld;
	system("cls");
	cout << ME;
	cout << "\n\n\tQUE TERMINO DESEA BUSCAR?: ";
	cin >> term;
	while(p != NULL){
		if(p->info.i == term){		
			i++;
			break;
		}
		p = p->ld;
	}
	if (i == 0){
		system("cls");
		cout << ME;
		cout << "\n\n\t\aEL DATO NO SE ENCUENTRA EN LA LISTA!\n\n\t";
		system("pause");
	}
	else if(i == 1){
		do{
			system("cls");
			cout << ME;
			cout << "\n\n\tSOLO SE HA ENCONTRADO UN TERMINO REFERENTE AL DATO QUE SE QUIERE BUSCAR!" << endl;
			LISTA(cab);
			cout << "\n\tQUE DESEA HACER CON EL TERMINO?" << endl;
			cout << "\t--------------------------------------------";
			cout << "\n\t(1) ELIMINARLO" << endl;
			cout << "\n\t(2) VOLVER AL MENU PRPAL" << endl;
			cout << "\t--------------------------------------------";
			cout << "\n\tESCOJA UNA OPCION: ";
			cin >> op_buscar;
			switch(op_buscar){
				case 1:
					cab = eliminarDato(cab, p);
					if (cab->info.i == 0){
						system("cls");
						cout << ME;
						cout << "\n\tLA LISTA HA QUEDADO VACIA...\n\n\t";
						system("pause");
					}
				break;
				default:
					if(op_buscar != 2){
						system("cls");
						cout << "\n\t\aERROR. INGRESE UNA OPCION CORRECTA!\n\n\t";
						system("pause");
					}
				break;
			}
		}while((op_buscar != 2) && (op_buscar != 1));
	}
}

nodo *eliminarDato(nodo *cab, nodo *&p){
	nodo *q;
	nodo *aux;
	int suma_new = 0;
	
	if(p->ld != NULL){
		aux = p->li;
		aux->ld = p->ld;
		aux = aux->ld;
		aux->li = p->li;
		p->ld = NULL;
		p->li = NULL;
		delete(p);
		if ((aux->ld != NULL) || (aux->li != NULL)){
			q = cab->ld;
			aux = q->ld;
			if(aux != NULL){
				while(aux->ld != NULL){
					suma_new = (q->info.i) + (aux->info.i);
					q = aux;
					aux = aux->ld;
					aux->info.i = suma_new;
				}
			}
		}
	}
	else if((p->ld == NULL)	&& (p->li == cab)){
		cab->ld = NULL;
		p->li = NULL;
		delete(p);
	}
	else if(p->ld == NULL){
		aux = p->li;
		aux->ld = NULL;
		p->li = NULL;		
		delete(p);
	}
	cab->info.i--;
	
	return cab;
}
nodo *adicionarDato(nodo *cab){
	nodo *p = cab->ld, *aux;
	int n = 0;
	int w = 0;
	unsigned int suma_add = 0;
	
	system("cls");
	cout << ME;
	cout << "\n\tCUANTOS TERMINOS DESEA ADICIONAR?: ";
	cin >> n;
	while(p->ld != NULL){
		p = p->ld;
	}
	if(n > 0){									
		aux = p->li;		
		do{
			nodo *x = new nodo();												
			suma_add = (p->info.i) + (aux->info.i);
			x->info.i = suma_add;
			x->li = p;
			p->ld = x;
			aux = p;
			p = p->ld;
			w++;
		}while(w != n);
		cab->info.i = cab->info.i + n; 
	}	
	return cab;
}
void guardarArchivo(nodo *cab){
	ofstream archivo;
	string nombre_archivo;
	
	if (mkdir("c:/Ejercicio_9_Simon_Sanchez") == 0){
		system("cls");
		cout << ME;
		cout << "\n\tLa carpeta con nombre (Ejercicio_9_Simon_Sanchez) se ha creado correctamente en c:/Ejercicio_9_Simon_Sanchez\n\t";
	}
	else{
		system("cls");
		cout << ME;
		cout << "\n\tNo se ha podido crear la carpeta o ya existe...\n\t";
	}
	system("pause");
	system("cls");
	cout << ME;
	cout << "\n\tQUE NOMBRE LE DESEA PONER AL ARCHIVO.txt (OMITA EL .txt): ";
	cin >> nombre_archivo;
	nombre_archivo = "c:/Ejercicio_9_Simon_Sanchez/" + nombre_archivo + ".txt";
	cout << "\n\tLA CARPETA DONDE ESTA GUARDADO EL ARCHIVO.txt ES: " << nombre_archivo;
	getch();
	archivo.open(nombre_archivo.c_str(), ios::out);	//SE CREA EL ARCHIVO
	if(archivo.fail()){
		system("cls");
		cout << ME;
		cout << "\n\tNo se pudo crear o abrir el archivo.txt...\n\t";
		system("pause");
	}
	else{
		nodo *p = cab->ld;
		while(p != NULL){				
			archivo << p->info.i << endl;
			p = p->ld;
		}
		archivo.close();
		cout << "\n\n\n\n\tADIOS, GRACIAS POR UTILIZAR EL PROGRAMA!...";	
	}
}
void LISTA(nodo *cab){					//MUESTRA LA LISTA EN CUALQUIER MOMENTO, MAS NO ES LA OPCION "MOSTRAR LA LISTA"
	
	nodo *p = cab;
	int j = 1;
	cout << "\n                                                        \n\n\t(POSICION)\t   \t  (INFORMACION)\n     ==============================================" << endl;
	while (p != NULL){			
		if(p == cab){
			cout <<  "\t   " << "CAB" << "\t\t==>\t   " <<  p->info.letra << p->info.i << endl;
			p = p->ld;
			if(cab->info.i >= 2){
				do{
					cout <<  "\t    " << j << "\t\t==>\t  " <<  p->info.letra << "("<< p->info.i << ")"<< endl;
					j++;
					p = p->ld;
				}while(j <= 2);
			}
		}		
		else{
			cout <<  "\t    " << j << "\t\t==>\t   (" << p->info.i << ")" << endl;	
			j++;
			p = p->ld;
		}	
	}			
}


