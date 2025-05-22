#pragma once
#include "../TProcuraAdversa.h"

enum EVariantesJogo {
	regular,  // jogar em qualquer casa livre
	gravidade, // jogar na linha de baixo, ou por cima de uma pe�a
	// ideias para outras variantes:
	jogadaDupla, // jogam sempre duas pe�as, mas a segunda pe�a + serve para ambos
	bordasLigadas, // linha de cima liga com a de baixo, coluna da esquerda liga com a da direita
	zonasOcupadas // algumas c�culas j� est�o ocupadas e ficam invi�veis para uso
};

typedef struct SJogoEmLinha {
	int K; // n�mero de marcas em linha
	int N; // n�mero de linhas do tabuleiro
	int M; // n�mero de colunas do tabuleiro
	EVariantesJogo variante; // qual a variante
} TJogoEmLinha;

///////////////////////////////////////////////////////////////////////////////
//	CJogo4emLinha class
///////////////////////////////////////////////////////////////////////////////
//	Author: Jos� Coelho
//	Last revision: 2009-03-30
//	Description: 
///////////////////////////////////////////////////////////////////////////////
class CJogoEmLinha :
	public TProcuraAdversa
{
public:
	TVector<char> tabuleiro;
public:
	CJogoEmLinha(void);
	~CJogoEmLinha(void);

	// dados da inst�ncia
	static TJogoEmLinha inst; 

	// Cria um objecto que � uma c�pia deste
	TProcuraConstrutiva* Duplicar(void);
	// Fica com uma c�pia de objecto
	void Copiar(TProcuraConstrutiva*objecto);
	// Coloca o objecto no estado inicial da procura
	void SolucaoVazia(void);
	// Coloca em sucessores a lista de objectos sucessores (s�o alocados neste m�todo e t�m de ser apagados)
	// O custo n�o necessita de ser preenchido, caso seja sempre unit�rio
	// chamar o m�todo desta classe ap�s adicionar os sucessores para actualizar geracoes e expansoes
	void Sucessores(TVector<TNo>&sucessores);
	// Retorna verdade caso o estado actual seja um estado objectivo
	bool SolucaoCompleta(void);
	// Escrever informa��o de debug sobre o objecto currente 
	// (utilizar vari�vel TProcuraConstrutiva::debug para seleccionar o detalhe pretendido)
	void Debug(void);

	void ResetParametros();


	// Redefinir para poder utilizar os algoritmos informados
	// O custo desde o n� inicial � tido em conta, esta fun��o deve devolver o custo estimado
	// nunca sobre estimando, deste estado at� ao n� final mais pr�ximo (� um m�nimo)
	// chamar para actualia��o de avaliacoes
	int Heuristica(void);

	const char* Acao(TNo sucessor);
	void TesteManual(const char* nome);
	void Codifica(uint64_t estado[OBJETO_HASHTABLE]);
	int Codigo(char peca) { return peca == 'x' ? 1 : (peca == 'o' ? 2 : 3); }
	int Indice(int i, int j) { return i * inst.M + j; }
	char Casa(int i, int j) { return tabuleiro[Indice(i, j)]; }
	void Casa(int i, int j, char valor) { tabuleiro[Indice(i, j)] = valor; }
	bool VerLinha(int i, int j, int di, int dj);
};
