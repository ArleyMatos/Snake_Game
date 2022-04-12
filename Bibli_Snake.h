#ifndef BIBLI_SNAKE_H
#define BIBLI_SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


#define lim 20
//----------------------------DECLARA�AO---------------------------------------------------------------
typedef char caracter;
typedef int tamanho,movimento,position,velocidade,game_over;


typedef struct tp_no{	//estrutura de no da cobra
	struct tp_no *prox,*ant;
	position posx,posy;
	caracter charc;
	movimento move_no;
}no;

typedef struct fruit{
	position food,fx,fy;
	char fc;
}fruta;

typedef struct data{ //estrutura de players
	char nome[20];
	int pontos,menu,opcao;
	
}dados;

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

dados *inicializar_dados(){
	dados *data = (dados*) malloc(sizeof(dados));
	data->pontos = 0;
	strcpy(data->nome,"SEM NOME");
	data->menu = 0;
	return data;
}

fruta *inicializar_fruta(){
	fruta *f = (fruta*) malloc(sizeof(fruta));
//	srand( (unsigned)time(NULL) );
	f->fc = '*';
	f->food = 1;
	f->fx = ((rand() % 18)+1);
	f->fy = ((rand() % 18)+1);
	return f;
}

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
		snk->tam+=1;
		b->posx = 9;
		b->posy = 9;		
		b->move_no = snk->move_cobra;
	}
	else {
		b->move_no = snk->fim->move_no;
		switch (b->move_no){
			case 1:// PARA CIMA
				b->posx = snk->fim->posx+1;
				b->posy = snk->fim->posy;
				break;
			case 2:// PARA BAIXO
				b->posx = snk->fim->posx-1;
				b->posy = snk->fim->posy;
				break;
			case 3:// PARA O LADO ESQUERDO
				b->posy = snk->fim->posy+1;
				b->posx = snk->fim->posx;
				break;
			case 4: // PARA O LADO DIREITO
				b->posy = snk->fim->posy-1;
				b->posx = snk->fim->posx;			
				break;		
		}
		snk->fim->prox = b;
		b->ant = snk->fim;	
		snk->fim = b;        
		snk->tam+=1;
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


void menu(dados *d){
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
		cont+=1;
		atu = atu->prox;
	}
	printf("\n%d\n",cont);
}


// para cima 1 ; baixo 2 ; lado L 3; lado D 4


void refresh(char tela[lim][lim], cobra *snk,fruta *f){ // atualiza matriz com os novos valores da cobra 
	no *atu;
	atu = snk->ini;
	while(atu!=NULL){
		tela[atu->posx][atu->posy] = atu->charc; 
		atu=atu->prox;
	}
	if(f->food == 1){
	tela[f->fx][f->fy] = f->fc;
	}
}


void verifica_morte(cobra *snk){
	no *atu;
	
	if(snk->ini->posx == 0 || snk->ini->posx == 19 || snk->ini->posy == 19 || snk->ini->posy == 0 ){
			snk->dead = 1;
		}
	else {
		atu = snk->ini->prox; //
		while(atu!=NULL){
			if(snk->ini->posx == atu->posx && snk->ini->posy == atu->posy){
				snk->dead = 1;
			}
			atu = atu->prox;
		  }	
		}
}


void tela_gameover(cobra *snk){
	if(snk->dead == 1){
		system("cls");
		printf("\n\n		GAME OVER");
	}
}


void verifica_tecla(cobra *snk,dados *d){
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
			else if(tecla == 27){
				snk->dead = 1;
			}
		}
		printf("%d",snk->tam);
    }
    
void verificar_fruta(cobra *snk,fruta *f){
	if(snk->ini->posx == f->fx && snk->ini->posy == f->fy ){
		aum_tamanho(snk);
		f->food = 0;
	}
	if(f->food == 0){
		free(f);
		f = inicializar_fruta();
	}
}    

void move_cobra(cobra *snk,char tela[lim][lim],fruta *f){ // ,teclado,char tela[lim][lim]
	no *atu;
	atu = snk->fim;
			verifica_morte(snk);
			while(atu != snk->ini){
				atu->move_no = atu->ant->move_no;
				atu = atu->ant;
			}
				atu->move_no = snk->move_cobra;	
		atu = snk->ini;
		while(atu!=NULL){
				if(atu == snk->fim){
					tela[atu->posx][atu->posy] = ' ';
				}
				switch (atu->move_no){
					case 1:// PARA CIMA
						atu->posx = atu->posx-1;
						break;
					case 2:// PARA BAIXO
						atu->posx= atu->posx+1;
						break;
					case 3:// PARA O LADO ESQUERDO
						atu->posy= atu->posy-1;
						break;
					case 4: // PARA O LADO DIREITO
						atu->posy= atu->posy+1;				
						break;		
				}
				atu = atu->prox;	
				verifica_morte(snk);
			}
			verifica_morte(snk);
			verificar_fruta(snk,f);
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
	
