#include <stdio.h>
#include <stdlib.h>
#include "bibli_snake.h"

#define lim 20

int main(){
	int x=0;
	char tela[lim][lim];
	cobra *snk;	
	snk	= inicializar_cobra();  
	tela_ini(tela,snk);
	refresh(tela,snk);
	frame(tela);
	Sleep(2);
	aum_tamanho(snk);
	aum_tamanho(snk);
	refresh(tela,snk);
	frame(tela);
	move_cobra(snk,tela);
	
	while(snk->dead != 1){
		printf("%d",snk->move_cobra);
		Sleep(2);
		refresh(tela,snk);
		frame(tela);
		verifica_tecla(snk);
		move_cobra(snk,tela);
		pos_cobra(snk);
	}
	/*
	*/
	
	
	
	return 0;
}


