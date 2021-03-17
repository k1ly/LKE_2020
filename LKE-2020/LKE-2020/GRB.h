#pragma once
#include "Error.h"
#include <iostream>

typedef short GRBALPHABET;

namespace GRB
{
	struct Rule
	{
		GRBALPHABET nn;
		int iderror;
		short size;
		struct Chain
		{
			short size;
			GRBALPHABET* nt;
			Chain() { size = 0; nt = 0; };
			Chain(short psize, GRBALPHABET s, ...);
			char* GetCChain(char* b);
			static GRBALPHABET T(char t) { return GRBALPHABET(t); };
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };
			static bool IsT(GRBALPHABET s) { return s > 0; };
			static bool IsN(GRBALPHABET s) { return !IsT(s); };
			static char AlphabetToChar(GRBALPHABET s) { return IsT(s) ? char(s) : char(-s); };
		}*chains;
		Rule() { nn = 0, iderror = 0; size = 0; chains = 0; };
		Rule(GRBALPHABET pnn, int errid, short psize, Chain c, ...);
		char* GetCRule(char* b, short nchain);
		short GetNextChain(GRBALPHABET t, Chain& pchain, short j);
	};
	struct Greibach
	{
		short size;
		GRBALPHABET startN;
		GRBALPHABET stbottomT;
		Rule* rules;
		Greibach() { size = 0; startN = 0; stbottomT = 0; rules = 0; }
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		short GetRule(GRBALPHABET pnn, Rule& prule);
		Rule GetRule(short n);
	};
	Greibach GetGreibach();
}