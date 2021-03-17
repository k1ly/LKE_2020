#pragma once
#include "Error.h"
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff

namespace LT
{
	struct Entry
	{
		char lexema;
		int sn;
		int idxTI;
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable &lextable, Entry &entry);
	Entry GetEntry(LexTable &lextable, int n);
	void Delete(LexTable &lextable);
}