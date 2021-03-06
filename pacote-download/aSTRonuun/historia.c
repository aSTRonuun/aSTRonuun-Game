#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "historia.h"

void anima(){

	#ifdef _WIN32
	Sleep(50);
	#else
	usleep(10000);
	#endif
}

historia* importarConjunto(historia *v,int *c){
	historia h;
	FILE *f = fopen("arquivos-txt/historia_1.txt","r");
	if(f == NULL){
		printf("ERROR: nao foi possivel abrir aquivo");
		exit(1);
	}

	while(!feof(f)){ //Funçao para ir até o final do arquivo
		int z=0;
		(*c)++;
		v = (historia*) realloc(v, *c * sizeof(historia));
		if(v == 0){
			printf("Nao foi possivel inserir Historias");
			return v;
		}
		fscanf(f,"%d\n",&v[*c-1].id);
		fscanf(f, "%d\n", &v[*c-1].resposta);
		fscanf(f, "%d\n", &v[*c-1].xp_h);
		fscanf(f, "%d\n", &v[*c-1].desblock);
		fscanf(f, "%[^\n]\n", v[*c-1].titulo);
		fscanf(f, "%[^\n]\n", v[*c-1].texto);
		fscanf(f, "%[^\n]\n", v[*c-1].respota_texto);
	}
	fclose(f);
	return v; 
}

void imprimeHistoria(historia v[],int p){
	//Função para imprimir com acentos da linguá portuguesa
	setlocale(LC_ALL, "ptb");

	int i=0;
	system("clear || cls");
	//Imprime o texto com animação de escrita
	while(v[p].texto[i] != '&'){
		if(v[p].texto[i] == '@'){
			v[p].texto[i] = '\n';
		}
		printf("%c",v[p].texto[i]);
		i++;
		anima();
	}
	//Imprime as alternativas sem a animação 
	printf("\n");
	//Enquanto não chegar ao caractere '#' imprima
	while(v[p].texto[i] != '#'){
		if(v[p].texto[i] == '@'){
			v[p].texto[i] = '\n';
		}
		printf("%c",v[p].texto[i]);
		i++;
	}
	printf("\n");
}

//Imprime a resposta caso a pessoa tenha acertado;
void imprimeResposta(historia v[], int p){
	//Função para imprimir com acentos da linguá portuguesa
	setlocale(LC_ALL, "ptb");

	int i = 0;
	printf("\n");
	while(v[p].respota_texto[i] != '#'){
		if(v[p].respota_texto[i] == '@'){
			v[p].respota_texto[i] = '\n';
		}
		printf("%c", v[p].respota_texto[i]);
		i++;
		anima();
	}
	printf("\n");
}
