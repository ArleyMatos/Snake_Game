#include <stdio.h>
#include <stdlib.h>
#include "bibli_snake.h"

#define lim 20

int main(){
	char tela[lim][lim];
	cobra *snk;	
	snk	= inicializar_cobra();  
	tela_ini(tela,snk);
	aum_tamanho(snk);
	aum_tamanho(snk);
	corpo_cobra(snk);
	pos_cobra(snk);
	refresh(tela,snk);
	frame(tela);
	/*
	move_cobra(snk);
	Sleep(snk->speed*2);
	refresh(tela,snk);
	frame(tela);
	*/
	
	
	
	return 0;
}


