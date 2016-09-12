#include "StdAfx.h"

#include "Peca.h"

Peca::Peca(Tipo tipo, Cor cor)
{
	this->cor = cor;
	this->setTipo(tipo);
}

Peca::~Peca(void)
{
}

void Peca::setTipo(Tipo tipo)
{
	this->tipo = tipo;
}

Tipo Peca::getTipo()
{
	return this->tipo;
}

void Peca::setCor(Cor cor)
{
	this->cor = cor;
}

Cor Peca::getCor()
{
	return this->cor;
}

string Peca::toString()
{
	return cor == BRANCA ?
		tipo == PEAO ? "b" : "B" :
		tipo == PEAO ? "p" : "P";
}