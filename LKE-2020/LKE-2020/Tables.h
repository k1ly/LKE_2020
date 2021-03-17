#pragma once
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "Lexem.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#define TOKEN_MAXSIZE 30

namespace Tables
{
	struct TABLE
	{
		std::ofstream* stream;
		LT::LexTable lt;
		IT::IdTable it;
	};
	TABLE GetTables(Parm::PARM& parm, In::IN& in);
	void WriteTable(TABLE& tbl, const char* c);
	void Close(TABLE& tbl);
}