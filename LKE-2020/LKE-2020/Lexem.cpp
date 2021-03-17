#include "Lexem.h"

namespace Lexem
{
	LEXEM GetLexem()
	{
		LEXEM* l = new LEXEM;
		l->fstn = new LEXEM::ka[LEXEMA_NUMBER + 7];


		l->fstn[0] = { LEX_DEFINE, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('&', 1)), FST::NODE() } };
		l->fstn[1] = { LEX_COMMA, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION(',', 1)), FST::NODE() } };
		l->fstn[2] = { LEX_COLON, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION(':', 1)), FST::NODE() } };
		l->fstn[3] = { LEX_SEMICOLON, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION(';', 1)), FST::NODE() } };
		l->fstn[4] = { LEX_POINT, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('.', 1)), FST::NODE() } };
		l->fstn[5] = { LEX_EXCLAM, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('!', 1)), FST::NODE() } };
		l->fstn[6] = { LEX_QUESTION, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('?', 1)), FST::NODE() } };

		l->fstn[7] = { LEX_LEFTCORNER, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('<', 1)), FST::NODE() } };
		l->fstn[8] = { LEX_RIGHTCORNER, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('>', 1)), FST::NODE() } };
		l->fstn[9] = { LEX_LEFTBRACKET, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('[', 1)), FST::NODE() } };
		l->fstn[10] = { LEX_RIGHTBRACKET, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION(']', 1)), FST::NODE() } };
		l->fstn[11] = { LEX_LEFTTHESIS, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('(', 1)), FST::NODE() } };
		l->fstn[12] = { LEX_RIGHTTHESIS, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION(')', 1)), FST::NODE() } };
		l->fstn[13] = { LEX_EQUAL, 2, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('=', 1)), FST::NODE() } };

		l->fstn[14] = { LEX_OPERATOR, 2, new FST::NODE[8]{ FST::NODE(5, 
			FST::RELATION('+', 1), FST::RELATION('-', 1), FST::RELATION('*', 1), FST::RELATION('/', 1), FST::RELATION('%', 1)), FST::NODE() } };


		l->fstn[15] = { LEX_ORDER, 6, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('o', 1)),
	FST::NODE(1, FST::RELATION('r', 2)), FST::NODE(1, FST::RELATION('d', 3)), FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE(1, FST::RELATION('r', 5)), 
	FST::NODE() } };
		l->fstn[16] = { LEX_ADHERE, 7, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('A', 1)),
	FST::NODE(1, FST::RELATION('d', 2)), FST::NODE(1, FST::RELATION('h', 3)), FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE(1, FST::RELATION('r', 5)), FST::NODE(1, FST::RELATION('e', 6)),
	FST::NODE() } };
		l->fstn[17] = { LEX_FORM, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('F', 1)),
	FST::NODE(1, FST::RELATION('o', 2)), FST::NODE(1, FST::RELATION('r', 3)), FST::NODE(1, FST::RELATION('m', 4)),
	FST::NODE() } };
		l->fstn[18] = { LEX_MAIN, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('m', 1)),
FST::NODE(1, FST::RELATION('a', 2)), FST::NODE(1, FST::RELATION('i', 3)), FST::NODE(1, FST::RELATION('n', 4)),
FST::NODE() } };
		l->fstn[19] = { LEX_RELEASE, 8, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('r', 1)),
FST::NODE(1, FST::RELATION('e', 2)), FST::NODE(1, FST::RELATION('l', 3)), FST::NODE(1, FST::RELATION('e', 4)),
FST::NODE(1, FST::RELATION('a', 5)), FST::NODE(1, FST::RELATION('s', 6)), FST::NODE(1, FST::RELATION('e', 7)),
FST::NODE() } };
		l->fstn[20] = { LEX_WRITE, 6, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('w', 1)),
FST::NODE(1, FST::RELATION('r', 2)), FST::NODE(1, FST::RELATION('i', 3)), FST::NODE(1, FST::RELATION('t', 4)),
FST::NODE(1, FST::RELATION('e', 5)),
FST::NODE() } };
		l->fstn[21] = { LEX_SINCE, 6, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('s', 1)),
FST::NODE(1, FST::RELATION('i', 2)), FST::NODE(1, FST::RELATION('n', 3)), FST::NODE(1, FST::RELATION('c', 4)),
FST::NODE(1, FST::RELATION('e', 5)),
FST::NODE() } };
		l->fstn[22] = { LEX_TILL, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('t', 1)),
FST::NODE(1, FST::RELATION('i', 2)), FST::NODE(1, FST::RELATION('l', 3)), FST::NODE(1, FST::RELATION('l', 4)),
FST::NODE() } };
		l->fstn[23] = { LEX_SKIP, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('s', 1)),
FST::NODE(1, FST::RELATION('k', 2)), FST::NODE(1, FST::RELATION('i', 3)), FST::NODE(1, FST::RELATION('p', 4)),
FST::NODE() } };
		l->fstn[24] = { LEX_CHECK, 6, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('c', 1)),
FST::NODE(1, FST::RELATION('h', 2)), FST::NODE(1, FST::RELATION('e', 3)), FST::NODE(1, FST::RELATION('c', 4)),
FST::NODE(1, FST::RELATION('k', 5)),
FST::NODE() } };
		l->fstn[25] = { LEX_GET, 4, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('g', 1)),
FST::NODE(1, FST::RELATION('e', 2)), FST::NODE(1, FST::RELATION('t', 3)),
FST::NODE() } };
		l->fstn[26] = { LEX_END, 4, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('e', 1)),
FST::NODE(1, FST::RELATION('n', 2)), FST::NODE(1, FST::RELATION('d', 3)),
FST::NODE() } };


		l->fstn[27] = { LEX_TYPE, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('u', 1)),
FST::NODE(1, FST::RELATION('n', 2)), FST::NODE(1, FST::RELATION('i', 3)), FST::NODE(1, FST::RELATION('t', 4)),
FST::NODE() } };
		l->fstn[28] = { LEX_TYPE, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('n', 1)),
FST::NODE(1, FST::RELATION('o', 2)), FST::NODE(1, FST::RELATION('t', 3)), FST::NODE(1, FST::RELATION('e', 4)),
FST::NODE() } };
		l->fstn[29] = { LEX_TYPE, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('i', 1)),
FST::NODE(1, FST::RELATION('d', 2)), FST::NODE(1, FST::RELATION('l', 3)), FST::NODE(1, FST::RELATION('e', 4)),
FST::NODE() } };


		l->fstn[30] = { LEX_LITERAL, 5, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('t', 1)),
FST::NODE(1, FST::RELATION('r', 2)), FST::NODE(1, FST::RELATION('u', 3)), FST::NODE(1, FST::RELATION('e', 4)),
FST::NODE() } };
		l->fstn[31] = { LEX_LITERAL, 6, new FST::NODE[8]{ FST::NODE(1, FST::RELATION('f', 1)),
FST::NODE(1, FST::RELATION('a', 2)), FST::NODE(1, FST::RELATION('l', 3)), FST::NODE(1, FST::RELATION('s', 4)),
FST::NODE(1, FST::RELATION('e', 5)),
FST::NODE() } };

		l->fstn[32] = { LEX_LITERAL, 4, new FST::NODE[8]{ FST::NODE(2, FST::RELATION('\"', 1), FST::RELATION('\"', 2)), FST::NODE(302,
FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1),
FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1),
FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1),
FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1),
FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1),
FST::RELATION('z', 1),
FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), FST::RELATION('E', 1),
FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),
FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('M', 1), FST::RELATION('N', 1), FST::RELATION('O', 1),
FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1), FST::RELATION('S', 1), FST::RELATION('T', 1),
FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1), FST::RELATION('Y', 1),
FST::RELATION('Z', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), 
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('�', 1), FST::RELATION('�', 1),
FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),
FST::RELATION('&', 1), FST::RELATION('!', 1), FST::RELATION('?', 1), FST::RELATION(';', 1), FST::RELATION(':', 1),
FST::RELATION(',', 1), FST::RELATION('{', 1), FST::RELATION('}', 1), FST::RELATION('(', 1), FST::RELATION(')', 1),
FST::RELATION('.', 1), FST::RELATION('<', 1), FST::RELATION('>', 1), FST::RELATION('[', 1), FST::RELATION(']', 1),
FST::RELATION('+', 1), FST::RELATION('-', 1), FST::RELATION('*', 1), FST::RELATION('/', 1), FST::RELATION('%', 1),
FST::RELATION('=', 1), FST::RELATION('#', 1), FST::RELATION('\'', 1), FST::RELATION(' ', 1), FST::RELATION('	', 1),
FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2),
FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2),
FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2),
FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2),
FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), FST::RELATION('y', 2),
FST::RELATION('z', 2),
FST::RELATION('A', 2), FST::RELATION('B', 2), FST::RELATION('C', 2), FST::RELATION('D', 2), FST::RELATION('E', 2),
FST::RELATION('F', 2), FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),
FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('M', 2), FST::RELATION('N', 2), FST::RELATION('O', 2),
FST::RELATION('P', 2), FST::RELATION('Q', 2), FST::RELATION('R', 2), FST::RELATION('S', 2), FST::RELATION('T', 2),
FST::RELATION('U', 2), FST::RELATION('V', 2), FST::RELATION('W', 2), FST::RELATION('X', 2), FST::RELATION('Y', 2),
FST::RELATION('Z', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('�', 2), FST::RELATION('�', 2),
FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2),
FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),
FST::RELATION('&', 2), FST::RELATION('!', 2), FST::RELATION('?', 2), FST::RELATION(';', 2), FST::RELATION(':', 2),
FST::RELATION(',', 2), FST::RELATION('{', 2), FST::RELATION('}', 2), FST::RELATION('(', 2), FST::RELATION(')', 2),
FST::RELATION('.', 2), FST::RELATION('<', 2), FST::RELATION('>', 2), FST::RELATION('[', 2), FST::RELATION(']', 2),
FST::RELATION('+', 2), FST::RELATION('-', 2), FST::RELATION('*', 2), FST::RELATION('/', 2), FST::RELATION('%', 2),
FST::RELATION('=', 2), FST::RELATION('#', 2), FST::RELATION('\'', 2), FST::RELATION(' ', 2), FST::RELATION('	', 2)),
FST::NODE(1, FST::RELATION('\"', 3)),
FST::NODE() } };

		l->fstn[33] = { LEX_LITERAL, 4, new FST::NODE[8]{ FST::NODE(2, FST::RELATION('\'', 1), FST::RELATION('\'', 2)), FST::NODE(140,
FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1),
FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1),
FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1),
FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1),
FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1),
FST::RELATION('z', 1),
FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), FST::RELATION('E', 1),
FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),
FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('M', 1), FST::RELATION('N', 1), FST::RELATION('O', 1),
FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1), FST::RELATION('S', 1), FST::RELATION('T', 1),
FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1), FST::RELATION('Y', 1),
FST::RELATION('Z', 1), FST::RELATION('.', 1),
FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 1), FST::RELATION('e', 1),
FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 1), FST::RELATION('j', 1),
FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 1), FST::RELATION('o', 1),
FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 1), FST::RELATION('t', 1),
FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 1), FST::RELATION('y', 1),
FST::RELATION('z', 2),
FST::RELATION('A', 2), FST::RELATION('B', 2), FST::RELATION('C', 2), FST::RELATION('D', 2), FST::RELATION('E', 2),
FST::RELATION('F', 2), FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),
FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('M', 2), FST::RELATION('N', 2), FST::RELATION('O', 2),
FST::RELATION('P', 2), FST::RELATION('Q', 2), FST::RELATION('R', 2), FST::RELATION('S', 2), FST::RELATION('T', 2),
FST::RELATION('U', 2), FST::RELATION('V', 2), FST::RELATION('W', 2), FST::RELATION('X', 2), FST::RELATION('Y', 2),
FST::RELATION('Z', 2), FST::RELATION('.', 2)),
FST::NODE(1, FST::RELATION('\'', 3)),
FST::NODE() } };

		l->fstn[34] = { LEX_LITERAL, 6, new FST::NODE[8]{ FST::NODE(21,
FST::RELATION('0', 2),
FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),
FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5), FST::RELATION('5', 5),
FST::RELATION('6', 5), FST::RELATION('7', 5), FST::RELATION('8', 5), FST::RELATION('9', 5), FST::RELATION('0', 5)),
				FST::NODE(20,
FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),
FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5), FST::RELATION('5', 5),
FST::RELATION('6', 5), FST::RELATION('7', 5), FST::RELATION('8', 5), FST::RELATION('9', 5), FST::RELATION('0', 5)),
				FST::NODE(2, FST::RELATION('o', 3), FST::RELATION('X', 4)),
				FST::NODE(16,
FST::RELATION('1', 3), FST::RELATION('2', 3), FST::RELATION('3', 3), FST::RELATION('4', 3),
FST::RELATION('5', 3), FST::RELATION('6', 3), FST::RELATION('7', 3), FST::RELATION('0', 3),
FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5),
FST::RELATION('5', 5), FST::RELATION('6', 5), FST::RELATION('7', 5), FST::RELATION('0', 5)),
				FST::NODE(32,
FST::RELATION('1', 4), FST::RELATION('2', 4), FST::RELATION('3', 4), FST::RELATION('4', 4),
FST::RELATION('5', 4), FST::RELATION('6', 4), FST::RELATION('7', 4), FST::RELATION('8', 4),
FST::RELATION('9', 4), FST::RELATION('0', 4), FST::RELATION('A', 4), FST::RELATION('B', 4),
FST::RELATION('C', 4), FST::RELATION('D', 4), FST::RELATION('E', 4), FST::RELATION('F', 4),
FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5),
FST::RELATION('5', 5), FST::RELATION('6', 5), FST::RELATION('7', 5), FST::RELATION('8', 5),
FST::RELATION('9', 5), FST::RELATION('0', 5), FST::RELATION('A', 5), FST::RELATION('B', 5),
FST::RELATION('C', 5), FST::RELATION('D', 5), FST::RELATION('E', 5), FST::RELATION('F', 5)),
FST::NODE() } };

		l->fstn[35] = { LEX_LITERAL, 8, new FST::NODE[8]{ FST::NODE(2, FST::RELATION('{', 1), FST::RELATION('{', 6)), FST::NODE(21,
FST::RELATION('0', 3),
FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2),
FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),
FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6),
FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('8', 6), FST::RELATION('9', 6), FST::RELATION('0', 6)),
				FST::NODE(21,
FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2),
FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),
FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6),
FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('8', 6), FST::RELATION('9', 6), FST::RELATION('0', 6),
FST::RELATION(',', 1)),
				FST::NODE(2, FST::RELATION('o', 4), FST::RELATION('X', 5)),
				FST::NODE(17,
FST::RELATION('1', 4), FST::RELATION('2', 4), FST::RELATION('3', 4), FST::RELATION('4', 4),
FST::RELATION('5', 4), FST::RELATION('6', 4), FST::RELATION('7', 4), FST::RELATION('0', 4),
FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6),
FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('0', 6),
FST::RELATION(',', 1)),
				FST::NODE(33,
FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5),
FST::RELATION('5', 5), FST::RELATION('6', 5), FST::RELATION('7', 5), FST::RELATION('8', 5),
FST::RELATION('9', 5), FST::RELATION('0', 5), FST::RELATION('A', 5), FST::RELATION('B', 5),
FST::RELATION('C', 5), FST::RELATION('D', 5), FST::RELATION('E', 5), FST::RELATION('F', 5),
FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6),
FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('8', 6),
FST::RELATION('9', 6), FST::RELATION('0', 6), FST::RELATION('A', 6), FST::RELATION('B', 6),
FST::RELATION('C', 6), FST::RELATION('D', 6), FST::RELATION('E', 6), FST::RELATION('F', 6),
FST::RELATION(',', 1)),
FST::NODE(1, FST::RELATION('}', 7)),
FST::NODE() } };


		l->fstn[36] = { LEX_ID, 3, new FST::NODE[8]{ FST::NODE(104,
FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), FST::RELATION('E', 1),
FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),
FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('M', 1), FST::RELATION('N', 1), FST::RELATION('O', 1),
FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1), FST::RELATION('S', 1), FST::RELATION('T', 1),
FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1), FST::RELATION('Y', 1),
FST::RELATION('Z', 1), FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1),
FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1),
FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1),
FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1),
FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),
FST::RELATION('y', 1), FST::RELATION('z', 1),
FST::RELATION('A', 2), FST::RELATION('B', 2), FST::RELATION('C', 2), FST::RELATION('D', 2), FST::RELATION('E', 2),
FST::RELATION('F', 2), FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),
FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('M', 2), FST::RELATION('N', 2), FST::RELATION('O', 2),
FST::RELATION('P', 2), FST::RELATION('Q', 2), FST::RELATION('R', 2), FST::RELATION('S', 2), FST::RELATION('T', 2),
FST::RELATION('U', 2), FST::RELATION('V', 2), FST::RELATION('W', 2), FST::RELATION('X', 2), FST::RELATION('Y', 2),
FST::RELATION('Z', 2), FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2),
FST::RELATION('e', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2),
FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2),
FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2),
FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2),
FST::RELATION('y', 2), FST::RELATION('z', 2)),
				FST::NODE(124,
		FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), FST::RELATION('E', 1),
FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),
FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('M', 1), FST::RELATION('N', 1), FST::RELATION('O', 1),
FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1), FST::RELATION('S', 1), FST::RELATION('T', 1),
FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1), FST::RELATION('Y', 1),
FST::RELATION('Z', 1), FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1),
FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1),
FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1),
FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1),
FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),
FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1),
FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1),
FST::RELATION('9', 1), FST::RELATION('0', 1),
FST::RELATION('A', 2), FST::RELATION('B', 2), FST::RELATION('C', 2), FST::RELATION('D', 2), FST::RELATION('E', 2),
FST::RELATION('F', 2), FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),
FST::RELATION('K', 2), FST::RELATION('L', 2), FST::RELATION('M', 2), FST::RELATION('N', 2), FST::RELATION('O', 2),
FST::RELATION('P', 2), FST::RELATION('Q', 2), FST::RELATION('R', 2), FST::RELATION('S', 2), FST::RELATION('T', 2),
FST::RELATION('U', 2), FST::RELATION('V', 2), FST::RELATION('W', 2), FST::RELATION('X', 2), FST::RELATION('Y', 2),
FST::RELATION('Z', 2), FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2),
FST::RELATION('e', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2),
FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2),
FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2),
FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2),
FST::RELATION('y', 2), FST::RELATION('z', 2), FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2),
FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2),
FST::RELATION('9', 2), FST::RELATION('0', 2)),
FST::NODE() } };

		return *l;
	}
}