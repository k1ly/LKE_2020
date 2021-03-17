#include "Check.h"

namespace Semantic
{
	bool TypeCheck(Log::LOG& log, Tables::TABLE& tbl)
	{
		int buf = 0; bool equal = false; bool check = false; bool till = false;
		bool operation = false; bool note = false; bool unit = false;
		bool error = false;
		for (int i = 0; i < tbl.lt.size; i++)
		{
			if ((tbl.lt.table[i].lexema == LEX_EQUAL && tbl.lt.table[i + 1].lexema != LEX_RIGHTCORNER) ||
				(tbl.lt.table[i].lexema == LEX_LEFTCORNER && tbl.lt.table[i - 1].lexema == LEX_LEFTCORNER) ||
				(tbl.lt.table[i].lexema == LEX_RIGHTCORNER && tbl.lt.table[i - 1].lexema == LEX_RIGHTCORNER) ||
				tbl.lt.table[i].lexema == LEX_CHECK ||
				tbl.lt.table[i].lexema == LEX_TILL)
			{
				if (tbl.lt.table[i].lexema == LEX_EQUAL)
				{
					buf = i - 1;
					equal = true;
				}
				if (tbl.lt.table[i].lexema == LEX_CHECK)
					check = true;
				if (tbl.lt.table[i].lexema == LEX_TILL)
					till = true;
				i++;
				int exp_length = i;
				for (; tbl.lt.table[exp_length].lexema != LEX_NULL &&
					tbl.lt.table[exp_length].lexema != LEX_SEMICOLON &&
					tbl.lt.table[exp_length].lexema != LEX_POINT &&
					tbl.lt.table[exp_length].lexema != LEX_TILL &&
					tbl.lt.table[exp_length].lexema != LEX_EQUAL &&
					(tbl.lt.table[exp_length].lexema != LEX_COMMA ||
						(tbl.lt.table[exp_length + 1].lexema != LEX_CHECK && tbl.lt.table[exp_length + 1].lexema != LEX_GET)); exp_length++)
					if (tbl.lt.table[exp_length + 1].sn > tbl.lt.table[exp_length].sn)
					{
						exp_length++;
						break;
					}
				while (i < exp_length)
				{
					if (tbl.lt.table[i].lexema == LEX_OPERATOR || tbl.lt.table[i].lexema == LEX_LEFTCORNER || tbl.lt.table[i].lexema == LEX_RIGHTCORNER ||
						tbl.lt.table[i].lexema == LEX_EXCLAM || tbl.lt.table[i].lexema == LEX_QUESTION)
						operation = true;
					else if (tbl.lt.table[i].lexema == LEX_ID || tbl.lt.table[i].lexema == LEX_LITERAL)
					{
						for (int j = i; j < exp_length; j++)
							if (tbl.lt.table[j].lexema == '@')
							{
								if ((int)tbl.lt.table[j + 1].lexema == j - 1 - i)
									i = j - 1;
								break;
							}
						switch (tbl.it.table[tbl.lt.table[i].idxTI].iddatatype)
						{
						case IT::NOTE:
							note = true; break;
						case IT::UNIT:
						case IT::IDLE:
						case IT::ARRAY:
							unit = true; break;
						}
					}

					if (note && (unit || operation))
					{
						Log::WriteLine(log, "\n-----------------------------", "");
						Log::WriteError(log, Error::geterrorpos(300, tbl.lt.table[i].sn, -1));
						error = true;
					}
					if ((equal && ((note && (tbl.it.table[tbl.lt.table[buf].idxTI].iddatatype == IT::UNIT || tbl.it.table[tbl.lt.table[buf].idxTI].iddatatype == IT::IDLE)) ||
						(unit && tbl.it.table[tbl.lt.table[buf].idxTI].iddatatype == IT::NOTE))) || (note && (check || till)))
					{
						Log::WriteLine(log, "\n-----------------------------", "");
						Log::WriteError(log, Error::geterrorpos(301, tbl.lt.table[i].sn, -1));
						error = true;
					}
					i++;
				}
				operation = unit = note = equal = check = till = false;
			}
		}
		return error;
	}
	bool ParamCheck(Log::LOG& log, Tables::TABLE& tbl)
	{
		std::stack<LT::Entry> call;
		std::stack<LT::Entry> order;
		bool error = false;
		for (int i = 0; i < tbl.lt.size; i++)
		{
			if (tbl.lt.table[i].lexema == LEX_ID && tbl.it.table[tbl.lt.table[i].idxTI].idtype == IT::F && tbl.lt.table[i + 1].lexema == '@')
			{
				int j = tbl.it.table[tbl.lt.table[i].idxTI].idxfirstLEX;
				while (tbl.lt.table[j].lexema != LEX_LEFTCORNER)
					j--;
				i -= (int)tbl.lt.table[i + 2].lexema;
				while (tbl.lt.table[i + 1].lexema != '@')
				{
					if (tbl.lt.table[i].lexema == LEX_ID || tbl.lt.table[i].lexema == LEX_LITERAL)
						call.push(tbl.lt.table[i]);
					i++;
				}
				while (tbl.lt.table[j].lexema != LEX_RIGHTCORNER)
				{
					if (tbl.lt.table[j].lexema == LEX_ID)
						order.push(tbl.lt.table[j]);
					j++;
				}
				while (!order.empty() && !call.empty())
				{
					if (tbl.it.table[call.top().idxTI].iddatatype == IT::ARRAY)
						call.pop();
					if (((tbl.it.table[call.top().idxTI].iddatatype == IT::UNIT || tbl.it.table[call.top().idxTI].iddatatype == IT::IDLE) && tbl.it.table[order.top().idxTI].iddatatype == IT::NOTE) ||
						(tbl.it.table[call.top().idxTI].iddatatype == IT::NOTE && (tbl.it.table[order.top().idxTI].iddatatype == IT::UNIT || tbl.it.table[order.top().idxTI].iddatatype == IT::IDLE)))
					{
						Log::WriteLine(log, "\n-----------------------------", "");
						Log::WriteError(log, Error::geterrorpos(302, tbl.lt.table[i].sn, -1));
						error = true;
					}
					call.pop();
					order.pop();
				}
				if (call.size() != order.size())
				{
					Log::WriteLine(log, "\n-----------------------------", "");
					Log::WriteError(log, Error::geterrorpos(303, tbl.lt.table[i].sn, -1));
					error = true;
					while (!order.empty())
						order.pop();
					while (!call.empty())
						call.pop();
				}
			}
		}
		return error;
	}
	bool FuncRet(Log::LOG& log, Tables::TABLE& tbl)
	{
		int check; bool error = false;
		for (int i = 0; i < tbl.lt.size; i++)
		{
			if (tbl.lt.table[i].lexema == LEX_ORDER)
			{
				for (int j = i; tbl.lt.table[j].lexema != LEX_ID || tbl.it.table[tbl.lt.table[j].idxTI].idtype != IT::F; j++)
					check = j + 1;
				while (tbl.lt.table[i].lexema != LEX_RELEASE)
					i++;
				i += 3;
				for (int j = i; tbl.lt.table[j].lexema != LEX_POINT; j++)
					if (tbl.lt.table[j].lexema == '@')
					{
						if ((int)tbl.lt.table[j + 1].lexema == j - 1 - i)
							i = j - 1;
						break;
					}
				if (((tbl.it.table[tbl.lt.table[check].idxTI].iddatatype == IT::UNIT || tbl.it.table[tbl.lt.table[check].idxTI].iddatatype == IT::IDLE) && tbl.it.table[tbl.lt.table[i].idxTI].iddatatype == IT::NOTE) ||
					(tbl.it.table[tbl.lt.table[check].idxTI].iddatatype == IT::NOTE && (tbl.it.table[tbl.lt.table[i].idxTI].iddatatype == IT::UNIT || tbl.it.table[tbl.lt.table[i].idxTI].iddatatype == IT::IDLE || tbl.it.table[tbl.lt.table[i].idxTI].iddatatype == IT::ARRAY)))
				{
					Log::WriteLine(log, "\n-----------------------------", "");
					Log::WriteError(log, Error::geterrorpos(304, tbl.lt.table[i].sn, -1));
					error = true;
				}
			}
		}
		return error;
	}
	bool StdCheck(Log::LOG& log, Tables::TABLE& tbl)
	{
		int i = 0; bool error = true;
		for (; i < tbl.lt.size; i++)
			if (tbl.lt.table[i].lexema == LEX_ADHERE)
			{
				if (!strcmp(tbl.it.table[tbl.lt.table[i + 1].idxTI].value.vstr->str, "STD.lib"))
					error = false;
				else
				{
					Log::WriteLine(log, "\n-----------------------------", "");
					Log::WriteError(log, Error::geterrorpos(305, tbl.lt.table[i].sn, -1));
				}
			}
		if (error)
		{
			Log::WriteLine(log, "\n-----------------------------", "");
			Log::WriteError(log, Error::geterrorpos(306, tbl.lt.table[i].sn, -1));
		}
		return error;
	}

	int SemanticAnalysis(Log::LOG& log, Tables::TABLE& tbl)
	{
		std::cout << "\n------ SEMANTIC ANALYSIS -----\n";
		int error = 0;
		error += StdCheck(log, tbl);
		error += TypeCheck(log, tbl);
		error += FuncRet(log, tbl);
		error += ParamCheck(log, tbl);
		if (error == 0)
			std::cout << "\nСемантический анализ выполнен без ошибок" << std::endl;
		return error;
	}
}