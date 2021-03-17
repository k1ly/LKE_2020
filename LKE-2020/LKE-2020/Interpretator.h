#pragma once
#include <iostream>
#include "Log.h"
#include "In.h"
#include "Tables.h"
#include "Polish.h"
#include <iostream>
#include <string>
#include <fstream>
#define BEFORE_DATA_SECTIONS_ENTRY ".586\n.model flat, stdcall\n\nincludelib kernel32.lib\nincludelib libucrt.lib\n"
#define CSMAXSIZE 255

namespace CodeGen
{
	enum INSTRUCTIONTYPE
	{// ���� ����������
		FUNC = 0,	// ������������� ������� *<...>ti
		PARM,		// �������� : <ti,...>
		PUSH,		// ��������� ���������� � ����
		INDX,		// ���������� ������� : i[...]
		CALL,		// ����� ������� : i(...)
		RET,		// ������� �������� �������: release >> l/i/expression
		WRT,		// ����� : write << l/i/expression
		CHK,		// ������� : check  l/i/expression =>
		NEXT,		// ������� : get =>
		CYC,		// ���� : since  i = l/i/expression
		SKIP,		// ����� : skip

		ENDP,		// ����� ��������� : func_name ENDP
		ADD,		// +
		SUB,		// -
		RST,		// %
		DIV,		// /
		MUL,		// *
		EQU,		// ?
		NEQU,		// !
		LESS,		// <
		GRTR,		// >
		EXECUTE		// ����������� �������� ��������� i = (...);
	};
	struct ConstSegment
	{
		char** Data;
		int size;
		int maxSize;
		ConstSegment(int _size)
		{
			size = 0;
			maxSize = _size + 4;
			Data = new char* [maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			Data[size++] = (char*)BEFORE_DATA_SECTIONS_ENTRY;
		}
	};
	struct DataSegment
	{
		char** Data;
		int size;
		int maxSize;
		DataSegment(int _size)
		{
			size = 0;
			maxSize = _size + 1;
			Data = new char* [maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			Data[size++] = (char*)"\n\n.data";
		}
	};
	struct CodeSegment
	{
		char** Data;
		int size;
		int maxSize;
		void add(std::string str);
		CodeSegment()
		{
			size = 0;
			maxSize = CSMAXSIZE;
			Data = new char* [maxSize];
			for (int i = 0; i < maxSize; i++)
				Data[i] = new char[TI_STR_MAXSIZE];
			Data[size++] = (char*)"\n\n.code";
		}
	};
	void adhere(IT::IdTable& idtable, LT::LexTable& lextable, ConstSegment& cnst);
	void form(IT::IdTable& idtable, LT::LexTable& lextable, ConstSegment& cnst);
	void add(IT::IdTable& idtable, ConstSegment& cnst);
	void add(IT::IdTable& idtable, DataSegment& dataseg);
	void generateExpression(int expStart, CodeSegment& CS, int idxTI, LT::LexTable l, IT::IdTable iT);
	void	CodeSegmentGeneration(CodeSegment& CS, LT::LexTable l, IT::IdTable& iT);
	std::string	generateInstructions(INSTRUCTIONTYPE t, int idxTI, IT::IdTable iT, IT::IDDATATYPE type = IT::UNIT, std::string func_name = "");
	void endOfFucntion(CodeSegment& CS);
	void startGeneration(const char* file, ConstSegment& CnstS, DataSegment& DS, CodeSegment& CS);
	void PrintData(Log::LOG log, ConstSegment& cnst, DataSegment& dataseg, CodeSegment& codeseg);
}