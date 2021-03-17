#pragma once
#include "FST.h"
#define LEXEMA_NUMBER 30

#define LEX_NULL			'n'

#define LEX_DEFINE			'&'
#define LEX_COMMA			','
#define LEX_COLON			':'
#define LEX_SEMICOLON		';'
#define LEX_POINT			'.'
#define LEX_EXCLAM			'!'
#define LEX_QUESTION		'?'

#define LEX_ORDER			'*'
#define LEX_ADHERE			'a'
#define LEX_FORM			'f'
#define LEX_MAIN			'm'
#define LEX_RELEASE			'r'
#define LEX_WRITE			'w'
#define LEX_SINCE			's'
#define LEX_TILL			'u'
#define LEX_SKIP			'b'
#define LEX_CHECK			'c'
#define LEX_GET				'g'
#define LEX_END				'e'

#define LEX_TYPE			't'
#define LEX_ID				'i'
#define LEX_LITERAL			'l'

#define LEX_LEFTCORNER		'<'
#define LEX_RIGHTCORNER		'>'
#define LEX_LEFTBRACKET		'['
#define LEX_RIGHTBRACKET	']'
#define LEX_LEFTTHESIS		'('
#define LEX_RIGHTTHESIS		')'
#define LEX_EQUAL			'='
#define LEX_OPERATOR		'v'


namespace Lexem
{
	struct LEXEM
	{
		struct ka
		{
			char lexema;
			int states;
			FST::NODE* nodes;
		}*fstn;
	};
	LEXEM GetLexem();
}