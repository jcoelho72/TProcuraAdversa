#pragma once
#include "TProcuraConstrutiva/TProcuraConstrutiva.h"

enum EParametrosAdversa { ordenarSucessores = parametrosConstrutivas,
	podaHeuristica, podaCega, parametrosAdversas };

// tipo de valor resultante do minimax com cortes alfa/beta
enum ETipoValor { 
	exato, // o valor foi calculado sem cortes, ou seja, não sofreu influência de alfa ou beta;
	lowerbound, // o valor foi afetado por um corte de beta (ou seja, ele é pelo menos esse valor, mas pode ser maior);
	upperbound // o valor foi afetado por um corte de alfa (ou seja, ele é no máximo esse valor, mas pode ser menor).
};

// registo do valor de um estado, em procuras anteriores 
typedef struct SValorEstado {
	int valor;
	int nivel; // 0 - valor heurístico, -1 - inválido
	ETipoValor tipo; 
} TValorEstado;

///////////////////////////////////////////////////////////////////////////////
//	TProcuraAdversa class
///////////////////////////////////////////////////////////////////////////////
//	Author: José Coelho
//	Last revision: 2025-01-30
//	Description:
//    Superclasse de procuras no espaço das soluções parciais (a solução é construida).
//    Os custos devem ser ignorados, apenas o valor da funcao Heuristica é utilizado. 
//    O valor infinito é definido numa variavel global à classe,
//    e deve ser alterado conforme o problema, significando vitoria/derrota.
//    Se não houver sucessores, o estado é terminal e o retorno da funcao heuristica
//    deve ser exacto: -infinito ganham pretas, 0 empate, +infinito ganham as brancas
///////////////////////////////////////////////////////////////////////////////
class TProcuraAdversa :
	public TProcuraConstrutiva
{
public:
	// o jogador actual deve minimizar o custo (ou maximizar caso tenha o valor falso)
	bool minimizar;
	// valor de infinito (vitoria/derrota), omissao 1000
	static int infinito;
	// controlo para indicar se a procura foi realizada de forma completa (c.c. foi cortada)
	static bool completo;
	// profundidade máxima no método iterativo
	static int nivelOK;

public:
	TProcuraAdversa(void);
	~TProcuraAdversa(void);

	// Método para inicializar os parâmetros (redefinir se forem adicionados parâmetros específicos)
	void ResetParametros();

	///////////////////////////////////////////////////////////////////////////////
	// Algoritmo MiniMax
	///////////////////////////////////////////////////////////////////////////////
	// retorna o valor do estado actual, apos procura de profundidade nivel
	int MiniMax(int nivel = 4);

	///////////////////////////////////////////////////////////////////////////////
	// Algoritmo MiniMaxAlfaBeta
	///////////////////////////////////////////////////////////////////////////////
	// retorna o valor do estado actual, apos procura de profundidade nivel
	// idêntico a MiniMax
	int MiniMaxAlfaBeta(int nivel = 4, int alfa = -infinito, int beta = +infinito);

	// utilizar para executar testes empíricos, utilizando todas as instâncias,
	// Utiliza as configurações existentes, ou parâmetros atuais
	// Efetua um torneio entre configurações
	void TesteEmpirico(int inicio = -1, int fim = -1, bool mostrarSolucoes = true);

	int ExecutaAlgoritmo();

	int Heuristica(void);

	// chamar em CSubProblema::Heuristica() para verificar se a heurística já existe, ou precisa de ser calculada
	bool ExisteHeuritica(void);

	// Utilitário para calculo de uma heurística standard em jogos simples (tipicamente sem empates):
	// - calcular o número de ameaças de vitória, para cada lado, de menor comprimento:
    //   - qMin - vetor com número de ameaças (1 ou mais) a 1 jogada (na primeira posição), a 2 (na segunda posição), e assim sucessivamente; 
    //   - qMax - vetor com número de ameaças (1 ou mais) a 1 jogada (na primeira posição), a 2 (na segunda posição), e assim sucessivamente; 
	int MaiorAmeaca(TVector<int>& qMin, TVector<int>& qMax, int maxAmeaca);

protected:
	// fim da procura, por corte de nível (ou não haver sucessores), retornar heurística
	int NoFolha(bool nivel); 

	// verifica se há um corte alfa/beta, atualizando alfa e beta
	bool CorteAlfaBeta(int valor, int& alfa, int& beta);

	// iteração, aumentando o nível progressivamente
	int MetodoIterativo(int alfaBeta);


	void OrdenarSucessores(TVector<TNo>& sucessores, TVector<int>& id, int nivel);

	// hashtable
	void SubstituirHT(int indice); // necessário redefinir para invalidar valorHT 
	bool ExisteHT(); // necessário redefinir par não remover estados (reutilizar o valor)
	static TValorEstado valorHT[TAMANHO_HASHTABLE]; // hashtable / valor e nível obtido
	// índice obtido na HT, se positivo
	int indiceHT;
	// ler ou gravar o melhor valor conhecido
	bool ValorEstado(TValorEstado& valor, int operacao);

	bool Utilizavel(TValorEstado& valor, int nivel, int alfa, int beta);
};
