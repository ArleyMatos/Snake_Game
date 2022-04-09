#ifndef BIBLI_SNAKE_H
#define BIBLI_SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define lim 20

typedef char caracter;
typedef int pontuacao,tamanho,movimento,position,velocidade;


typedef struct tp_no{	
	struct tp_no *prox;
	position posx,posy;
	caracter charc;
}no;

typedef struct player{
	pontuacao pontos;
	char nome[20];
}jogador;

typedef struct snake{
	tamanho tam;
	movimento move;
	position posx,posy;	
	no *ini;
	no *fim;
	velocidade speed;
}cobra;


no *inicializar_no(){
	no *bloco = (no*) malloc(sizeof(no));
	bloco->posx = -1;
	bloco->posy = -1;
	bloco->prox = NULL;
	bloco->charc = 'O';
	
	return bloco;
}

int aum_tamanho(cobra *snk){//aumenta o tamnaho da cobra
	no *b;
	if(snk->fim==NULL) return 0;
	b = inicializar_no();
	if(snk->tam == 0){
		snk->fim=snk->ini=b;
	}
	else{
	snk->fim->prox = b;
	snk->fim = b;	
	}
	return 1;
}

cobra *inicializar_cobra(){
	cobra *snk = (cobra*) malloc(sizeof(cobra));
	aum_tamanho(snk);
	aum_tamanho(snk);
		
	snk->tam = 1;
	snk->move = 1;
	snk->speed = 300;
	
	printf("iniciou cobra");
	return snk;
}

// para cima 1 ; baixo 2 ; lado L 3; lado D 4

void refresh(char tela[lim][lim], cobra *snk){
	int x;
	no *atu;
	atu = snk->ini;
	for(x=0;x<snk->tam+1;x++){
		tela[atu->posx][atu->posy] = atu->charc; 
	}
}

void atualizar_pos_cobra(cobra *snk){
	no *atu;
	int x;
	atu = snk->ini;
	for(x=0;x<snk->tam+1;x++){
	switch (snk->move){
		case 1 :
			atu->posx =-1;
			break;
		case 2: 
			atu->posx=+1;
			break;
		case 3:
			atu->posy=-1;
			break;
		case 4:
			atu->posy=+1;	
			break;
	  	
		atu = atu->prox;  
		}	
	}
}



	
void tela_ini(char tela[lim][lim],cobra *snk){
	int i,j;
	snk->ini->posx = 9;
	snk->ini->posy = 9;
	snk->fim->posx = 10;
	snk->fim->posy = 9;
	
	printf("iniciou cobra");
	for(i=0;i<lim;i++){
		for(j=0;j<lim;j++){
			if(i == 0 || j==0 ||j==19 || i==19){
				tela[i][j]= 'D';
			
			}
			else{
			tela[i][j] = ' ';
			
			}
		}
	}
}



void frame(char tela[lim][lim]){
	int i,j;
	system("cls");
	for(i=0;i<lim;i++){
		for(j=0;j<lim;j++){
			printf("%c ",tela[i][j]);
		}
		printf("\n");
	} 
}
	
	
	
#endif	
	
