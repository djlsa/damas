#pragma once

#include <string>

using namespace std;

#include "Tabuleiro.h"

enum Estado { QUADRADO_BRANCO, QUADRADO_PRETO, MOVIMENTO_NO_SE, MOVIMENTO_SO_NE, PECA_CAPTURADA };

class Casa
{
public:
	Casa(Tabuleiro* tabuleiro, int linha, int coluna);
	~Casa(void);
	void setEstado(Estado estado);
	void setEstadoOriginal(bool pecas);
	Estado getEstado();
	int getLinha();
	int getColuna();
	Peca* getPeca();
	void moverPeca(Casa* casa);
	string toString(void);
private:
	static char CaracteresEstado[];

	Estado estado;
	Tabuleiro* tabuleiro;
	int linha, coluna;
	Peca* peca;
};
