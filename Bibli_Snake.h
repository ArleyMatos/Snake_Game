#ifndef BIBLI_SNAKE_H
#define BIBLI_SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


#define lim 20
#define limname 30
//----------------------------DECLARAï¿½AO---------------------------------------------------------------
typedef char caracter;
typedef int pontuacao,tamanho,movimento,position,velocidade,game_over;
typedef char name;


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

typedef struct panel{ //estrutura de players
	int menu_ini,opcao,aux;
	
}painel;



typedef struct tp_no_arvore{
	struct tp_no_arvore *esq;
	name nome[30];
	pontuacao pontos;
	struct tp_no_arvore *dir;
}tp_no_arv;



typedef struct snake{	//estruturas da cobra 
	tamanho tam;
	movimento move_cobra;
	position posx,posy;	
	no *ini;
	no *fim;
	velocidade speed;
	game_over dead;
}cobra;

typedef tp_no_arv *tp_arvore;

//--------------------------------INICIALIZAï¿½AO---------------------------------------------------

tp_arvore inicializa_arvore(){
	return NULL;
}

int arvore_vazia(tp_arvore raiz){
	if(raiz==NULL) return 1;
	else return 0;
}

tp_no_arv *aloca_no(){ //aloca e retorna o endereço
	tp_no_arv *noarv;
	noarv =(tp_no_arv*)malloc(sizeof(tp_no_arv));
	strcpy(noarv->nome,"SEM NOME");
	return noarv;

}


painel *inicializar_menu(){
	painel *menu = (painel*) malloc(sizeof(painel));
	menu->opcao = 0;
	menu->menu_ini = 0;
	menu->aux = 1;
	return menu;
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


void regras(painel *m){
	int x;
	system("cls");
	printf("Tecla ascendente: Para cima\nTecla descendente: Para baixo\nTecla esquerda: Esquerda\nTecla direita: Direita\nESQ para sair durante o jogo\n\n\nClique 1 para voltar");

	x = getch(); 
	while(x!=49){
		printf("\nDigite 1 para sair ");
		x = getch();
	} 
	if(x==49){
		m->menu_ini = 0;
	}	
}


void verificar_menu(painel *m){
	switch (m->menu_ini){
		case 1:
			break;
		case 2:
			break;
		case 3:
			regras(m);	
			break;
		}
}






void menu(painel *m, tp_arvore *arv){
	char auxc[20],opcoes[4][25] = 
	{"1. Iniciar jogo","2. Pontuacoes","3. Regras", "4. Sair do jogo"};
	int tecla,x,i,tam;
	while(m->aux == 1){
		for(x=0;x<4;x++){
			printf("%s\n",opcoes[x]);
		}
		m->aux = 0;				
	}
		 	tecla = getch();
	        	switch (tecla){
	        		case 49:  // numero 1 
	        			m->opcao = 0;	
	        			break;
	        		case 50: // numero 2 
	        			m->opcao = 1;	
	        			break;
					case 51: // numero 3  
	        			m->opcao = 2;	
	        			break;
					case 52: // numero 4 
	        			m->opcao = 3;	
	        			break;	
					case 13: // ENTER  
	       				 printf("%d",m->opcao);
							switch (m->opcao){
							case 0:
								m->menu_ini = 1;
								break;
							case 1:
							 	m->menu_ini = 2;
							 	int x;
								system("cls");
								
								printf("\n\n\n	Clique 1 para voltar");
							 	pre_ordem(arv);
								x = getch(); 
							
									while(x!=49){
										printf("\nDigite 1 para sair ");
										x = getch();
									} 
									if(x==49){
										m->menu_ini = 0;
									}
								  break;
							case 2:
								m->menu_ini = 3;
								break;
							case 3: 
								system("cls");
								printf("\n	VOCE SAIU DO JOGO	\n");
								Sleep(1000);
								m->menu_ini = -1;
								 break;
						 }	
														
				}
				system("cls");
				tam = strlen(opcoes[m->opcao]);
				for(x=0;x<4;x++){
					if(x == m->opcao){
						for(i=0; i<tam; i++){         	   // Converte cada caracter de Str
					    opcoes[x][i] = toupper (opcoes[x][i]);  // para maiusculas
						}
					    printf("%s\n",opcoes[x]);
					}
					else
						printf("%s\n",opcoes[x]);
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


void pre_ordem(tp_no_arv *p){
	if (p!=NULL){
		printf("\n%d --- %s\n", p->pontos, p->nome);
		pre_ordem(p->esq);
		pre_ordem(p->dir);
	}
}

void em_ordem (tp_no_arv *p){
	if (p!=NULL){
		em_ordem(p->esq);
		printf("\n%d --- %s\n", p->pontos, p->nome);
		em_ordem(p->dir);
	}
}

void pos_ordem (tp_no_arv *p){
	if (p!=NULL){
		pos_ordem(p->esq);
		pos_ordem(p->dir);
		printf("\n%d --- %s\n", p->pontos, p->nome);
	}
}
	


void tela_gameover(cobra *snk,tp_arvore *raiz, name nome[limname]){
	if(snk->dead == 1){
		insere_no(raiz,nome,snk->tam);
		system("cls");
		printf("\n\n		GAME OVER       \n\n\n		Pressione qualquer tecla\n\n\n");
	}
}


void verifica_tecla(cobra *snk,painel *m){
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
				m->menu_ini = 0;
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





int insere_no(tp_arvore *raiz,name nome[limname], pontuacao points){
	tp_no_arv *pai=NULL,*novo,*p; //*p=ponteiro auxiliar
	novo=aloca_no(); //cria um novo elemento e coloca o endereço dele no novo
	if(!novo) return 0; //não deu para alocar (novo==null)
	
	strcpy(novo->nome,nome);
	novo->pontos = points;
	novo->esq=NULL;
	novo->dir=NULL;
	p=*raiz;
	
	while(p!=NULL){
		//busca a posição onde será inserido o novo nó
		pai=p;
		if (points<p->pontos) p=p->esq;
		else p=p->dir;
	}
	
	if(pai!=NULL){
		if (points<pai->pontos) pai->esq=novo;
		else pai->dir=novo;
	}
	else *raiz=novo;
	
	return 1;
}

	
	
#endif	
	
