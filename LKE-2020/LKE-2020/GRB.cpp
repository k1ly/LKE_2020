#include "GRB.h"

namespace GRB
{
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* ptr = (int*)&s;
		for (int i = 0; i < psize; i++)
			nt[i] = (GRBALPHABET)ptr[i];
	}
	char* Rule::Chain::GetCChain(char* b)
	{
		for (int i = 0; i < size; i++)
			b[i] = AlphabetToChar(nt[i]);
		b[size] = '\0';
		return b;
	}
	Rule::Rule(GRBALPHABET pnn, int errid, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = errid;
		chains = new Chain[size = psize];
		Chain* ptr = &c;
		for (int i = 0; i < psize; i++)
			chains[i] = ptr[i];
	}
	char* Rule::GetCRule(char* b, short nchain)
	{
		char bchain[200];
		bchain[0] = Chain::AlphabetToChar(nn);
		bchain[1] = '-'; bchain[2] = '>';
		chains[nchain].GetCChain(bchain + 3);
		bchain[strlen(bchain)] = '\0';
		for (int i = 0; i < (int)strlen(bchain); i++)
			b[i] = bchain[i];
		return b;
	}
	short Rule::GetNextChain(GRBALPHABET t, Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottomT;
		rules = new Rule[size = psize];
		Rule* ptr = &r;
		for (int i = 0; i < size; i++)
			rules[i] = ptr[i];
	}
	short Greibach::GetRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		int i = 0;
		for (; i < size && pnn != rules[i].nn; i++);
		if (i < size)
			prule = rules[rc = i];
		return rc;
	}
	Rule Greibach::GetRule(short n)
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	}
	Greibach GetGreibach()
	{
#define T(t) GRB::Rule::Chain::T(t)
#define N(n) GRB::Rule::Chain::N(n)

		Greibach* grb = new Greibach(N('S'), T('$'), 9,

			Rule(N('S'), 200, 14,
				Rule::Chain(4, T('!'), T('a'), T('l'), N('S')),
				Rule::Chain(7, T('!'), T('f'), T('<'), T('>'), T('t'), T('i'), N('S')),
				Rule::Chain(8, T('!'), T('f'), T('<'), N('F'), T('>'), T('t'), T('i'), N('S')),
				Rule::Chain(5, T('m'), T(':'), N('N'), T('e'), T('.')),
				Rule::Chain(7, T('&'), T('t'), T('i'), T('='), T('l'), T('.'), N('S')),
				Rule::Chain(8, T('['), T('l'), T(']'), T('t'), T('i'), T('l'), T('.'), N('S')),

				Rule::Chain(11, T('*'), T('<'), T('>'), T('t'), T('i'), T(':'), T('r'), T('>'), T('>'), N('E'), T('.')),
				Rule::Chain(12, T('*'), T('<'), N('F'), T('>'), T('t'), T('i'), T(':'), T('r'), T('>'), T('>'), N('E'), T('.')),
				Rule::Chain(12, T('*'), T('<'), T('>'), T('t'), T('i'), T(':'), N('N'), T('r'), T('>'), T('>'), N('E'), T('.')),
				Rule::Chain(13, T('*'), T('<'), N('F'), T('>'), T('t'), T('i'), T(':'), N('N'), T('r'), T('>'), T('>'), N('E'), T('.')),
				Rule::Chain(12, T('*'), T('<'), T('>'), T('t'), T('i'), T(':'), T('r'), T('>'), T('>'), N('E'), T('.'), N('S')),
				Rule::Chain(13, T('*'), T('<'), N('F'), T('>'), T('t'), T('i'), T(':'), T('r'), T('>'), T('>'), N('E'), T('.'), N('S')),
				Rule::Chain(13, T('*'), T('<'), T('>'), T('t'), T('i'), T(':'), N('N'), T('r'), T('>'), T('>'), N('E'), T('.'), N('S')),
				Rule::Chain(14, T('*'), T('<'), N('F'), T('>'), T('t'), T('i'), T(':'), N('N'), T('r'), T('>'), T('>'), N('E'), T('.'), N('S'))),
			Rule(N('N'), 201, 32,
				Rule::Chain(6, T('.'), T('.'), T('i'), T('('), T(')'), N('N')),
				Rule::Chain(7, T('.'), T('.'), T('i'), T('('), N('W'), T(')'), N('N')),
				Rule::Chain(6, T('&'), T('t'), T('i'), T('='), N('E'), N('N')),
				Rule::Chain(5, T('&'), T('t'), T('i'), T(','), N('N')),
				Rule::Chain(4, T('i'), T('='), N('E'), N('N')),
				Rule::Chain(5, T('w'), T('<'), T('<'), N('E'), N('N')),
				Rule::Chain(5, T('i'), T('='), N('E'), N('L'), N('N')),
				Rule::Chain(6, T('w'), T('<'), T('<'), N('E'), N('L'), N('N')),
				Rule::Chain(7, T('['), T('l'), T(']'), T('t'), T('i'), T('l'), N('N')),
				Rule::Chain(8, T('s'), T('i'), T('u'), N('E'), T(':'), N('N'), T(';'), N('N')),
				Rule::Chain(10, T('s'), T('i'), T('='), N('E'), T('u'), N('E'), T(':'), N('N'), T(';'), N('N')),
				Rule::Chain(12, T('s'), T('&'), T('t'), T('i'), T('='), N('E'), T('u'), N('E'), T(':'), N('N'), T(';'), N('N')),

				Rule::Chain(6, T('c'), N('E'), T('='), T('>'), N('A'), N('N')),
				Rule::Chain(7, T('c'), N('E'), N('L'), T('='), T('>'), N('A'), N('N')),
				Rule::Chain(4, T('c'), N('E'), N('V'), N('N')),
				Rule::Chain(5, T('c'), N('E'), N('L'), N('V'), N('N')),

				Rule::Chain(5, T('.'), T('.'), T('i'), T('('), T(')')),
				Rule::Chain(6, T('.'), T('.'), T('i'), T('('), N('W'), T(')')),
				Rule::Chain(5, T('&'), T('t'), T('i'), T('='), T('l')),
				Rule::Chain(4, T('&'), T('t'), T('i'), T(',')),
				Rule::Chain(3, T('i'), T('='), N('E')),
				Rule::Chain(4, T('w'), T('<'), T('<'), N('E')),
				Rule::Chain(4, T('i'), T('='), N('E'), N('L')),
				Rule::Chain(5, T('w'), T('<'), T('<'), N('E'), N('L')),
				Rule::Chain(6, T('['), T('l'), T(']'), T('t'), T('i'), T('l')),
				Rule::Chain(7, T('s'), T('i'), T('u'), N('E'), T(':'), N('N'), T(';')),
				Rule::Chain(9, T('s'), T('i'), T('='), N('E'), T('u'), N('E'), T(':'), N('N'), T(';')),
				Rule::Chain(11, T('s'), T('&'), T('t'), T('i'), T('='), N('E'), T('u'), N('E'), T(':'), N('N'), T(';')),

				Rule::Chain(5, T('c'), N('E'), T('='), T('>'), N('A')),
				Rule::Chain(6, T('c'), N('E'), N('L'), T('='), T('>'), N('A')),
				Rule::Chain(3, T('c'), N('E'), N('V')),
				Rule::Chain(4, T('c'), N('E'), N('L'), N('V'))),
			Rule(N('V'), 202, 4,
				Rule::Chain(4, T('='), T('>'), N('A'), T(';')),
				Rule::Chain(9, T('='), T('>'), N('A'), T(','), T('g'), T('='), T('>'), N('A'), T(';')),
				Rule::Chain(7, T('='), T('>'), N('A'), T(','), T('c'), N('E'), N('V')),
				Rule::Chain(8, T('='), T('>'), N('A'), T(','), T('c'), N('E'), N('L'), N('V'))),
			Rule(N('A'), 203, 7,
				Rule::Chain(1, T('b')),
				Rule::Chain(5, T('.'), T('.'), T('i'), T('('), T(')')),
				Rule::Chain(6, T('.'), T('.'), T('i'), T('('), N('W'), T(')')),
				Rule::Chain(3, T('i'), T('='), N('E')),
				Rule::Chain(4, T('w'), T('<'), T('<'), N('E')),
				Rule::Chain(4, T('i'), T('='), N('E'), N('L')),
				Rule::Chain(5, T('w'), T('<'), T('<'), N('E'), N('L'))),
			Rule(N('E'), 204, 14,
				Rule::Chain(1, T('i')),
				Rule::Chain(1, T('l')),
				Rule::Chain(4, T('i'), T('['), T('i'), T(']')),
				Rule::Chain(4, T('i'), T('['), T('l'), T(']')),
				Rule::Chain(3, T('('), N('E'), T(')')),
				Rule::Chain(3, T('i'), T('('), T(')')),
				Rule::Chain(4, T('i'), T('('), N('W'), T(')')),

				Rule::Chain(2, T('i'), N('M')),
				Rule::Chain(2, T('l'), N('M')),
				Rule::Chain(5, T('i'), T('['), T('i'), T(']'), N('M')),
				Rule::Chain(5, T('i'), T('['), T('l'), T(']'), N('M')),
				Rule::Chain(4, T('('), N('E'), T(')'), N('M')),
				Rule::Chain(4, T('i'), T('('), T(')'), N('M')),
				Rule::Chain(5, T('i'), T('('), N('W'), T(')'), N('M'))),
			Rule(N('M'), 205, 2,
				Rule::Chain(2, T('v'), N('E')),
				Rule::Chain(3, T('v'), N('E'), N('M'))),
			Rule(N('L'), 206, 4,
				Rule::Chain(2, T('?'), N('E')),
				Rule::Chain(2, T('!'), N('E')),
				Rule::Chain(2, T('<'), N('E')),
				Rule::Chain(2, T('>'), N('E'))),
			Rule(N('F'), 207, 2,
				Rule::Chain(2, T('t'), T('i')),
				Rule::Chain(4, T('t'), T('i'), T(','), N('F'))),
			Rule(N('W'), 208, 8,
				Rule::Chain(1, T('i')),
				Rule::Chain(1, T('l')),
				Rule::Chain(3, T('i'), T(','), N('W')),
				Rule::Chain(3, T('l'), T(','), N('W')),

				Rule::Chain(4, T('i'), T('['), T('i'), T(']')),
				Rule::Chain(4, T('i'), T('['), T('l'), T(']')),
				Rule::Chain(6, T('i'), T('['), T('i'), T(']'), T(','), N('W')),
				Rule::Chain(6, T('i'), T('['), T('l'), T(']'), T(','), N('W')))
		);
		return *grb;
	}
}