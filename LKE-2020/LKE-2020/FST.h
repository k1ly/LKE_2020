#pragma once
namespace FST
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(char c, short nn);
	};
	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE();
		NODE(short n, RELATION rel, ...);
	};
	struct FST
	{
		char* string;
		short position;
		short nstates;
		short* rstates;
		NODE* nodes;
		FST(char* s, short ns, NODE n, ...);
	};
	bool execute(FST &fst);
}
