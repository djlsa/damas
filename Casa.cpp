#include "StdAfx.h"

#include "Casa.h"

char Casa::CaracteresEstado[9] = { '²', ' ', '\\', '/', 'O' };

Casa::Casa(Tabuleiro* tabuleiro, int linha, int coluna) : peca(0)
{
	this->tabuleiro = tabuleiro;
	this->linha = linha;
	this->coluna = coluna;
	this->setEstadoOriginal(true);
}

Casa::~Casa(void)
{
}

void Casa::setEstado(Estado estado)
{
	if(estado == PECA_CAPTURADA)
		this->peca = 0;
	this->estado = estado;
}

void Casa::setEstadoOriginal(bool pecas)
{
	if( (linha % 2 == 0 && coluna % 2 != 0) || (linha % 2 != 0 && coluna % 2 == 0) )
	{
		this->estado = QUADRADO_BRANCO;
	}
	else
	{
		this->estado = QUADRADO_PRETO;
		if(pecas)
		{
			int totalcasas = LINHAS * COLUNAS / 2;
			int ncasa = (linha * COLUNAS + coluna) / 2;
			if(ncasa < PECAS_POR_JOGADOR)
			{
				this->peca = new Peca(PEAO, PRETA);
			}
			else if (ncasa >= totalcasas - PECAS_POR_JOGADOR)
			{
				this->peca = new Peca(PEAO, BRANCA);
			}
		}
	}
}

Estado Casa::getEstado()
{
	return this->estado;
}

int Casa::getLinha()
{
	return this->linha;
}

int Casa::getColuna()
{
	return this->coluna;
}

Peca* Casa::getPeca()
{
	return this->peca;
}

void Casa::moverPeca(Casa* casa)
{
	casa->peca = this->peca;
	this->peca = 0;
}

string Casa::toString(void)
{
	string s = "";
	s += this->CaracteresEstado[this->getEstado()];
	return this->peca != 0 ? this->peca->toString() : s;
}