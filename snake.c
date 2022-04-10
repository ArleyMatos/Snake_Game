#include <stdio.h>
#include <stdlib.h>
#include "bibli_snake.h"

#define lim 20

int main(){
	char tela[lim][lim];
	cobra *snk;	
	snk	= inicializar_cobra();  
	tela_ini(tela,snk);
	refresh(tela,snk);
	frame(tela);
	Sleep(1000);
	aum_tamanho(snk);
	aum_tamanho(snk);
	refresh(tela,snk);
	frame(tela);
	move_cobra(snk,tela);
	
	while(snk->dead != 1){
		Sleep(1000);
		refresh(tela,snk);
		frame(tela);
		move_cobra(snk,tela);
		pos_cobra(snk);
	}
	/*
	*/
	
	
	
	return 0;
}


