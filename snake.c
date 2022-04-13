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
	char tela[lim][lim];
	cobra *snk;	
	fruta *f;
	f = inicializar_fruta();
	snk	= inicializar_cobra();  
	SetConsoleTitle("GAME SNAKE"); 
	InitConsole(10, 0);
	int opcao;
	painel *painel;
	painel = inicializar_menu();
	while(painel->menu_ini == 0){
	menu(painel);
	verificar_menu(painel);
	}
	if(painel->menu_ini == 1){	
	tela_ini(tela,snk);
	refresh(tela,snk,f);
	frame(tela);
	Sleep(2);
	refresh(tela,snk,f);
	frame(tela);
	frame(tela);
	Sleep(10);
	move_cobra(snk,tela,f);
	}
	while(snk->dead != 1 && painel->menu_ini == 1){
		Sleep(10);
		refresh(tela,snk,f);
		frame(tela);
		verifica_tecla(snk,painel);
		move_cobra(snk,tela,f);
	}
	if(snk->dead == 1){
		tela_gameover(snk);
		Sleep(100);
		painel->menu_ini = 0;
		}
	
	/*
	*/
	
	
	
	return 0;
}

