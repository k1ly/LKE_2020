#pragma once
#include "Tables.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace Polish
{
	void GetPolish(Tables::TABLE& tbl);
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable &idtable);
}