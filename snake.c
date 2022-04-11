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
	SetConsoleTitle("GAME SNAKE"); 
	InitConsole(10, 0);
	int x=0;
	char tela[lim][lim];
	cobra *snk;	
	dados *data;
	data = inicializar_dados();
	snk	= inicializar_cobra();  
	tela_ini(tela,snk);
	refresh(tela,snk);
	frame(tela);
	Sleep(2);
	aum_tamanho(snk);
	aum_tamanho(snk);
	aum_tamanho(snk);
	aum_tamanho(snk);
	aum_tamanho(snk);
	refresh(tela,snk);
	frame(tela);
	frame(tela);
	Sleep(10);
	move_cobra(snk,tela);
	while(snk->dead != 1){
		Sleep(10);
		refresh(tela,snk);
		frame(tela);
		verifica_tecla(snk);
		move_cobra(snk,tela);
	}
	tela_gameover(snk);
	/*
	*/
	
	
	
	return 0;
}


