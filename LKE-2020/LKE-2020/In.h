#pragma once
#include "Error.h"
#include "Parm.h"
#include <fstream>
#include <iostream>
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDS '\0'
#define IN_CODE_SEP '|'

#define IN_CODE_TABLE {\
/*0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F*/ \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::P, IN::S, IN::F, IN::F, IN::F, IN::F, IN::F, /* 0 */ \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /* 1 */ \
IN::P, IN::X, IN::X, IN::I, IN::F, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, /* 2 */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::X, IN::X, IN::X, IN::X, IN::X, IN::X, /* 3 */ \
IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /* 4 */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::X, IN::F, IN::X, IN::F, IN::F, /* 5 */ \
IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /* 6 */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::X, IN::F, IN::X, IN::F, IN::F, /* 7 */ \
																												\
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /* 8 */ \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /* 9 */ \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /* A */ \
IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /* B */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /* C */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /* D */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /* E */ \
IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /* F */ \
}

namespace In
{
	struct IN
	{
		enum { F = 0, T = 1, I = 2, S = 3, P = 4, X = 5 };
		int size = 0;
		int lines = 0;
		int ignore = 0;
		unsigned char* text = nullptr;
		int code[256] = IN_CODE_TABLE;
		struct pos
		{
			int line;
			int col;
		}*table = nullptr;
		void addpos(pos e);
	};
	IN GetIn(Parm::PARM &parm);
}