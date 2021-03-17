#include "Tables.h"
using namespace std;

namespace Tables
{
	TABLE GetTables(Parm::PARM& parm, In::IN& in)
	{
		TABLE* tbl = new TABLE;
		tbl->stream = new ofstream;
		tbl->stream->open(parm.out);
		if (tbl->stream->fail())
			throw ERROR_THROW(20);

		tbl->lt = LT::Create(10);
		tbl->it = IT::Create(10);

		Lexem::LEXEM lexem = Lexem::GetLexem();

		if (in.size > 0)
		{
			char token[TI_STR_MAXSIZE] = "";
			char subtoken[ID_MAXSIZE + 1] = "";
			char functoken[TOKEN_MAXSIZE] = "";

			short iliteral = 0;
			short iparm = 0;
			short iarr = 0;
			short icheck = 0;
			short icycle = 0;

			bool preproc = 0;
			bool isform = 0;
			bool isfile = 0;

			bool defid = 0;
			bool unitid = 0;
			bool noteid = 0;
			bool idleid = 0;

			bool funcid = 0;
			bool parmid = 0;
			bool mainid = 0;
			bool isfunc = 0;
			bool endfunc = 0;

			bool iscycle = 0;
			bool arrid = 0;
			bool index = 0;
			bool isindx = 0;

			bool string = 0;
			bool file = 0;
			bool arr = 0;

			for (int itext = 0, itoken = 0; in.text[itext] != IN_CODE_ENDS; itext++)
			{
				token[itoken] = in.text[itext];
				itoken++;

				if (in.text[itext] == '\"')
					string = !string;
				if (in.text[itext] == '\'')
					file = !file;
				if (in.text[itext] == '{' || in.text[itext] == '}')
					arr = !arr;

				if (!string && !file && !arr && (in.code[in.text[itext]] == in.X || in.text[itext + 1] == IN_CODE_SEP || in.text[itext + 1] == IN_CODE_ENDS ||
					in.code[in.text[itext + 1]] == in.P || in.code[in.text[itext + 1]] == in.X))
				{
					token[itoken] = IN_CODE_ENDS;

					for (int f = 0; f < LEXEMA_NUMBER + 7; f++)
					{
						FST::FST fst((char*)token, lexem.fstn[f].states, lexem.fstn[f].nodes[0], lexem.fstn[f].nodes[1], lexem.fstn[f].nodes[2], lexem.fstn[f].nodes[3],
							lexem.fstn[f].nodes[4], lexem.fstn[f].nodes[5], lexem.fstn[f].nodes[6], lexem.fstn[f].nodes[7]);
						if (FST::execute(fst))
						{
							int idxTI = TI_NULLIDX;
							LT::Entry* lex = new LT::Entry;
							lex->lexema = lexem.fstn[f].lexema;
							lex->sn = in.table[itext].line;
							lex->idxTI = LT_TI_NULLIDX;
							IT::Entry* id = new IT::Entry;
							switch (f)
							{
							case 0: defid = 1;
								break;
							case 2:
								if (funcid)
								{
									isfunc = 1;
									funcid = 0;
								}
								break;
							case 3:
								if (iscycle && icheck < 2)
									iscycle = 0;
								if (icheck == 2)
									icheck = 0;
								break;
							case 4:
								if (endfunc)
								{
									endfunc = 0;
									isfunc = 0;
									strcpy_s(functoken, "");
								}
								break;
							case 5:
								if (!isfunc)
									preproc = 1;
								break;
							case 7:
								if (funcid)
									parmid = 1;
								break;
							case 8:
								if (parmid)
								{
									if (isform)
									{
										unitid = 0;
										noteid = 0;
										idleid = 0;
									}
									parmid = 0;
								}
								break;
							case 9:
								index = 1;
								break;
							case 10:
								if (isindx)
									index = 0;
								isindx = 0;
								break;
							case 15:
								if (isfunc)
									throw ERROR_THROW_OUT(120, in.table[itext].line, in.table[itext].col);
								funcid = 1;
								break;
							case 16:
								if (!preproc)
									throw ERROR_THROW_OUT(114, in.table[itext].line, in.table[itext].col);
								isfile = 1;
								break;
							case 17:
								if (!preproc)
									throw ERROR_THROW_OUT(114, in.table[itext].line, in.table[itext].col);
								isform = 1;
								funcid = 1;
								break;
							case 18:
								if (mainid)
									throw ERROR_THROW_OUT(112, in.table[itext].line, in.table[itext].col);
								mainid = 1;
								break;
							case 19:
								if (!isfunc)
									throw ERROR_THROW_OUT(121, in.table[itext].line, in.table[itext].col);
								endfunc = 1;
								break;
							case 21:
								if (iscycle || icheck)
									throw ERROR_THROW_OUT(122, in.table[itext].line, in.table[itext].col);
								iscycle = 1;
								icycle++;
								break;
							case 24:
								if (tbl->lt.table[tbl->lt.size - 1].lexema != LEX_COMMA ||
									(tbl->lt.table[tbl->lt.size - 1].lexema == LEX_COMMA && tbl->lt.table[tbl->lt.size - 3].lexema == LEX_TYPE))
									icheck = 0;
								icheck++;
								break;
							case 25:
								icheck = 2;
								break;
							case 26:
								if (!mainid)
									throw ERROR_THROW_OUT(113, in.table[itext].line, in.table[itext].col);
								endfunc = 1;
								break;
							case 27:
								if (index)
								{
									index = 0;
									arrid = 1;
								}
								else
									unitid = 1;
								break;
							case 28:
								noteid = 1;
								break;
							case 29:
								idleid = 1;
								break;
							}
							if (lex->lexema == LEX_ID || lex->lexema == LEX_OPERATOR || lex->lexema == LEX_LITERAL || lex->lexema == LEX_MAIN)
							{
								strcpy_s(id->id, "");
								strcpy_s(id->realm, "");
								id->block = TI_NULLIDX;
								id->idxfirstLEX = TI_NULLIDX;
								(*id).iddatatype = (IT::IDDATATYPE)0;
								(*id).idtype = (IT::IDTYPE)0;
								switch (lex->lexema)
								{
								case LEX_ID:
									if (index && !isindx)
										throw ERROR_THROW_OUT(129, in.table[itext].line, in.table[itext].col);

									for (int i = 0; i < ID_MAXSIZE; i++)
										subtoken[i] = token[i];
									subtoken[ID_MAXSIZE] = IN_CODE_ENDS;

									if (iscycle)
										idxTI = IT::IsId(tbl->it, subtoken, functoken, token, icycle, f);
									else
										idxTI = IT::IsId(tbl->it, subtoken, functoken, token, -1, f);

									if (idxTI < 0)
									{
										if (strcmp(token, subtoken) != 0 && (!funcid || (funcid && !isform)))
											cout << "Предупреждение: Имя идентификатора " << token << " урезано до " << subtoken << " !\n";

										id->idxfirstLEX = tbl->lt.size;
										if (unitid && !(noteid || idleid || arrid))
										{
											(*id).iddatatype = IT::UNIT;
											id->value.vint = 0;
											unitid = 0;
										}
										else if (noteid && !(unitid || idleid || arrid))
										{
											(*id).iddatatype = IT::NOTE;
											id->value.vstr->len = 0;
											strcpy_s(id->value.vstr->str, "");
											noteid = 0;
										}
										else if (idleid && !(unitid || noteid || arrid))
										{
											(*id).iddatatype = IT::IDLE;
											id->value.vint = 0;
											idleid = 0;
										}
										else if (arrid && !(unitid || idleid || unitid))
										{
											(*id).iddatatype = IT::ARRAY;
											if (iarr > TI_ARR_MAXSIZE || iarr < 1)
												throw ERROR_THROW_OUT(128, in.table[itext].line, in.table[itext].col);
											else
												id->value.varr->len = iarr;
											for (int i = 0; i < id->value.varr->len; i++)
												id->value.varr->val[i] = 0;
											iarr = 0;
										}
										if ((*id).iddatatype == 0)
											throw ERROR_THROW_OUT(124, in.table[itext].line, in.table[itext].col);
										if (funcid && !parmid)
										{
											if (arrid)
												throw ERROR_THROW_OUT(125, in.table[itext].line, in.table[itext].col);
											strcpy_s(id->id, subtoken);
											(*id).idtype = IT::F;
											if (isform)
											{
												strcpy_s(id->realm, "EXTERN");
												funcid = 0;
												for (; iparm > 0; iparm--)
													strcpy_s(tbl->it.table[tbl->it.size - iparm].realm, subtoken);
											}
											else
											{
												strcpy_s(functoken, subtoken);
												for (; iparm > 0; iparm--)
													strcpy_s(tbl->it.table[tbl->it.size - iparm].realm, functoken);
											}
										}
										else if (parmid)
										{
											strcpy_s(id->id, subtoken);
											(*id).idtype = IT::P;
											iparm++;
										}
										else
										{
											if (!defid && !arrid)
												throw ERROR_THROW_OUT(123, in.table[itext].line, in.table[itext].col);
											if (isform || isfile)
												throw ERROR_THROW_OUT(115, in.table[itext].line, in.table[itext].col);
											strcpy_s(id->id, subtoken);
											strcpy_s(id->realm, functoken);
											if (iscycle)
												id->block = icycle;
											if (!funcid && !parmid)
												(*id).idtype = IT::V;
											defid = 0;
											arrid = 0;
										}
									}
									else
									{
										if (tbl->it.table[idxTI].iddatatype == IT::ARRAY)
											isindx = 1;
										if (defid || arrid)
											throw ERROR_THROW_OUT(126, in.table[itext].line, in.table[itext].col);
										if (funcid)
											throw ERROR_THROW_OUT(127, in.table[itext].line, in.table[itext].col);
									}
									break;
								case LEX_MAIN:
									strcpy_s(subtoken, token);
									id->idxfirstLEX = tbl->lt.size;
									strcpy_s(id->id, token);
									strcpy_s(functoken, token);
									(*id).iddatatype = IT::MAIN;
									(*id).idtype = IT::F;
									break;
								case LEX_LITERAL:
									if (index && f != 34 && f != 30 && f != 31)
										throw ERROR_THROW_OUT(133, in.table[itext].line, in.table[itext].col);
									if (isfile && f != 33)
										throw ERROR_THROW_OUT(134, in.table[itext].line, in.table[itext].col);
									if (!isfile && f == 33)
										throw ERROR_THROW_OUT(135, in.table[itext].line, in.table[itext].col);
									if (f == 30 || f == 31)
									{
										if (f == 30)
											strcpy_s(token, "1");
										else strcpy_s(token, "0");
									}
									if (f == 32)
									{
										for (int i = 0; token[i + 1] != '\"'; i++)
											token[i] = token[i + 1];
										token[strlen(token) - 2] = IN_CODE_ENDS;
										for (int i = 0; i < (int)strlen(token); i++)
											if (token[i] == '/' && token[i + 1] == 'n')
											{
												token[i] = '\n';
												for (int j = i + 1; j < (int)strlen(token); j++)
													token[j] = token[j + 1];
											}
									}
									else if (f == 33)
									{
										int s = strlen(token);
										for (int i = 0; token[i + 1] != '\''; i++)
											token[i] = token[i + 1];
										token[s - 2] = IN_CODE_ENDS;
									}
									else if (f == 34)
									{
										long long t = atoll(token);
										if (token[1] == 'X')
											t = strtoull(token, NULL, 16);
										else if (token[1] == 'o')
										{
											for (int i = 1; token[i + 1] != IN_CODE_ENDS; i++)
												token[i] = token[i + 1];
											token[strlen(token) - 1] = IN_CODE_ENDS;
											t = strtoull(token, NULL, 8);
										}
										if (t > UINT_MAX)
											throw ERROR_THROW_OUT(130, in.table[itext].line, in.table[itext].col);
										_itoa_s((int)t, token, 10);
										if (index)
											iarr = atoi(token);
									}
									else if (f == 35)
									{
										int s = strlen(token);
										for (int i = 0; token[i + 1] != '}'; i++)
											token[i] = token[i + 1];
										token[s - 2] = IN_CODE_ENDS;

										int l = 0;
										char number[TOKEN_MAXSIZE] = "";
										for (int inum = 0, ielem = 0, iarray = 0; token[inum] != IN_CODE_ENDS; inum++)
										{
											number[ielem] = token[inum];
											ielem++;
											if (token[inum + 1] == ',' || token[inum + 1] == IN_CODE_ENDS)
											{
												l++;
												number[ielem] = IN_CODE_ENDS;

												long long t = atoll(number);
												if (number[1] == 'X')
													t = strtoull(number, NULL, 16);
												else if (number[1] == 'o')
												{
													for (int i = 1; number[i + 1] != IN_CODE_ENDS; i++)
														number[i] = number[i + 1];
													number[strlen(number) - 1] = IN_CODE_ENDS;
													t = strtoull(number, NULL, 8);
												}
												if (t > UINT_MAX)
													throw ERROR_THROW_OUT(130, in.table[itext].line, in.table[itext].col);
												id->value.varr->val[iarray] = (int)t;
												iarray++;
												strcpy_s(number, "");
												ielem = 0;
												if (token[inum + 1] == ',')
													inum++;
											}
										}
										id->value.varr->len = l;
										if (tbl->it.table[tbl->it.size - 1].iddatatype == IT::ARRAY)
										{
											if (tbl->it.table[tbl->it.size - 1].value.varr->len < id->value.varr->len)
												throw ERROR_THROW_OUT(131, in.table[itext].line, in.table[itext].col);
											for (int i = 0; i < id->value.varr->len; i++)
												tbl->it.table[tbl->it.size - 1].value.varr->val[i] = id->value.varr->val[i];
										}
										else
											throw ERROR_THROW_OUT(132, in.table[itext].line, in.table[itext].col);
									}

									if (f != 35)
									{
										if (tbl->it.size > 0 && tbl->it.table[tbl->it.size - 1].idtype == IT::V && !strcmp(tbl->it.table[tbl->it.size - 1].realm, ""))
										{
											if ((f == 30 || f == 31) && (tbl->it.table[tbl->it.size - 1].iddatatype == IT::IDLE || tbl->it.table[tbl->it.size - 1].iddatatype == IT::UNIT))
											{
												if (f == 30)
													tbl->it.table[tbl->it.size - 1].value.vint = 1;
												else
													tbl->it.table[tbl->it.size - 1].value.vint = 0;
											}
											else if (f == 34 && (tbl->it.table[tbl->it.size - 1].iddatatype == IT::UNIT || tbl->it.table[tbl->it.size - 1].iddatatype == IT::IDLE))
												tbl->it.table[tbl->it.size - 1].value.vint = atoi(token);
											else
											{
												tbl->it.table[tbl->it.size - 1].value.vstr->len = (char)strlen(token);
												strcpy_s(tbl->it.table[tbl->it.size - 1].value.vstr->str, token);
											}
										}
										idxTI = IT::IsId(tbl->it, subtoken, functoken, token, icycle, f);
									}

									if (idxTI < 0)
									{
										id->idxfirstLEX = tbl->lt.size;
										(*id).idtype = IT::L;
										if (f == 33)
											_itoa_s(0, subtoken, 10);
										else if (f == 30 || f == 31 || f == 34 || f == 35)
											strcpy_s(subtoken, "");
										else
											_itoa_s((++iliteral), subtoken, 10);
										strcpy_s(id->id, "_L");
										strcat_s(id->id, subtoken);
										strcpy_s(subtoken, "");

										if (f == 30 || f == 31)
										{
											(*id).iddatatype = IT::IDLE;
											if (f == 30)
												id->value.vint = 1;
											else id->value.vint = 0;
										}
										else if (f == 32 || f == 33)
										{
											(*id).iddatatype = IT::NOTE;
											id->value.vstr->len = (char)strlen(token);
											strcpy_s(id->value.vstr->str, token);
										}
										else if (f == 34)
										{
											(*id).iddatatype = IT::UNIT;
											id->value.vint = atoi(token);
										}
										else if (f == 35)
											(*id).iddatatype = IT::ARRAY;
									}
									break;
								case LEX_OPERATOR:
									strcpy_s(id->id, token);
									(*id).idtype = IT::O;
									break;
								}
								if (idxTI < 0)
									IT::Add(tbl->it, *id);
							}
							if (lex->lexema == LEX_ID || lex->lexema == LEX_MAIN || (lex->lexema == LEX_LITERAL && f != 35))
								lex->idxTI = IT::IsId(tbl->it, subtoken, functoken, token, icycle, f);
							else if (lex->lexema == LEX_OPERATOR || f == 35)
								lex->idxTI = tbl->it.size - 1;

							LT::Add(tbl->lt, *lex);
							break;
						}
						else
							if (f == LEXEMA_NUMBER + 7 - 1)
								throw ERROR_THROW_OUT(110, in.table[itext].line, in.table[itext].col);
					}
					if (in.text[itext + 1] == IN_CODE_SEP)
					{
						preproc = 0;
						isform = 0;
						isfile = 0;
					}
					strcpy_s(token, "");
					strcpy_s(subtoken, "");
					itoken = 0;
					if (in.code[in.text[itext + 1]] == in.P || in.text[itext + 1] == IN_CODE_SEP)
						itext++;
				}
				else
					if ((string || file || arr) && itoken >= TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(111, in.table[itext].line, in.table[itext].col);
			}
		}
		for (int i = 0; i < tbl->it.size; i++)
		{
			if (tbl->it.table[i].idtype == IT::F && !strcmp(tbl->it.table[i].realm, "") && tbl->it.table[i].iddatatype != IT::MAIN)
			{
				char proc[] = "proc_";
				int s = strlen(tbl->it.table[i].id);
				int p = strlen(proc);
				tbl->it.table[i].id[s + p] = '\0';
				for (int j = s; j > 0; j--)
					tbl->it.table[i].id[j + p - 1] = tbl->it.table[i].id[j - 1];
				int j = 0;
				for (; j < p; j++)
					tbl->it.table[i].id[j] = proc[j];
				tbl->it.table[i].id[s + j] = '\0';
			}
			else if (tbl->it.table[i].idtype == IT::V)
			{
				if (tbl->it.table[i].block != -1)
				{
					int s = strlen(tbl->it.table[i].id);
					tbl->it.table[i].id[s + 5] = '\0';
					for (int j = s; j > 0; j--)
						tbl->it.table[i].id[j + 4] = tbl->it.table[i].id[j - 1];
					char ic[3] = "00";
					_itoa_s(tbl->it.table[i].block, ic, 10);
					tbl->it.table[i].id[0] = '_';
					tbl->it.table[i].id[1] = 'c';
					if (tbl->it.table[i].block < 10)
					{
						tbl->it.table[i].id[2] = '0';
						tbl->it.table[i].id[3] = ic[0];
					}
					else
					{
						tbl->it.table[i].id[2] = ic[0];
						tbl->it.table[i].id[3] = ic[1];
					}
					tbl->it.table[i].id[4] = '_';
				}
				else
				{
					if (!strcmp(tbl->it.table[i].realm, ""))
					{
						int s = strlen(tbl->it.table[i].id);
						tbl->it.table[i].id[s + 2] = '\0';
						for (int j = s; j > 0; j--)
							tbl->it.table[i].id[j + 1] = tbl->it.table[i].id[j - 1];
						tbl->it.table[i].id[1] = '_';
						tbl->it.table[i].id[0] = '_';
					}
					else
					{
						int s = strlen(tbl->it.table[i].id);
						int r = strlen(tbl->it.table[i].realm);
						tbl->it.table[i].id[s + r + 1] = '\0';
						for (int j = s; j > 0; j--)
							tbl->it.table[i].id[j + r] = tbl->it.table[i].id[j - 1];
						int j = 0;
						for (; j < r; j++)
							tbl->it.table[i].id[j] = tbl->it.table[i].realm[j];
						tbl->it.table[i].id[j] = '_';
					}
				}
			}
			else if (tbl->it.table[i].idtype == IT::V && tbl->it.table[i].iddatatype == IT::ARRAY)
			{
				int s = strlen(tbl->it.table[i].id);
				tbl->it.table[i].id[s + 1] = '\0';
				for (int j = s; j > 0; j--)
					tbl->it.table[i].id[j] = tbl->it.table[i].id[j - 1];
				tbl->it.table[i].id[0] = '_';
			}
		}
		delete[] lexem.fstn;
		return *tbl;
	}

	void WriteTable(TABLE& tbl, const char* c)
	{
		bool lt = 0;
		bool it = 0;
		if (!strcmp(c, "all"))
		{
			lt = 1;
			it = 1;
		}
		else if (!strcmp(c, "lt"))
			lt = 1;
		else if (!strcmp(c, "it"))
			it = 1;

		if (it)
		{
			*tbl.stream << "\n-------- ID TABLE --------------\n" << endl;
			*tbl.stream << setw(3) << right << "№" << "  " << setw(20) << left << "Имя идентификатора:" << setw(25) << "Область видимости:" << setw(20) << "Индекс вхождения:" << setw(25) << "Тип:" << setw(20) << "Значение:" << endl << endl;
			for (int i = 0; i < tbl.it.size; i++)
			{
				if (tbl.it.table[i].idtype == IT::O)
					continue;
				*tbl.stream << setw(3) << right;
				*tbl.stream << i << ". ";

				*tbl.stream << setw(20) << left;
				*tbl.stream << tbl.it.table[i].id;

				if (tbl.it.table[i].block != -1)
					*tbl.stream << setw(11);
				else
					*tbl.stream << setw(25);
				if (strcmp(tbl.it.table[i].realm, ""))
					*tbl.stream << tbl.it.table[i].realm;
				else
					*tbl.stream << "Global";
				if (tbl.it.table[i].block != -1)
				{
					*tbl.stream << setw(14);
					char c[9] = "cycle_";
					char ic[3] = "";
					_itoa_s(tbl.it.table[i].block, ic, 10);
					if (tbl.it.table[i].block < 10)
					{
						c[6] = '0';
						c[7] = ic[0];
					}
					else
					{
						c[6] = ic[0];
						c[7] = ic[1];
					}
					*tbl.stream << c;
				}

				*tbl.stream << setw(20);
				*tbl.stream << tbl.it.table[i].idxfirstLEX;

				*tbl.stream << setw(7);
				switch (tbl.it.table[i].iddatatype)
				{
				case IT::IDDATATYPE::UNIT:
					*tbl.stream << "unit"; break;
				case IT::IDDATATYPE::NOTE:
					*tbl.stream << "note"; break;
				case IT::IDDATATYPE::IDLE:
					*tbl.stream << "idle"; break;
				case IT::IDDATATYPE::ARRAY:
					*tbl.stream << "[]unit"; break;
				case IT::IDDATATYPE::MAIN:
					*tbl.stream << "Main"; break;
				default:
					*tbl.stream << "_"; break;
				}

				*tbl.stream << setw(18);
				switch (tbl.it.table[i].idtype)
				{
				case IT::IDTYPE::L:
					*tbl.stream << "Literal"; break;
				case IT::IDTYPE::F:
					*tbl.stream << "Function"; break;
				case IT::IDTYPE::P:
					*tbl.stream << "parameter"; break;
				case IT::IDTYPE::V:
					*tbl.stream << "variable"; break;
				default:
					*tbl.stream << "_"; break;
				}

				if (tbl.it.table[i].idtype != IT::IDTYPE::F)
				{
					if (tbl.it.table[i].iddatatype == IT::NOTE)
					{
						*tbl.stream << '\"';
						for (int j = 0; j < tbl.it.table[i].value.vstr->len; j++)
							if (tbl.it.table[i].value.vstr->str[j] == '\n')
								*tbl.stream << "\\n";
							else
								*tbl.stream << tbl.it.table[i].value.vstr->str[j];
						*tbl.stream << '\"';
					}
					if (tbl.it.table[i].iddatatype == IT::ARRAY)
					{
						*tbl.stream << "{";
						for (int j = 0; j < tbl.it.table[i].value.varr->len; j++)
						{
							*tbl.stream << tbl.it.table[i].value.varr->val[j];
							if (j + 1 != tbl.it.table[i].value.varr->len)
								*tbl.stream << ",";
						}
						*tbl.stream << "}";
					}
					if (tbl.it.table[i].iddatatype == IT::UNIT || tbl.it.table[i].iddatatype == IT::IDLE)
						*tbl.stream << tbl.it.table[i].value.vint;
				}
				*tbl.stream << endl;
			}
		}

		if (lt)
		{
			*tbl.stream << "\n-------- LEX TABLE -------------\n" << endl;
			*tbl.stream << setw(3) << right;
			int l = tbl.lt.table[0].sn;
			*tbl.stream << l << ":  ";
			for (int i = 0; i < tbl.lt.size; i++)
			{
				if (tbl.lt.table[i].sn > l)
				{
					*tbl.stream << setw(3);
					l = tbl.lt.table[i].sn;
					*tbl.stream << endl << l << ":  ";
				}
				if (tbl.lt.table[i].lexema == LEX_NULL)
					continue;
				if (tbl.lt.table[i].lexema == LEX_OPERATOR)
					*tbl.stream << tbl.it.table[tbl.lt.table[i].idxTI].id;
				else if (tbl.lt.table[i].lexema == '@')
				{
					char count[3];
					_itoa_s((int)tbl.lt.table[i + 1].lexema, count, 10);
					*tbl.stream << tbl.lt.table[i].lexema << count;
					i++;
				}
				else
					*tbl.stream << tbl.lt.table[i].lexema;
			}
			*tbl.stream << endl;
		}

		if (!lt && !it)
		{
			*tbl.stream << "\n-------- LEX TABLE -------------\n" << endl;
			*tbl.stream << setw(3) << right;
			int l = tbl.lt.table[0].sn;
			*tbl.stream << l << ":  ";
			for (int i = 0; i < tbl.lt.size; i++)
			{
				if (tbl.lt.table[i].sn > l)
				{
					*tbl.stream << setw(3);
					l = tbl.lt.table[i].sn;
					*tbl.stream << endl << l << ":  ";
				}
				*tbl.stream << tbl.lt.table[i].lexema;
			}
			*tbl.stream << endl;
		}
	}

	void Close(TABLE& tbl)
	{
		tbl.stream->close();
		delete tbl.stream;
	}
}