#include "Log.h"
#pragma warning(disable: 4996)
using namespace std;

namespace Log
{
	LOG GetLog(Parm::PARM &parm)
	{
		LOG* log = new LOG;
		log->stream = new ofstream;
		log->stream->open(parm.log);
		if (log->stream->fail())
			throw ERROR_THROW(12);
		return *log;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			std::wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << endl;
	}
	void WriteLog(LOG log)
	{
		tm* timeinfo;
		time_t ttime;
		time(&ttime);
		timeinfo = localtime(&ttime);
		char temp[100];
		strftime(temp, sizeof(temp), "\n-------- ПРОТОКОЛ -----------\n---- %d.%m.%y %T ------\n", timeinfo);
		*log.stream << temp;
	}
	void WriteIn(LOG log, In::IN &in)
	{
		*log.stream << "\n----- Исходные данные -------\n\n";
		*log.stream << in.table[0].line << ":	";
		for (int i = 0; in.text[i] != IN_CODE_ENDS; i++)
		{
			*log.stream << in.text[i];
			if (in.text[i] == IN_CODE_SEP)
				*log.stream << endl << in.table[i + 1].line << ":	";
		}
		*log.stream << "\n\nВсего символов: " << in.size
			<< "\nВсего строк: " << in.lines
			<< "\nПропущено: " << in.ignore << endl;
	}
	void WriteParm(LOG log, Parm::PARM &parm)
	{
		char i[PARM_MAX_SIZE];
		char o[PARM_MAX_SIZE];
		char l[PARM_MAX_SIZE];
		std::wcstombs(i, parm.in, PARM_MAX_SIZE);
		std::wcstombs(o, parm.out, PARM_MAX_SIZE);
		std::wcstombs(l, parm.log, PARM_MAX_SIZE);
		*log.stream << "\n-------- Параметры ----------\n\n-in: " << i
			<< "\n-out: " << o
			<< "\n-log: " << l << endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream)
		{
			*log.stream << "\nОшибка " << error.id
				<< ": " << error.message;
			if (!(error.inext.line < 0))
				*log.stream << ",\nСтрока " << error.inext.line;
			if (!(error.inext.col < 0))
				*log.stream << " позиция " << error.inext.col;
			*log.stream << endl;
		}
		std::cout << "\nОшибка " << error.id
			<< ": " << error.message;
		if (!(error.inext.line < 0))
			cout << ",\nСтрока " << error.inext.line;
		if (!(error.inext.col < 0))
			cout << " позиция " << error.inext.col;
		cout << endl;
	}
	void Close(LOG &log)
	{
		log.stream->close();
		delete log.stream;
	}
}