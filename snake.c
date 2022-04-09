#include <stdio.h>
#include <stdlib.h>
#include "bibli_snake.h"

#define lim 20

int main(){
	char tela[lim][lim];
	cobra *snk;	
	snk	= inicializar_cobra(); //inicia a struct 
	tela_ini(tela,snk); //inicia a tela
	refresh(tela,snk); 
	frame(tela); //printa a tela
	
	return 0;
}

//printar tela inicial 
//adicionar dois nos na cobra dentro de tela ini
