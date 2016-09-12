#pragma once

#include <string>

using namespace std;

#define PECAS_POR_JOGADOR 12

enum Cor { BRANCA, PRETA };
enum Tipo { PEAO, DAMA };

class Peca
{
private:
	Tipo tipo;
	Cor cor;
public:
	Peca(Tipo tipo, Cor cor);
	~Peca(void);
	void setTipo(Tipo tipo);
	Tipo getTipo();
	void setCor(Cor cor);
	Cor getCor();
	string toString();
};
