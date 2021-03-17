#include "FST.h"
#include <iostream>

namespace FST
{
	RELATION::RELATION(char c = 0, short nn = 0)
	{
		symbol = c;
		nnode = nn;
	}

	NODE::NODE()
	{
		n_relation = 0;
		relations = NULL;
	}
	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* ptr = &rel;
		relations = new RELATION[n_relation];
		for (int i = 0; i < n_relation; i++)
			relations[i] = ptr[i];
	}

	FST::FST(char* s, short ns, NODE n, ...)
	{
		string = s;
		position = 0;
		nstates = ns;
		rstates = new short[nstates];
		for (int i = 0; i < nstates; i++)
			rstates[i] = -1;
		rstates[0] = 0;
		NODE* ptr = &n;
		nodes = new NODE[nstates];
		for (int i = 0; i < nstates; i++)
			nodes[i] = ptr[i];
	}

	bool step(FST &fst, short* &rstates)
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
		return rc;
	}
	bool execute(FST &fst)
	{
		fst.position = 0;
		short length = (short)strlen(fst.string);
		short* rstates = new short[fst.nstates];
		for (int i = 0; i < fst.nstates; i++)
			rstates[i] = -1;
		bool rc = true;
		while (fst.position < length && rc)
		{
			rc = step(fst, rstates);
			fst.position++;
		}
		delete[] rstates;
		return (rc?(fst.rstates[fst.nstates - 1] == length):rc);
	}
}