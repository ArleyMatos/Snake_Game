#ifndef BIBLI_SNAKE_H
#define BIBLI_SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


#define lim 20
//----------------------------DECLARA�AO---------------------------------------------------------------
typedef char caracter;
typedef int pontuacao,tamanho,movimento,position,velocidade,game_over;


typedef struct tp_no{	//estrutura de no da cobra
	struct tp_no *prox,*ant;
	position posx,posy;
	caracter charc;
	movimento move_no;
}no;

typedef struct player{ //estrutura de players
	pontuacao pontos;
	char nome[20];
}jogador;

typedef struct snake{	//estruturas da cobra 
	tamanho tam;
	movimento move_cobra;
	position posx,posy;	
	no *ini;
	no *fim;
	velocidade speed;
	game_over dead;
}cobra;


//--------------------------------INICIALIZA�AO---------------------------------------------------

no *inicializar_no(){
	no *bloco = (no*) malloc(sizeof(no));
	bloco->posx = -1;
	bloco->posy = -1;
	bloco->prox = NULL;
	bloco->ant = NULL;
	bloco->move_no = 0;
	bloco->charc = 'O';
	
	return bloco;
}

void aum_tamanho(cobra *snk){	//aumenta o tamnaho da cobra adicionando um no em final 
	no *b;
	b = inicializar_no();
	if(snk->tam == 0){
		snk->fim=snk->ini=b;
		snk->tam=+1;
		b->posx = 9;
		b->posy = 9;		
		b->move_no = snk->move_cobra;
		printf("ENTROU NO IF\n");
	}
	else {
		b->move_no = snk->fim->move_no;
		switch (b->move_no){
			case 1:// PARA CIMA
				b->posx = snk->fim->posx+1;
				b->posy = snk->fim->posy;
				printf("ENTROU NO case 1");
				break;
			case 2:// PARA BAIXO
				b->posx = snk->fim->posx-1;
				b->posy = snk->fim->posy;
				printf("ENTROU NO case 2");
				break;
			case 3:// PARA O LADO ESQUERDO
				b->posy = snk->fim->posy+1;
				b->posx = snk->fim->posx;
				printf("ENTROU NO case 3");
				break;
			case 4: // PARA O LADO DIREITO
				b->posy = snk->fim->posy-1;
				b->posx = snk->fim->posx;
				printf("ENTROU NO case 4");				
				break;		
		}
		snk->fim->prox = b;
		b->ant = snk->fim;	
		snk->fim = b;        
		snk->tam=+1;
		printf("ENTROU NO ELSE");
	}
}

cobra *inicializar_cobra(){ // cobra inicial
	cobra *snk = (cobra*) malloc(sizeof(cobra));
	snk->dead = 0;
	snk->ini = NULL;
	snk->fim = NULL;
	snk->tam = 0;
	snk->move_cobra = 1;
	snk->speed = 500;
	aum_tamanho(snk);
	aum_tamanho(snk);
	printf("\niniciou cobra\n");
	return snk;
}

//--------------------------FUNCOES-----------------------------------------------------------------

void pos_cobra(cobra *snk){ // mostrar como esta o corpo da cobra em cadeia de char
	no *atu;
	atu = snk->ini;
	printf("\n");
	while(atu!=NULL){
		printf("\n %d,%d ",atu->posx,atu->posy);
		atu = atu->prox;
	}
	printf("\n");
}

void corpo_cobra(cobra *snk){ // mostrar como esta o corpo da cobra em cadeia de char
	no *atu;
	atu = snk->ini;
	printf("\n");
	while(atu!=NULL){
		printf("%c",atu->charc);
		atu = atu->prox;
	}
	printf("\n");
}

void verificar_tam(cobra *snk){ //verifica o tamanho da cobra em inteiro 
	no *atu;
	int cont = 0;
	atu = snk->ini;
	while(atu!=NULL){
		cont=+1;
		atu = atu->prox;
	}
	printf("\n%d\n",cont);
}


// para cima 1 ; baixo 2 ; lado L 3; lado D 4


void refresh(char tela[lim][lim], cobra *snk){ // atualiza matriz com os novos valores da cobra 
	no *atu;
	atu = snk->ini;
	while(atu!=NULL){
		tela[atu->posx][atu->posy] = atu->charc; 
		atu=atu->prox;
	}
}


void verifica_morte(cobra *snk){
	if(snk->ini->posx == 0 || snk->ini->posx == 19 || snk->ini->posy == 19 || snk->ini->posy == 0 ){
			snk->dead = 1;
			printf("GAME OVER PARCERO");
		}
}


void verifica_tecla(cobra *snk){
		if(!kbhit()){
		}
		else{
			
			int tecla;
		 	tecla = getch();
			if(tecla == 0 || tecla == 224){
	        	tecla = _getch ();
	        	switch (tecla){
	        		case 72:  // para cima 
	        			snk->move_cobra = 1;
	        			break;
	        		case 80: //para baixo
	        			snk->move_cobra = 2;
	        			break;
					case 75: // para esquerda  
	        			snk->move_cobra = 3;
	        			break;
					case 77: //para direita 
	        			snk->move_cobra = 4;
	        			break;			
				}
			}
		}
    }

void move_cobra(cobra *snk,char tela[lim][lim]){ // ,teclado,char tela[lim][lim]
	no *atu;
	atu = snk->fim;
	printf("\n");
			while(atu != snk->ini){
				atu->move_no = atu->ant->move_no;
				printf("%d",atu->move_no);
				atu = atu->ant;
			}
				atu->move_no = snk->move_cobra;	
				printf("%d",atu->move_no);
				printf("\n");
	atu = snk->ini;
		while(atu!=NULL){
				if(atu == snk->fim){
					tela[atu->posx][atu->posy] = ' ';
				}
				switch (atu->move_no){
					case 1:// PARA CIMA
						atu->posx = atu->posx-1;
						printf("ENTROU NO case cima");
						break;
					case 2:// PARA BAIXO
						atu->posx= atu->posx+1;
						printf("ENTROU NO case baixo ");
						break;
					case 3:// PARA O LADO ESQUERDO
						atu->posy= atu->posy-1;
						printf("ENTROU NO case esquerdo");
						break;
					case 4: // PARA O LADO DIREITO
						atu->posy= atu->posy+1;
						printf("ENTROU NO case direito");				
						break;		
				}
				atu = atu->prox;	
			}
			verifica_morte(snk);
}
	


	
void tela_ini(char tela[lim][lim],cobra *snk){
	int i,j;
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
	
