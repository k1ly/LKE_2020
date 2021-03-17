#include "In.h"
using namespace std;

namespace In
{
	IN GetIn(Parm::PARM& parm)
	{
		IN* inf = new IN;
		inf->table = new IN::pos[10];

		int col = 0;
		int line = 1;

		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];
		text[0] = 0;

		ifstream fin(parm.in);
		if (fin.fail())
			throw ERROR_THROW(13);

		bool file = 0;
		bool string = 0;
		bool comment = 0;

		while (inf->size < IN_MAX_LEN_TEXT)
		{
			char c;	fin.get(c);
			unsigned char u = c;
			if (fin.eof())
			{
				if (string || file)
					throw ERROR_THROW_IN(100, line, col);
				if (comment || inf->code[text[inf->size - 1]] == inf->P || text[inf->size - 1] == IN_CODE_SEP)
				{
					if (!comment)
						inf->ignore++;
					if (text[inf->size - 1] == IN_CODE_SEP)
						inf->lines--;
					text[inf->size - 1] = IN_CODE_ENDS;
					inf->size--;
				}
				else
					text[inf->size] = IN_CODE_ENDS;
				inf->lines++;
				break;
			}

			IN::pos t;
			t.col = col;
			t.line = line;
			switch (inf->code[u])
			{
			case inf->S: {
				if (string || file)
					throw ERROR_THROW_IN(101, line, col);
				if (inf->size > 0 && text[inf->size - 1] != IN_CODE_SEP)
				{
					if (inf->code[text[inf->size - 1]] == inf->P)
					{
						text[inf->size - 1] = IN_CODE_SEP;
						inf->ignore++;
					}
					else
					{
						text[inf->size] = IN_CODE_SEP;
						inf->addpos(t);
						inf->size++;
					}
					inf->lines++;
				}
				else inf->ignore++;
				comment = 0;
				col = 0;
				line++;
			} break;
			case inf->T: {
				if (!comment)
				{
					text[inf->size] = u;
					inf->addpos(t);
					inf->size++;
				}
				else inf->ignore++;
				col++;
			} break;
			case inf->X: {
				if (!comment)
				{
					if (u == '\"' && !file)
						string = !string;
					if (u == '\'' && !string)
						file = !file;
					if (string || file || u == '\"' || u == '\'')
					{
						text[inf->size] = u;
						inf->addpos(t);
						inf->size++;
					}
					else
					{
						if (inf->code[text[inf->size - 1]] == inf->P)
						{
							text[inf->size - 1] = u;
							inf->ignore++;
						}
						else
						{
							text[inf->size] = u;
							inf->addpos(t);
							inf->size++;
						}
					}
				}
				else inf->ignore++;
				col++;
			} break;
			case inf->P: {
				if (!comment)
				{
					if (text[inf->size - 1] == '>' && text[inf->size - 2] == '=')
						col++;
					if (inf->size > 0 && (string || file ||
						(inf->code[text[inf->size - 1]] != inf->X && inf->code[text[inf->size - 1]] != inf->P && text[inf->size - 1] != IN_CODE_SEP)))
					{
						text[inf->size] = u;
						inf->addpos(t);
						inf->size++;
					}
					else inf->ignore++;
				}
				else inf->ignore++;
				col++;
			} break;
			case inf->I: {
				if (!string && !file)
				{
					if (inf->code[text[inf->size - 1]] == inf->P)
						inf->ignore++;
					comment = 1;
					inf->ignore++;
				}
				else
				{
					text[inf->size] = u;
					inf->addpos(t);
					inf->size++;
				}
				col++;
			} break;
			case inf->F: {
				if (!comment)
					throw ERROR_THROW_IN(100, line, col);
				inf->ignore++;
				col++;
			} break;
			default: {
				if (!comment)
				{
					text[inf->size] = inf->code[u];
					inf->addpos(t);
					inf->size++;
				}
				else inf->ignore++;
				col++;
			}
			}
		}
		fin.close();
		inf->text = text;

		return *inf;
	}

	void IN::addpos(pos e)
	{
		IN::pos* t = new pos[size + 1];
		for (int i = 0; i < size; i++)
			t[i] = table[i];
		delete[] table;
		table = t;
		table[size] = e;
	}
}