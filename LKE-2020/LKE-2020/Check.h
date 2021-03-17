#pragma once
#include "Tables.h"
#include "Log.h"
#include <stack>
#include <iostream>

namespace Semantic
{
	bool TypeCheck(Log::LOG& log, Tables::TABLE& tbl);
	bool ParamCheck(Log::LOG &log, Tables::TABLE &tbl);
	bool FuncRet(Log::LOG& log, Tables::TABLE &tbl);
	bool StdCheck(Log::LOG& log, Tables::TABLE& tbl);
	int SemanticAnalysis(Log::LOG& log, Tables::TABLE &tbl);
}
