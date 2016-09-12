#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

#include "Peca.h"

#define LINHAS 8
#define COLUNAS 8

class Casa;
class Tabuleiro
{
public:
	Tabuleiro(void);
	~Tabuleiro(void);
	Casa* Tabuleiro::getCasa(int linha, int coluna);
	bool temJogadasPossiveis(Cor cor);
	vector<vector<Casa*>> getJogadasObrigatorias(Cor cor);
	bool moverPeca(Casa* casa1, Casa* casa2);
	string toString(bool limpar);
private:
	vector<vector<Casa*>> tabuleiro;
	map<Cor, vector<Casa*>> pecas;
	bool isJogadaValida(Casa* casa1, Casa* casa2);
};
