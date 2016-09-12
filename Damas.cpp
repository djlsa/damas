// Damas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

#include "Tabuleiro.h"
#include "Casa.h"

int _tmain(int argc, _TCHAR* argv[])
{
	bool terminado = false;
	Cor jogador = BRANCA;
	cout << "Indique a peca a jogar e a casa para onde mover (ex: A 1 B 2)" << endl;
	Tabuleiro* tabuleiro = new Tabuleiro();
	cout << tabuleiro->toString(false);
	while(!terminado)
	{
		vector<vector<Casa*>> jogadasObrigatorias = tabuleiro->getJogadasObrigatorias(jogador);
		cout << (jogador == BRANCA ? "BRANCAS" : "PRETAS") << "> ";
		char linha1, linha2;
		int coluna1, coluna2;
		cin >> linha1 >> coluna1 >> linha2 >> coluna2;
		if(cin.fail())
		{
			cout << "Problema no input" << endl;
		}
		else
		{
			if(linha1 >= 'a')
				linha1 -= 32;
			linha1 -= 'A';
			coluna1--;
			if(linha2 >= 'a')
				linha2 -= 32;
			linha2 -= 'A';
			coluna2--;

			int nJogadasObrigatorias = jogadasObrigatorias.size();
			if(nJogadasObrigatorias > 0)
			{
				bool fezJogadaObrigatoria = false;
				for(int i = 0; i < nJogadasObrigatorias; i++)
				{
					vector<Casa*> jogada = jogadasObrigatorias[i];
					Casa* casa1 = jogada[0];
					Casa* casa2 = jogada[1];
					if(linha1 == casa1->getLinha() && coluna1 == casa1->getColuna() && linha2 == casa2->getLinha() && coluna2 == casa2->getColuna())
					{
						fezJogadaObrigatoria = true;
						break;
					}
					if(!fezJogadaObrigatoria)
						cout << "Tem de fazer a jogada obrigatoria" << endl;
				}
			}


			Casa* casa1 = tabuleiro->getCasa(linha1, coluna1);
			Casa* casa2 = tabuleiro->getCasa(linha2, coluna2);
			Peca* peca = casa1->getPeca();

			if(peca != 0 && peca->getCor() == jogador && tabuleiro->moverPeca(casa1, casa2))
			{
				if(tabuleiro->getJogadasObrigatorias(jogador).size() > 0)
				{
					cout << endl << tabuleiro->toString(false);
					cout << "O jogador atual pode fazer mais uma captura";
				}
				cout << endl << tabuleiro->toString(true);
				jogador = jogador == BRANCA ? PRETA : BRANCA;
				if(!tabuleiro->temJogadasPossiveis(jogador))
				{
					terminado = true;
					cout << "Jogo terminado, vencedor: " << (jogador == BRANCA ? "PRETAS" : "BRANCAS") << endl;
				}
			}
			else
			{
				cout << "Nao e' possivel efetuar essa jogada" << endl;
			}
		}
	}
	return 0;
}

