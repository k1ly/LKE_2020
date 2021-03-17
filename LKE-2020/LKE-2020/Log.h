#pragma once
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include <time.h>
#include <fstream>
#include <iostream>

namespace Log
{
	struct LOG
	{
		std::ofstream* stream;
	};
	static const LOG INITLOG = { NULL };
	LOG GetLog(Parm::PARM &parm);
	void WriteLine(LOG log, const char* c, ...);
	void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteIn(LOG log, In::IN &in);
	void WriteParm(LOG log, Parm::PARM &parm);
	void WriteError(LOG log, Error::ERROR error);
	void Close(LOG &log);
}