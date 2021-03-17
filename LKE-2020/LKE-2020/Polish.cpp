#include "Polish.h"

namespace Polish
{
	void GetPolish(Tables::TABLE& tbl)
	{
		cout << "\n------ POLISH EXPRESSION -----" << endl;
		for (int i = 0; i < tbl.lt.size; i++)
		{
			if ((tbl.lt.table[i].lexema == LEX_EQUAL && tbl.lt.table[i + 1].lexema != LEX_RIGHTCORNER) ||
				(tbl.lt.table[i].lexema == LEX_LEFTCORNER && tbl.lt.table[i - 1].lexema == LEX_LEFTCORNER) ||
				(tbl.lt.table[i].lexema == LEX_RIGHTCORNER && tbl.lt.table[i - 1].lexema == LEX_RIGHTCORNER) ||
				(tbl.lt.table[i].lexema == LEX_POINT && tbl.lt.table[i - 1].lexema == LEX_POINT) ||
				tbl.lt.table[i].lexema == LEX_CHECK ||
				tbl.lt.table[i].lexema == LEX_TILL)
			{
				cout << endl << tbl.lt.table[i + 1].sn << ":	";
				if (!PolishNotation(i + 1, tbl.lt, tbl.it))
					cout << "Польская запись не построена!" << endl;
			}
		}
	}

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		bool rc = 1;
		short exp_length = 0;
		short opened_thesis = 0;
		for (; lextable.table[lextable_pos + exp_length].lexema != LEX_SEMICOLON &&
			lextable.table[lextable_pos + exp_length].lexema != LEX_POINT &&
			lextable.table[lextable_pos + exp_length].lexema != LEX_TILL &&
			(lextable.table[lextable_pos + exp_length].lexema != LEX_EQUAL || lextable.table[lextable_pos + exp_length + 1].lexema != LEX_RIGHTCORNER) &&
			(lextable.table[lextable_pos + exp_length].lexema != LEX_COMMA ||
				(lextable.table[lextable_pos + exp_length + 1].lexema != LEX_CHECK && lextable.table[lextable_pos + exp_length + 1].lexema != LEX_GET)); exp_length++)
			if (lextable.table[lextable_pos + exp_length + 1].sn != lextable.table[lextable_pos + exp_length].sn)
			{
				exp_length++;
				break;
			}
		struct Stack
		{
			LT::Entry lex;
			Stack* next;
			Stack* head;
			short priority(char c)
			{
				struct Operator
				{
					char lex;
					short pr;
#define OPERATOR_NUMBER 10
				} priority[OPERATOR_NUMBER]{ {'?', 1}, {'!', 1}, {'<', 1}, {'>', 1}, {'-', 2}, {'+', 2}, {'*', 3}, {'/', 3}, {'%', 3}, {'i', 4} };
				short rc = -1;
				for (int i = 0; i < OPERATOR_NUMBER; i++)
					if (c == priority[i].lex)
					{
						rc = priority[i].pr; break;
					}
				return rc;
			}
			void push(LT::Entry l)
			{
				Stack* e = new Stack;
				e->lex = l;
				e->next = head;
				head = e;
			}
			LT::Entry pop()
			{
				if (head == NULL)
					return LT::Entry{ LEX_NULL, 0, -1 };
				Stack* p = head;
				head = p->next;
				LT::Entry rc = p->lex;
				delete p;
				return rc;
			}
		};
		Stack st; st.head = NULL;

		for (int i = 0; i < exp_length; i++)
		{
			if (lextable.table[lextable_pos + i].lexema == LEX_OPERATOR)
				cout << idtable.table[lextable.table[lextable_pos + i].idxTI].id;
			else if (lextable.table[lextable_pos + i].lexema == LEX_ID)
			{
				if (idtable.table[lextable.table[lextable_pos + i].idxTI].idtype == IT::F)
					cout << 'f';
				else if (idtable.table[lextable.table[lextable_pos + i].idxTI].iddatatype == IT::ARRAY)
					cout << 'a';
				else
					cout << lextable.table[lextable_pos + i].lexema;
			}
			else
				cout << lextable.table[lextable_pos + i].lexema;
		}
		cout << "\t";

		short e = 0;
		LT::Entry* expression = new LT::Entry[exp_length];
		for (int i = 0, j = 0; i < exp_length; i++)
		{
			if (lextable.table[lextable_pos + i].lexema == LEX_ID || lextable.table[lextable_pos + i].lexema == LEX_LITERAL)
			{
				if (st.head != NULL && st.head->lex.lexema == '(' && e == 0)
					e = 1;
				if (lextable.table[lextable_pos + i].lexema == LEX_ID && (idtable.table[lextable.table[lextable_pos + i].idxTI].idtype == IT::F || idtable.table[lextable.table[lextable_pos + i].idxTI].iddatatype == IT::ARRAY))
					st.push(lextable.table[lextable_pos + i]);
				else
				{
					expression[j] = lextable.table[lextable_pos + i];
					j++;
				}
			}
			else if (lextable.table[lextable_pos + i].lexema == ')')
			{
				while (1)
				{
					if (st.head->lex.lexema == '(')
					{
						st.pop(); break;
					}
					expression[j] = st.pop();
					j++;
				}
				opened_thesis--;
			}
			else if (lextable.table[lextable_pos + i].lexema == ',')
				e++;
			else if (lextable.table[lextable_pos + i].lexema == '[');
			else if (lextable.table[lextable_pos + i].lexema == ']')
			{
				if (st.head->lex.lexema == LEX_ID && idtable.table[st.head->lex.idxTI].iddatatype == IT::ARRAY)
				{
					expression[j] = st.pop();
					j++;
					if (e > 0)
						e++;
				}
				else
				{
					rc = 0;
					break;
				}
			}
			else
			{
				if (lextable.table[lextable_pos + i].lexema == '(')
					opened_thesis++;
				while (lextable.table[lextable_pos + i].lexema != '(' && st.head != NULL && st.head->lex.lexema != '(')
				{

					if (((st.head->lex.lexema != LEX_OPERATOR) ? st.priority(st.head->lex.lexema) : st.priority((char)idtable.table[st.head->lex.idxTI].id[0])) <
						((lextable.table[lextable_pos + i].lexema != LEX_OPERATOR) ? st.priority(lextable.table[lextable_pos + i].lexema) : st.priority((char)idtable.table[lextable.table[lextable_pos + i].idxTI].id[0])))
						break;
					expression[j] = st.pop(); j++;
					if (expression[j - 1].lexema == LEX_ID && idtable.table[expression[j - 1].idxTI].idtype == IT::F)
					{
						expression[j] = LT::Entry{ '@', expression[j - 1].sn, -1 }; j++;
						expression[j] = LT::Entry{ (char)e, expression[j - 1].sn, -1 }; j++;
						e = 0;
					}
				}
				st.push(lextable.table[lextable_pos + i]);
			}
			if (i == exp_length - 1)
			{
				while (st.head != NULL)
				{
					expression[j] = st.pop(); j++;
					if (expression[j - 1].lexema == LEX_ID && idtable.table[expression[j - 1].idxTI].idtype == IT::F)
					{
						expression[j] = LT::Entry{ '@', expression[j - 1].sn, -1 }; j++;
						expression[j] = LT::Entry{ (char)e, expression[j - 1].sn, -1 }; j++;
						e = 0;
					}
				}
				while (j < exp_length)
				{
					expression[j] = LT::Entry{ LEX_NULL, expression[j - 1].sn, -1 }; j++;
				}
			}
		}
		for (int i = 0; i < exp_length; i++)
			lextable.table[lextable_pos + i] = expression[i];
		delete[] expression;
		cout << "=>\t";
		if (opened_thesis == 0 && rc == 1)
		{
			rc = 1;
			for (int i = 0; i < exp_length && lextable.table[lextable_pos + i].lexema != LEX_NULL; i++)
			{
				if (lextable.table[lextable_pos + i].lexema == LEX_OPERATOR)
					cout << idtable.table[lextable.table[lextable_pos + i].idxTI].id;
				else if (lextable.table[lextable_pos + i].lexema == '@')
				{
					char count[3];
					_itoa_s((int)lextable.table[lextable_pos + i + 1].lexema, count, 10);
					cout << "@" << count;
					i++;
				}
				else if (lextable.table[lextable_pos + i].lexema == LEX_ID)
				{
					if (idtable.table[lextable.table[lextable_pos + i].idxTI].idtype == IT::F)
						cout << "f";
					else if (idtable.table[lextable.table[lextable_pos + i].idxTI].iddatatype == IT::ARRAY)
						cout << "a";
					else
						cout << lextable.table[lextable_pos + i].lexema;
				}
				else
					cout << lextable.table[lextable_pos + i].lexema;
			}
			cout << endl;
		}
		else
			rc = 0;
		return rc;
	}
}