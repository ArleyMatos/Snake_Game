#include <stdio.h>
#include <stdlib.h>
#include "bibli_snake.h"
#include <conio.h>

#define lim 20

void InitConsole(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE); /* Handle to current output buffer*/
    COORD coord = {0, 0};
    DWORD count;

    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
    SetConsoleTextAttribute(handleConsole, wColor);
    if (GetConsoleScreenBufferInfo(handleConsole, &consoleBuffer))
        FillConsoleOutputAttribute(handleConsole, consoleBuffer.wAttributes, consoleBuffer.dwSize.X * consoleBuffer.dwSize.Y, coord, &count);
    
    return;
}   

int main(){	
	char tela[lim][lim], jogador[limname];
	tp_arvore arvore;
	arvore=inicializa_arvore();
	cobra *snk;	
	fruta *f;
	f = inicializar_fruta();
	snk	= inicializar_cobra();  
	SetConsoleTitle("GAME SNAKE"); 
	InitConsole(10, 0);
	int opcao;
	painel *painel;
	painel = inicializar_menu();
	
	while(painel->menu_ini != -1){	

		while(painel->menu_ini == 0){
			menu(painel,&arvore);
			verificar_menu(painel,&arvore);
		}
		if(painel->menu_ini == 1){
			printf("Digite seu nome : \n");
			scanf("%s", &jogador);
			snk = inicializar_cobra();	
			tela_ini(tela,snk);
			refresh(tela,snk,f);
			frame(tela);
			Sleep(100);
			move_cobra(snk,tela,f);
		}
		while(snk->dead != 1 && painel->menu_ini == 1){
			Sleep((snk->speed));
			refresh(tela,snk,f);
			frame(tela);
			verifica_tecla(snk,painel);
			move_cobra(snk,tela,f);
		}
		if(snk->dead == 1){
			tela_gameover(snk,&arvore, jogador);
			Sleep(100);
			painel->menu_ini = 0;
			}
			
			
			
			
	}
	
	return 0;
}
