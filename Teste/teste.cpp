// teste.cpp : programa para teste da classe TProcuraConstrutiva
//

#include <stdio.h>
#include <locale>

#include "../TProcuraAdversa.h"
#include "JogoDoGalo.h"

int main(int argc, char* argv[])
{
	CJogoDoGalo jogo;

	std::locale::global(std::locale(""));

	jogo.TesteManual("Jogo do Galo");

}
