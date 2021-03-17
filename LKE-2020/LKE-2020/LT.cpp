#include "LT.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size >= LT_MAXSIZE)
			throw ERROR_THROW(21);
		LexTable lext;
		lext.maxsize = size;
		lext.size = 0;
		lext.table = new Entry[size];
		return lext;
	}

	void Add(LexTable &lextable, Entry &entry)
	{
		if (lextable.maxsize >= LT_MAXSIZE)
			throw ERROR_THROW(21);
		Entry* table = nullptr;
		if (lextable.size == lextable.maxsize)
		{
			table = new Entry[lextable.maxsize + 10];
			for (int i = 0; i < lextable.maxsize; i++)
				table[i] = lextable.table[i];
			lextable.maxsize += 10;
			delete[] lextable.table;
			lextable.table = table;
		}
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable &lextable, int n)
	{
		Entry* rc = new Entry;
		if (!(n < 0) && n < lextable.size)
			*rc = lextable.table[n];
		else throw ERROR_THROW(23);
		return *rc;
	}

	void Delete(LexTable &lextable)
	{
		lextable.maxsize = 0;
		lextable.size = 0;
		delete[] lextable.table;
		lextable.table = nullptr;
	}
}