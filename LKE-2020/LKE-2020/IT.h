#pragma once
#include "Error.h"
#include <iostream>
#define ID_MAXSIZE 15
#define ID_SIZE 30
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x0000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255
#define TI_ARR_MAXSIZE 50

namespace IT
{
	enum IDDATATYPE { UNIT = 1, NOTE, IDLE, ARRAY, MAIN};
	enum IDTYPE { V = 1, F, P, L, O };

	struct Entry
	{
		int idxfirstLEX;
		char id[ID_SIZE];
		char realm[ID_SIZE];
		int block;
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union
		{
			int vint;
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE - 1];
			}vstr[TI_STR_MAXSIZE];
			struct Array
			{
				int len;
				int val[TI_ARR_MAXSIZE - 1];
			}varr[TI_ARR_MAXSIZE];
		}value;
	};

	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char funcblock[ID_SIZE], char longid[ID_SIZE], int cycleblock, int type);
	IdTable Create(int size);
	void Add(IdTable& idtable, Entry& entry);
	Entry GetEntry(IdTable& idtable, int n);
	void Delete(IdTable& idtable);
}