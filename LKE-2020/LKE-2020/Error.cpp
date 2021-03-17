#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "|SYSTEM| ������������ ��� ������"),
		ERROR_ENTRY(1, "|SYSTEM| ��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),

		ERROR_ENTRY(10, "|SYSTEM| �������� -in ������ ���� �����"),
		ERROR_ENTRY(11, "|SYSTEM| ��������� ����� ��������� -in"),
		ERROR_ENTRY(12, "|SYSTEM| ������ ��� �������� ����� ���������"),
		ERROR_ENTRY(13, "|SYSTEM| ������ ��� �������� ��������� ����"),
		ERROR_ENTRY_NODEF(14), ERROR_ENTRY_NODEF(15), ERROR_ENTRY_NODEF(16),
		ERROR_ENTRY_NODEF(17), ERROR_ENTRY_NODEF(18), ERROR_ENTRY_NODEF(19),

		ERROR_ENTRY(20, "|SYSTEM| ������ ��� �������� ��������� �����"),
		ERROR_ENTRY(21, "|SYSTEM| �������� ���������� ������ ������� ������"),
		ERROR_ENTRY(22, "|SYSTEM| �������� ���������� ������ ������� ���������������"),
		ERROR_ENTRY(23, "|SYSTEM| ������� �� ������� � �������"),
		ERROR_ENTRY(24, "|SYSTEM| ������������� �� ������ � �������"),
		ERROR_ENTRY_NODEF(25), ERROR_ENTRY_NODEF(26), ERROR_ENTRY_NODEF(27), ERROR_ENTRY_NODEF(28), ERROR_ENTRY_NODEF(29),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "|Lexical| ������������ ������ � �������� ����"),
		ERROR_ENTRY(101, "|Lexical| ������������ ������ � ��������� ��������"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "|Lexical| ������� �� �������"),
		ERROR_ENTRY(111, "|Lexical| ��������� ����� ���������� ��������"),
		ERROR_ENTRY(112, "|Semantic| ������������ ������� main"),
		ERROR_ENTRY(113, "|Semantic| ��������� ���������� ������� main"),
		ERROR_ENTRY(114, "|Semantic| ������� ������ ���������"),
		ERROR_ENTRY(115, "|Semantic| ��������� ������������� ���������"),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120, "|Semantic| ���������� ��������� �������"),
		ERROR_ENTRY(121, "|Semantic| ��������� ���������� �������"),
		ERROR_ENTRY(122, "|Semantic| ������������� ���������� ����� �����������"),
		ERROR_ENTRY(123, "|Lexical| ���������� �� ���������"),
		ERROR_ENTRY(124, "|Lexical| ������� ����� ��� ������"),
		ERROR_ENTRY(125, "|Lexical| ������� ��������� �������"),
		ERROR_ENTRY(126, "|Semantic| ��������� ���������� ����������"),
		ERROR_ENTRY(127, "|Semantic| ��������� ���������� �������"),
		ERROR_ENTRY(128, "|Semantic| ����������� ����� ������ �������"),
		ERROR_ENTRY(129, "|Semantic| ��������� ���������� �������"),

		ERROR_ENTRY(130, "|Lexical| ��������� ���������� ������������� ��������"),
		ERROR_ENTRY(131, "|Lexical| ������� ����� �������� ��������������"),
		ERROR_ENTRY(132, "|Lexical| �������� ������������� �������"),
		ERROR_ENTRY(133, "|Semantic| ������ ������� ������ ����� ������������� ���"),
		ERROR_ENTRY(134, "|Semantic| ��������� ��� �����"),
		ERROR_ENTRY(135, "|Semantic| �������� ������������� ����� �����"),
		ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY(200, "|Syntax| �������� ��������� ���������"),
		ERROR_ENTRY(201, "|Syntax| ������ � ���������� �����"),
		ERROR_ENTRY(202, "|Syntax| ������ � �������� �����"),
		ERROR_ENTRY(203, "|Syntax| ������ � �������� ����������"),
		ERROR_ENTRY(204, "|Syntax| ������ � ���������"),
		ERROR_ENTRY(205, "|Syntax| ������ � �������������� ��������"),
		ERROR_ENTRY(206, "|Syntax| ������ � �������� ���������"),
		ERROR_ENTRY(207, "|Syntax| ������ � ���������� �������"),
		ERROR_ENTRY(208, "|Syntax| ������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250),
		ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),

		ERROR_ENTRY(300, "|Semantic| ������������ ����� ���������"),
		ERROR_ENTRY(301, "|Semantic| ������������ ������������� ����"),
		ERROR_ENTRY(302, "|Semantic| ������������ ����� ���������� �������"),
		ERROR_ENTRY(303, "|Semantic| ������������ ���������� ���������� �������"),
		ERROR_ENTRY(304, "|Semantic| ��� ������������� �������� �� ������������� ���� �������"),
		ERROR_ENTRY(305, "|Semantic| �� ������� ������� ����"),
		ERROR_ENTRY(306, "|Semantic| ��������� ����������� ����������� ����������"),
		ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308), ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),

		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500), ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR* e = new ERROR;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			*e = errors[0];
		else
			*e = errors[id];
		return *e;
	}
	ERROR geterrorpos(int id, int line, int col)
	{
		ERROR* e = new ERROR;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			*e = errors[0];
		else
		{
			*e = errors[id];
			e->inext.line = line;
			e->inext.col = col;
		}
		return *e;
	}
}