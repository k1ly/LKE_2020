#include "Parm.h"

namespace Parm
{
	PARM GetParm(int argc, wchar_t* argv[])
	{
		PARM* parm = new PARM;
		bool in = 0;
		bool out = 0;
		bool log = 0;
		for (int i = 0; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(11);
			if (wcsstr(argv[i], PARM_IN))
			{
				wcscpy_s(parm->in, argv[i] + wcslen(PARM_IN));
				in = 1;
			}
			if (wcsstr(argv[i], PARM_OUT))
			{
				wcscpy_s(parm->out, argv[i] + wcslen(PARM_OUT));
				out = 1;
			}
			if (wcsstr(argv[i], PARM_LOG))
			{
				wcscpy_s(parm->log, argv[i] + wcslen(PARM_LOG));
				log = 1;
			}
		}
		if (!in)
			throw ERROR_THROW(10);
		if (!out)
		{
			wcscpy_s(parm->out, parm->in);
			wcscat_s(parm->out, PARM_OUT_DEFAULT_EXIT);
		}
		if (!log)
		{
			wcscpy_s(parm->log, parm->in);
			wcscat_s(parm->log, PARM_LOG_DEFAULT_EXIT);
		}

		return *parm;
	}
}