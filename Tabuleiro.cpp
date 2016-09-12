#include "StdAfx.h"
#include <iostream>
#include <sstream>

#include "Tabuleiro.h"
#include "Casa.h"
#include "Peca.h"

using namespace std;

Tabuleiro::Tabuleiro(void) : tabuleiro(LINHAS, COLUNAS)
{
	for(int i = 0; i < LINHAS; i++)
	{
		for(int j = 0; j < COLUNAS; j++)
		{
			Casa* casa = new Casa(this, i, j);
			this->tabuleiro[i][j] = casa;
			Peca* peca = casa->getPeca();
			if(peca != 0)
				this->pecas[peca->getCor()].push_back(casa);
		}
	}
}

Tabuleiro::~Tabuleiro(void)
{
	for(int i = 0; i < LINHAS; i++)
	{
		for(int j = 0; j < COLUNAS; j++)
		{
			delete this->tabuleiro[i][j];
		}
	}
}

Casa* Tabuleiro::getCasa(int linha, int coluna)
{
	if(linha >= 0 && coluna >= 0 && linha < LINHAS && coluna < COLUNAS)
		return this->tabuleiro[linha][coluna];
	return 0;
}

bool Tabuleiro::isJogadaValida(Casa* casa1, Casa* casa2)
{
	Peca* peca1 = casa1->getPeca();
	Peca* peca2 = casa2->getPeca();
	if(peca1 != 0 && peca2 == 0)
	{
		Tipo tipo = peca1->getTipo();
		Cor cor = peca1->getCor();

		int
			linha1 = casa1->getLinha(), coluna1 = casa1->getColuna(),
			linha2 = casa2->getLinha(), coluna2 = casa2->getColuna();
		int distLinha = linha1 - linha2;
		int distColuna = abs( coluna1 - coluna2 );

		if(tipo == PEAO)
		{
			if( ((cor == PRETA && distLinha == -1) || (cor == BRANCA && distLinha == 1)) && distColuna == 1)
				return true;
			else if( ((cor == PRETA && distLinha == -2) || (cor == BRANCA && distLinha == 2)) && distColuna == 2)
			{
				int linhaIntermedia = cor == BRANCA ? linha1 - 1 : linha1 + 1;
				int colunaIntermedia = coluna1 > coluna2 ? coluna1 - 1 : coluna2 - 1;
				Peca* pecaCapturada = this->getCasa(linhaIntermedia, colunaIntermedia)->getPeca();
				if(pecaCapturada != 0 && pecaCapturada->getCor() != cor)
					return true;
			}
		}
		else if(tipo == DAMA)
		{
			if(distLinha = abs(distLinha) == distColuna)
			{
				int dirHorizontal = coluna2 > coluna1 ? 1 : -1;
				int dirVertical = linha2 > linha1 ? 1 : -1;
				for(int i = 1; i < distLinha - 1; i++)
				{
					if(this->getCasa(linha1 + i*dirVertical, coluna1 + i*dirHorizontal)->getPeca() != 0)
						return false;
				}
				int linhaAdjacente = linha2 + dirVertical;
				int colunaAdjacente = coluna2 + dirHorizontal;
				Peca* pecaCapturada = this->getCasa(linhaAdjacente, colunaAdjacente)->getPeca();
				if(pecaCapturada == 0 || pecaCapturada->getCor() != cor)
					return true;
			}
		}
	}
	return false;
}

bool Tabuleiro::temJogadasPossiveis(Cor cor)
{
	for(int i = 0, numeroPecas = this->pecas[cor].size(); i < numeroPecas; i++)
	{
		Casa* peca = this->pecas[cor][i];
		for(int linha = -2; linha <= 2; linha++)
		{
			for(int coluna = -2; coluna <= 2; coluna++)
			{
				Casa* peca2 = this->getCasa(peca->getLinha() + linha, peca->getColuna() + coluna);
				if(peca2 != 0 && this->isJogadaValida(peca, peca2))
					return true;
			}
		}
	}
	return false;
}

vector<vector<Casa*>> Tabuleiro::getJogadasObrigatorias(Cor cor)
{
	vector<vector<Casa*>> jogadas;
	for(int i = 0, numeroPecas = this->pecas[cor].size(); i < numeroPecas; i++)
	{
		vector<Casa*> jogadasPeca;
		Casa* casa = this->pecas[cor][i];
		Peca* peca = casa->getPeca();
		if(peca != 0)
		{
			Tipo tipo = peca->getTipo();
			if(tipo == PEAO)
			{
				int dirVertical = cor == PRETA ? 1 : -1;
				for(int coluna = -2; coluna <= 2; coluna += 4)
				{
					int dirHorizontal = coluna < 0 ? -1 : 1;
					Casa* adjacente = this->getCasa(casa->getLinha() + 1 * dirVertical, casa->getColuna() + dirHorizontal);
					if(adjacente != 0)
					{
						Peca* peca = adjacente->getPeca();
						if(peca != 0 && peca->getCor() != cor)
						{
							Casa* casa2 = this->getCasa(casa->getLinha() + 2 * dirVertical, casa->getColuna() + coluna);
							if(casa2 != 0 && this->isJogadaValida(casa, casa2))
							{
								jogadasPeca.push_back(casa);
								jogadasPeca.push_back(casa2);
							}
						}
					}
				}
			}
			else if(tipo == DAMA)
			{
			}
		}
		if(jogadasPeca.size() > 0)
			jogadas.push_back(jogadasPeca);
	}
	return jogadas;
}

bool Tabuleiro::moverPeca(Casa* casa1, Casa* casa2)
{
	if(this->isJogadaValida(casa1, casa2))
	{
		int
			linha1 = casa1->getLinha(), coluna1 = casa1->getColuna(),
			linha2 = casa2->getLinha(), coluna2 = casa2->getColuna();
		int dirHorizontal = coluna2 > coluna1 ? 1 : -1;
		int dirVertical = linha2 > linha1 ? 1 : -1;
		Estado movimento = dirHorizontal == dirVertical ? MOVIMENTO_NO_SE : MOVIMENTO_SO_NE;
		casa1->setEstado(movimento);
		for(int i = 1, distLinha = abs(linha1 - linha2); i < distLinha; i++)
		{
			Casa* casa = this->getCasa(linha1 + i*dirVertical, coluna1 + i*dirHorizontal);
			Peca* peca = casa->getPeca();
			if(peca == 0)
				casa->setEstado(movimento);
			else
			{
				Cor cor = peca->getCor();
				for(int j = 0, numeroPecas = this->pecas[cor].size(); j < numeroPecas; j++)
				{
					if(this->pecas[cor][j] == casa)
					{
						this->pecas[cor].erase(this->pecas[cor].begin() + j);
						break;
					}
				}
				casa->setEstado( PECA_CAPTURADA );
			}
		}
		casa1->moverPeca(casa2);
		Cor cor = casa2->getPeca()->getCor();
		for(int i = 0, numeroPecas = this->pecas[cor].size(); i < numeroPecas; i++)
		{
			if(this->pecas[cor][i] == casa1)
				this->pecas[cor][i] = casa2;
		}
		if(linha2 == 0 || linha2 == LINHAS - 1)
			casa2->getPeca()->setTipo(DAMA);
		return true;
	}
	return false;
}

string Tabuleiro::toString(bool limpar)
{
	stringstream s;
	s << ' ';
	for(int j = 0; j < COLUNAS; j++)
	{
		s << j + 1;
	}
	s << endl;
	for(int i = 0; i < LINHAS; i++)
	{
		s << (char) ('A' + i);
		for(int j = 0; j < COLUNAS; j++)
		{
			Casa* c = tabuleiro[i][j];
			s << c->toString();
			if(limpar && c->getPeca() == 0)
				c->setEstadoOriginal(false);
		}
		s << endl;
	}
	return s.str();
}