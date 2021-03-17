#include "Interpretator.h"
#pragma warning(disable: 4996)

namespace CodeGen
{
	void add(IT::IdTable& idtable, ConstSegment& cnst)
	{
		strcpy(cnst.Data[cnst.size++], "\n\toverflow db 'ERROR: VARIABLE OVERFLOW', 0 \n\tnull_division db 'ERROR: DIVISION BY ZERO', 0");
		std::string str;
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].iddatatype == IT::NOTE && idtable.table[i].id[2] == '0')
				continue;
			if (idtable.table[i].idtype == IT::L && idtable.table[i].iddatatype == IT::NOTE)
			{
				str += "\n\t"; str += idtable.table[i].id; str += " BYTE ";
				bool string = 0;
				for (int j = 0; j < idtable.table[i].value.vstr->len; j++)
					if (idtable.table[i].value.vstr->str[j] == '\n')
					{
						if (string)
						{
							str += "\", ";
							string = 0;
						}
						else if (!string && j > 0)
							str += ", ";
						str += "0dh, 0ah";
					}
					else
					{
						if (!string)
						{
							if (j > 0)
								str += ", ";
							str += "\"";
							string = 1;
						}
						str += idtable.table[i].value.vstr->str[j];
					}
				if (string)
					str += '\"';
				str += ", 0";
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
			else if (idtable.table[i].idtype == IT::V && idtable.table[i].iddatatype == IT::ARRAY)
			{
				str += "\n\t"; str += idtable.table[i].id; str += " DWORD ";

				str += std::to_string(std::abs(idtable.table[i].value.varr->val[0]));
				for (int len = 1; len < idtable.table[i].value.varr->len; len++)
				{
					str += ", ";
					str += std::to_string(std::abs(idtable.table[i].value.varr->val[len]));
				}
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
		}
	}
	void add(IT::IdTable& idtable, DataSegment& dataseg)
	{
		std::string str;
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::V)
			{
				bool string = 0;
				switch (idtable.table[i].iddatatype)
				{
				case IT::UNIT:
					str += "\n\t"; str += idtable.table[i].id; str += " DWORD ";
					str += std::to_string(std::abs(idtable.table[i].value.vint));
					break;
				case IT::NOTE:
					str += "\n\t"; str += idtable.table[i].id; str += " BYTE ";
					for (int j = 0; j < idtable.table[i].value.vstr->len; j++)
						if (idtable.table[i].value.vstr->str[j] == '\n')
						{
							if (string)
							{
								str += "\", ";
								string = 0;
							}
							else if (!string && j > 0)
								str += ", ";
							str += "0dh, 0ah";
						}
						else
						{
							if (!string)
							{
								if (j > 0)
									str += ", ";
								str += "\"";
								string = 1;
							}
							str += idtable.table[i].value.vstr->str[j];
						}
					if (string)
						str += '\"';
					if (idtable.table[i].value.vstr->len > 0)
						str += ", ";
					str += std::to_string(std::abs(255 - idtable.table[i].value.vstr->len));
					str += " DUP(0)";
					break;
				case IT::IDLE:
					str += "\n\t"; str += idtable.table[i].id; str += " BYTE ";
					str += std::to_string(std::abs(idtable.table[i].value.vint));
					break;
				}
				strcpy(dataseg.Data[dataseg.size++], str.c_str());
				str.clear();
			}
		}
	}
	void CodeSegment::add(std::string str)
	{
		std::strcpy(Data[size++], str.c_str());
	}
	void adhere(IT::IdTable& idtable, LT::LexTable& lextable, ConstSegment& cnst)
	{
		std::string str;
		for (int i = 0; i < lextable.size && lextable.table[i].lexema != LEX_MAIN && lextable.table[i].lexema != LEX_ORDER && lextable.table[i].lexema != LEX_DEFINE; i++)
		{
			if (lextable.table[i].lexema == LEX_ADHERE)
			{
				str += "\nincludelib ";
				str += idtable.table[lextable.table[i + 1].idxTI].value.vstr->str;
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
		}
		strcpy(cnst.Data[cnst.size++], "\n.stack 4096\n\n.const");
	}
	void form(IT::IdTable& idtable, LT::LexTable& lextable, ConstSegment& cnst)
	{
		strcpy(cnst.Data[cnst.size++], "\nExitProcess PROTO : DWORD\nwritenote PROTO : DWORD\nwriteidle PROTO : DWORD\nwriteunit PROTO : DWORD\ncopynote PROTO : DWORD, : DWORD\n");
		std::string str;
		for (int i = 0; i < lextable.size && lextable.table[i].lexema != LEX_MAIN && lextable.table[i].lexema != LEX_ORDER && lextable.table[i].lexema != LEX_DEFINE; i++)
		{
			if (lextable.table[i].lexema == LEX_FORM)
			{
				short prm = 0;
				for (int j = i + 1; lextable.table[j].lexema != LEX_RIGHTCORNER; j++)
					if (lextable.table[j].lexema == LEX_TYPE)
						prm++;
				if (prm == 0)
					str += idtable.table[lextable.table[i + 4].idxTI].id;
				else
					str += idtable.table[lextable.table[i + prm * 3 + 3].idxTI].id;
				str += " PROTO";
				if (prm > 0)
				{
					str += " : DWORD";
					for (int p = 1; p < prm; p++)
						str += ", : DWORD";
				}
				str += "\n";
				strcpy(cnst.Data[cnst.size++], str.c_str());
				str.clear();
			}
		}
	}
	void CodeSegmentGeneration(CodeSegment& CS, LT::LexTable l, IT::IdTable& iT)
	{
		bool iffunc = false;
		bool ifcycle = false;
		bool ifcheck = false;
		bool endc = false;
		std::string str;
		IT::IDDATATYPE expression_type = IT::UNIT;
		std::string func_name;
		int idxTI = 0;
		int iret = 0;
		int icount = 0;

		for (int i = 0; i < l.size; i++)
		{
			str.clear();
			while (l.table[i].lexema != LEX_SEMICOLON && l.table[i].lexema != LEX_COLON &&
				l.table[i].lexema != LEX_POINT && l.table[i].lexema != LEX_COMMA &&
				l.table[i].lexema != LEX_LEFTCORNER && l.table[i].lexema != LEX_RIGHTCORNER)
			{
				if (l.table[i + 1].lexema == LEX_TILL || (l.table[i + 1].sn != l.table[i].sn && l.table[i + 1].lexema != LEX_SEMICOLON && l.table[i + 1].lexema != LEX_COLON &&
					l.table[i + 1].lexema != LEX_POINT && l.table[i + 1].lexema != LEX_COMMA &&
					l.table[i + 1].lexema != LEX_LEFTCORNER && l.table[i + 1].lexema != LEX_RIGHTCORNER &&
					l.table[i + 1].lexema != LEX_TILL && l.table[i + 1].lexema != LEX_EQUAL))
				{
					if (ifcheck)
						endc = true;
					break;
				}
				if (!iffunc)
					while (l.table[i].lexema != LEX_MAIN && l.table[i].lexema != LEX_ORDER)
						i++;
				if (l.table[i].lexema == LEX_TYPE)
				{
					if (l.table[i - 1].lexema == LEX_RIGHTCORNER)
					{
						i += 2;	break;
					}
					else if (l.table[i - 1].lexema == LEX_RIGHTBRACKET)
					{
						i += 2;	break;
					}
					else if (l.table[i - 1].lexema == LEX_DEFINE)
						break;
				}
				str += l.table[i++].lexema;

				if (l.table[i - 1].lexema == '*')
				{
					for (int j = i; ; j++)
						if (l.table[j].lexema == 'i' && iT.table[l.table[j].idxTI].idtype == IT::F)
						{
							idxTI = l.table[j].idxTI; break;
						}
				}
				if (l.table[i - 1].lexema == 's')
				{
					for (int j = i; ; j++)
						if (l.table[j].lexema == 'i' && iT.table[l.table[j].idxTI].idtype == IT::V)
						{
							icount = j; break;
						}
				}
				if (l.table[i - 1].lexema == 'i')
				{
					idxTI = l.table[i - 1].idxTI; break;
				}
				if (l.table[i - 1].lexema == 'w' || l.table[i - 1].lexema == 'r' ||
					l.table[i - 1].lexema == 'c' || l.table[i - 1].lexema == 'g' ||
					l.table[i - 1].lexema == 'u' || l.table[i - 1].lexema == 'b')
					break;
			}
			if (str == "*") {
				iffunc = true;
				iret = idxTI;
				func_name = iT.table[idxTI].id;
				expression_type = iT.table[idxTI].iddatatype;
				CS.add(generateInstructions(FUNC, idxTI, iT, expression_type, func_name));
			}
			else if (str == "ti") {
				CS.add(generateInstructions(PARM, l.table[i - 1].idxTI, iT));
			}
			else if (str == "m") {
				iffunc = true;
				func_name = iT.table[l.table[i - 1].idxTI].id;
				CS.add(generateInstructions(FUNC, l.table[i - 1].idxTI, iT, expression_type, func_name));
			}
			else if (str == "r") {
				i += 2;
				generateExpression(i, CS, -1, l, iT);
				endOfFucntion(CS);
				expression_type = iT.table[iret].iddatatype;
				CS.add(generateInstructions(RET, 1, iT, expression_type));
			}
			else if (str == "w") {
				i++;
				int t = i + 1;
				for (int j = t; l.table[j].lexema != LEX_NULL &&
					l.table[j].lexema != LEX_SEMICOLON &&
					l.table[j].lexema != LEX_COMMA &&
					l.table[j].lexema != LEX_TILL; j++)
				{
					if (l.table[j].lexema == '@')
					{
						if ((int)l.table[j + 1].lexema == j - 1 - t)
							t = j - 1;
						break;
					}
					if (l.table[j + 1].sn > l.table[j].sn)
						break;
				}
				expression_type = iT.table[l.table[t].idxTI].iddatatype;
				generateExpression(i + 1, CS, -1, l, iT);
				CS.add(generateInstructions(WRT, NULL, iT, expression_type));
			}
			else if (str == "c") {
				ifcheck = true;
				generateExpression(i, CS, -1, l, iT);
				CS.add(generateInstructions(CHK, 1, iT));
			}
			else if (str == "g") {
				CS.add(generateInstructions(CHK, NULL, iT));
			}
			else if (str == "u") {
				ifcycle = true;
				generateExpression(i, CS, -1, l, iT);
				generateExpression(icount, CS, -1, l, iT);
				CS.add(generateInstructions(CYC, 1, iT));
			}
			else if (str == "b") {
				CS.add(generateInstructions(SKIP, 0, iT));
			}
			else if (str == "e") {
				endOfFucntion(CS);
				CS.add(generateInstructions(RET, NULL, iT));
			}
			if (l.table[i].lexema == '.' && l.table[i + 1].lexema != '.' && l.table[i - 1].lexema != '.') {
				if (iffunc)
				{
					CS.add(generateInstructions(ENDP, NULL, iT, expression_type, func_name));
					iffunc = 0;
				}
			}
			if (l.table[i].lexema == ';' || endc) {
				if (l.table[i].lexema == 'b')
					CS.add(generateInstructions(SKIP, 0, iT));
				if (ifcheck)
				{
					ifcheck = false;
					CS.add(generateInstructions(NEXT, NULL, iT));
				}
				if (ifcycle && !ifcheck && !endc)
				{
					ifcycle = false;
					generateExpression(icount, CS, -1, l, iT);
					CS.add(generateInstructions(CYC, NULL, iT));
					CS.add(generateInstructions(EXECUTE, l.table[icount].idxTI, iT));
					CS.add(generateInstructions(SKIP, 1, iT));
				}
				endc = false;
			}
			if (l.table[i].lexema == ',' && l.table[i - 2].lexema != 't' && (l.table[i + 1].lexema == 'c' || l.table[i + 1].lexema == 'g')) {
				CS.add(generateInstructions(NEXT, 1, iT));
			}
			if (l.table[i].lexema == '.' && l.table[i - 1].lexema == '.') {
				generateExpression(i + 1, CS, -2, l, iT);
			}
			if (l.table[i].lexema == '=' && l.table[i + 1].lexema != '>') {
				generateExpression(i + 1, CS, idxTI, l, iT);
			}
		}
	}
	void endOfFucntion(CodeSegment& CS)
	{
		CS.add("\n\n\tjmp EXIT\nEXIT_DIV_ON_NULL:\n\tpush offset null_division\n\tcall writenote\n\tpush -1\n\tcall ExitProcess");
		CS.add("\nEXIT_OVERFLOW:\n\tpush offset overflow\n\tcall writenote\n\tpush -2\n\tcall ExitProcess\nEXIT:");
	}
	void generateExpression(int expStart, CodeSegment& CS, int idxTI, LT::LexTable l, IT::IdTable iT)
	{
		int begin = 0; int end = 0; int count = 0;
		short exp_length = 0;
		for (; l.table[expStart + exp_length].lexema != LEX_NULL &&
			l.table[expStart + exp_length].lexema != LEX_SEMICOLON &&
			l.table[expStart + exp_length].lexema != LEX_POINT &&
			l.table[expStart + exp_length].lexema != LEX_TILL &&
			l.table[expStart + exp_length].lexema != LEX_EQUAL &&
			(l.table[expStart + exp_length].lexema != LEX_COMMA ||
				(l.table[expStart + exp_length + 1].lexema != LEX_CHECK && l.table[expStart + exp_length + 1].lexema != LEX_GET)); exp_length++)
			if (l.table[expStart + exp_length + 1].sn > l.table[expStart + exp_length].sn)
			{
				exp_length++;
				break;
			}
		for (int j = expStart; j < expStart + exp_length; j++)
		{
			if (l.table[j].lexema == '@')
			{
				count = (int)l.table[j + 1].lexema;
				begin = j - count - 1;
				end = j - 2;
			}
			if (begin && end && count != 1)
			{
				while (end >= begin)
				{
					if (iT.table[l.table[begin + 1].idxTI].iddatatype == IT::ARRAY || iT.table[l.table[end].idxTI].iddatatype == IT::ARRAY)
					{
						if (count == 2)
							break;
						if (iT.table[l.table[begin + 1].idxTI].iddatatype == IT::ARRAY && iT.table[l.table[end].idxTI].iddatatype != IT::ARRAY)
						{
							LT::Entry begindx = l.table[begin];
							std::swap(l.table[begin + 1], l.table[end]);
							for (int i = begin; i < end - 1; i++)
								l.table[i] = l.table[i + 1];
							l.table[end - 1] = begindx;
							begin += 2; end--;
						}
						else if (iT.table[l.table[begin + 1].idxTI].iddatatype != IT::ARRAY && iT.table[l.table[end].idxTI].iddatatype == IT::ARRAY)
						{
							LT::Entry endindx = l.table[end - 1];
							std::swap(l.table[begin], l.table[end]);
							for (int i = end - 1; i > begin; i--)
								l.table[i] = l.table[i - 1];
							l.table[begin] = endindx;
							begin++; end -= 2;
						}
						else if (iT.table[l.table[begin + 1].idxTI].iddatatype == IT::ARRAY && iT.table[l.table[end].idxTI].iddatatype == IT::ARRAY)
						{
							std::swap(l.table[begin + 1], l.table[end]);
							std::swap(l.table[begin], l.table[end - 1]);
							begin += 2; end -= 2;
						}
					}
					else
						std::swap(l.table[begin++], l.table[end--]);
				}
				end = 0;
				begin = 0;
			}
		}
		for (int i = expStart; i < expStart + exp_length; i++)
		{
			switch (l.table[i].lexema)
			{
			case LEX_LITERAL:
			case LEX_ID:
				if (iT.table[l.table[i].idxTI].idtype == IT::F)
					CS.add(generateInstructions(CALL, l.table[i].idxTI, iT));
				else if (iT.table[l.table[i].idxTI].iddatatype == IT::ARRAY)
					CS.add(generateInstructions(INDX, l.table[i].idxTI, iT));
				else
					CS.add(generateInstructions(PUSH, l.table[i].idxTI, iT));
				break;
			case LEX_OPERATOR:
				if (iT.table[l.table[i].idxTI].id[0] == '+')
					CS.add(generateInstructions(ADD, l.table[i].idxTI, iT));
				else if (iT.table[l.table[i].idxTI].id[0] == '*')
					CS.add(generateInstructions(MUL, l.table[i].idxTI, iT));
				else if (iT.table[l.table[i].idxTI].id[0] == '-')
					CS.add(generateInstructions(SUB, l.table[i].idxTI, iT));
				else if (iT.table[l.table[i].idxTI].id[0] == '/')
					CS.add(generateInstructions(DIV, l.table[i].idxTI, iT));
				else if (iT.table[l.table[i].idxTI].id[0] == '%')
					CS.add(generateInstructions(RST, l.table[i].idxTI, iT));
				break;
			case LEX_QUESTION:	CS.add(generateInstructions(EQU, l.table[i].idxTI, iT));
				break;
			case LEX_EXCLAM:	CS.add(generateInstructions(NEQU, l.table[i].idxTI, iT));
				break;
			case LEX_LEFTCORNER:	CS.add(generateInstructions(LESS, l.table[i].idxTI, iT));
				break;
			case LEX_RIGHTCORNER:	CS.add(generateInstructions(GRTR, l.table[i].idxTI, iT));
				break;
			}
			if (i + 1 == expStart + exp_length)
				CS.add(generateInstructions(EXECUTE, idxTI, iT));
		};
	}
	std::string	generateInstructions(INSTRUCTIONTYPE t, int idxTI, IT::IdTable iT, IT::IDDATATYPE type, std::string func_name)
	{
		std::string str;
		static int ret = 0;

		static int idle = 0;
		static int endi = 0;
		static int cmpx = 0;
		static int endx = 0;
		static int next = 0;
		static int endc = 0;
		static int cycle = 0;
		static int ends = 0;

		switch (t)
		{
		case FUNC:
			str += "\n\n"; str += func_name; str += " PROC ";
			return str; break;
		case PARM:
			str += iT.table[idxTI].id; str += ": ";
			str += "DWORD";
			if (iT.table[idxTI + 1].idtype != IT::F)
				str += ", ";
			ret += 4;
			return str; break;
		case PUSH:
			if (iT.table[idxTI].iddatatype == IT::UNIT || iT.table[idxTI].idtype == IT::P)
			{
				str += "\n\tpush ";
				if (iT.table[idxTI].idtype == IT::L)
					str += std::to_string(iT.table[idxTI].value.vint);
				else
					str += iT.table[idxTI].id;
			}
			else if (iT.table[idxTI].iddatatype == IT::IDLE)
			{
				if (iT.table[idxTI].idtype == IT::L)
				{
					str += "\n\tmov eax, ";
					str += std::to_string(iT.table[idxTI].value.vint);
				}
				else
				{
					str += "\n\tmovzx eax, ";
					str += iT.table[idxTI].id;
				}
				str += "\n\tpush eax";
			}
			else
			{
				str += "\n\tpush offset ";
				str += iT.table[idxTI].id;
			}
			return str; break;
		case INDX:
			str += "\n\tmov ebx, offset ";
			str += iT.table[idxTI].id;
			str += "\n\tpop eax\n\timul eax, 4\n\tadd ebx, eax\n\tjo EXIT_OVERFLOW\n\tpush [ebx]";
			return str; break;
		case CALL:  str += "\n\tcall "; str += iT.table[idxTI].id;
			str += "\n\tpush eax\n";
			return str; break;
		case RET:
			if (!idxTI)
				return "\n\tpush 0\n\tcall ExitProcess\n";
			else
			{
				str += "\n\tpop eax";
				if (type == IT::IDLE)
				{
					str += "\n\ttest eax, eax\n\tjz IDLE"; str += std::to_string(idle);
					str += "\n\tmov eax, 1\n\tjmp ENDI"; str += std::to_string(endi);
					str += "\nIDLE"; str += std::to_string(idle);
					str += ":\n\tmov eax, 0\nENDI"; str += std::to_string(endi); str += ":";
					idle++; endi++;
				}
				str += "\n\tret ";
				str += std::to_string(ret); str += "\n";
				ret = 0;
				return str;
			}
			break;
		case WRT:
			if (type == IT::NOTE)
				return "\n\tcall writenote\n";
			else if (type == IT::IDLE)
				return "\n\tcall writeidle\n";
			else
				return "\n\tcall writeunit\n";
			break;
		case CHK:
			if (idxTI)
			{
				str += "\n\tpop eax\n\ttest eax, eax\n\tjz NEXT";
				str += std::to_string(next);
			}
			return str; break;
		case NEXT:
			if (idxTI)
			{
				str += "\tjmp ENDC";
				str += std::to_string(endc);
				str += "\nNEXT";
				str += std::to_string(next); str += ":";
			}
			else
			{
				str += "\nNEXT";
				str += std::to_string(next); str += ":";
				str += "\nENDC";
				str += std::to_string(endc); str += ":\n";
				endc++;
			}
			next++;
			return str; break;
		case CYC:
			if (idxTI)
			{
				str += "\nCYCLE";
				str += std::to_string(cycle); str += ":";
				str += "\n\tpop eax\n\tpop ecx\n\tcmp eax, ecx\n\tjz ENDS";
				str += std::to_string(ends);
				str += "\n\tpush ecx\n";
			}
			else
				str += "\n\tpop eax\n\tinc eax\n\tpush eax";
			return str; break;
		case SKIP:
			if (idxTI)
			{
				str += "\n\tpush eax\n\tjmp CYCLE";
				str += std::to_string(cycle);
				str += "\nENDS";
				str += std::to_string(ends); str += ":\n";
				cycle++; ends++;
			}
			else
			{
				str += "\n\tjmp ENDS";
				str += std::to_string(ends); str += "\n";
			}
			return str; break;
		case ENDP:	str += func_name; str += " ENDP";
			if (!strcmp(func_name.c_str(), "main"))
				str += "\nend main";
			return str; break;
		case ADD:	return "\n\tpop ebx\n\tpop eax\n\tadd eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case SUB:	return "\n\tpop ebx\n\tpop eax\n\tsub eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case MUL:	return "\n\tpop ebx\n\tpop eax\n\timul eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
		case DIV:	return "\n\tpop ebx\n\tpop eax\n\ttest ebx, ebx\n\tjz EXIT_DIV_ON_NULL\n\tcdq\n\tidiv ebx\n\tpush eax"; break;
		case RST:	return "\n\tpop ebx\n\tpop eax\n\tmov edx, 0\n\ttest ebx,ebx\n\tjz EXIT_DIV_ON_NULL\n\tcdq\n\tidiv ebx\n\tpush edx"; break;
		case EQU:
			str += "\n\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tjnz NEQUX"; str += std::to_string(cmpx);
			str += "\n\tmov eax, 1\n\tjmp ENDX"; str += std::to_string(endx);
			str += "\nNEQUX"; str += std::to_string(cmpx);
			str += ":\n\tmov eax, 0\nENDX"; str += std::to_string(endx);
			str += ":\n\tpush eax";
			cmpx++; endx++;
			return str; break;
		case NEQU:
			str += "\n\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tjz EQUALX"; str += std::to_string(cmpx);
			str += "\n\tmov eax, 1\n\tjmp ENDX"; str += std::to_string(endx);
			str += "\nEQUALX"; str += std::to_string(cmpx);
			str += ":\n\tmov eax, 0\nENDX"; str += std::to_string(endx);
			str += ":\n\tpush eax";
			cmpx++; endx++;
			return str; break;
		case LESS:
			str += "\n\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tjge NLESSX"; str += std::to_string(cmpx);
			str += "\n\tmov eax, 1\n\tjmp ENDX"; str += std::to_string(endx);
			str += "\nNLESSX"; str += std::to_string(cmpx);
			str += ":\n\tmov eax, 0\nENDX"; str += std::to_string(endx);
			str += ":\n\tpush eax";
			cmpx++; endx++;
			return str; break;
		case GRTR:
			str += "\n\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tjle NGRTRX"; str += std::to_string(cmpx);
			str += "\n\tmov eax, 1\n\tjmp ENDX"; str += std::to_string(endx);
			str += "\nNGRTRX"; str += std::to_string(cmpx);
			str += ":\n\tmov eax, 0\nENDX"; str += std::to_string(endx);
			str += ":\n\tpush eax";
			cmpx++; endx++;
			return str; break;
		case EXECUTE:
			if (idxTI == -2)
				str += "\n\tpop eax\n";
			else if (idxTI != -1 && iT.table[idxTI].idtype != IT::F && (iT.table[idxTI].iddatatype == IT::UNIT || iT.table[idxTI].iddatatype == IT::IDLE || iT.table[idxTI].idtype == IT::P))
			{
				if (iT.table[idxTI].iddatatype == IT::IDLE)
				{
					str += "\n\tpop eax\n\ttest eax, eax\n\tjz IDLE"; str += std::to_string(idle);
					str += "\n\tmov eax, 1\n\tjmp ENDI"; str += std::to_string(endi);
					str += "\nIDLE"; str += std::to_string(idle);
					str += ":\n\tmov eax, 0\nENDI"; str += std::to_string(endi); str += ":";
					if (iT.table[idxTI].idtype == IT::P)
					{
						str += "\n\tmov "; str += iT.table[idxTI].id;
						str += ", eax\n";
					}
					else
					{
						str += "\n\tmov "; str += iT.table[idxTI].id;
						str += ", al\n";
					}
					idle++; endi++;
				}
				else
				{
					str += "\n\tpop ";
					str += iT.table[idxTI].id; str += "\n";
				}
			}
			else if (idxTI != -1 && iT.table[idxTI].iddatatype == IT::NOTE)
			{
				str += "\n\tpush offset "; str += iT.table[idxTI].id;
				str += "\n\tcall copynote\n";
			}
			return str; break;
		}
		return str;
	}
	void PrintData(Log::LOG log, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg)
	{
		*log.stream << "\n----- Код на ассемблере -----\n\n";
		for (int i = 0; i < cnst.size; i++)
			*log.stream << cnst.Data[i];
		for (int i = 0; i < dataseg.size; i++)
			*log.stream << dataseg.Data[i];
		for (int i = 0; i < codeseg.size; i++)
			*log.stream << codeseg.Data[i];
	}
	void DataOut(std::ofstream& file, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg)
	{
		for (int i = 0; i < cnst.size; i++)
			file << cnst.Data[i];
		for (int i = 0; i < dataseg.size; i++)
			file << dataseg.Data[i];
		for (int i = 0; i < codeseg.size; i++)
			file << codeseg.Data[i];
	}
	void startGeneration(const char* path, ConstSegment& CnstS, DataSegment& DS, CodeSegment& CS)
	{
		cout << "\n------------------------------\n" << endl;
		std::ofstream assembler; assembler.open(path, std::ios_base::out | std::ios_base::trunc);
		if (assembler.is_open())
		{
			remove(path);
		}
		DataOut(assembler, CnstS, DS, CS);
		assembler.close();
	}
};
