#include "IT.h"

namespace IT
{
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char funcblock[ID_SIZE], char longid[ID_SIZE], int cycleblock, int type)
	{
		int rc = TI_NULLIDX;
		for (int i = 0; i < idtable.size; i++)
		{
			if ((idtable.table[i].idtype == IT::L &&
				((!strcmp(idtable.table[i].value.vstr->str, longid) && idtable.table[i].iddatatype == IT::NOTE && (type == 32 || type == 33)) ||
					(idtable.table[i].value.vint == atoi(longid) && idtable.table[i].iddatatype == IT::UNIT && type == 34) ||
					(idtable.table[i].value.vint == atoi(longid) && idtable.table[i].iddatatype == IT::IDLE && (type == 30 || type == 31)))) ||
				(idtable.table[i].idtype == IT::P && !strcmp(idtable.table[i].id, id) &&
					!strcmp(idtable.table[i].realm, funcblock)) ||
				(idtable.table[i].idtype == IT::F &&
					(!strcmp(idtable.table[i].id, id))) ||
				((idtable.table[i].idtype == IT::V) && !strcmp(idtable.table[i].id, id) &&
					(idtable.table[i].block == -1 || idtable.table[i].block == cycleblock) &&
					(!strcmp(idtable.table[i].realm, "") || !strcmp(idtable.table[i].realm, funcblock))))
			{
				rc = i;
				break;
			}
		}
		return rc;
	}

	IdTable Create(int size)
	{
		if (size >= TI_MAXSIZE)
			throw ERROR_THROW(22);
		IdTable idt;
		idt.maxsize = size;
		idt.size = 0;
		idt.table = new Entry[size];
		return idt;
	}

	void Add(IdTable &idtable, Entry &entry)
	{
		if (idtable.maxsize >= TI_MAXSIZE)
			throw ERROR_THROW(22);
		Entry* table;
		if (idtable.size == idtable.maxsize)
		{
			table = new Entry[idtable.maxsize + 10];
			for (int i = 0; i < idtable.maxsize; i++)
				table[i] = idtable.table[i];
			idtable.maxsize += 10;
			delete[] idtable.table;
			idtable.table = table;
		}
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable &idtable, int n)
	{
		Entry* rc = new Entry;
		if (!(n < 0) && n < idtable.size)
			*rc = idtable.table[n];
		else throw ERROR_THROW(24);
		return *rc;
	}

	void Delete(IdTable &idtable)
	{
		idtable.maxsize = 0;
		idtable.size = 0;
		delete[] idtable.table;
		idtable.table = nullptr;
	}
}