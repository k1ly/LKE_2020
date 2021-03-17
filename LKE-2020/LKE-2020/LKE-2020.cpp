#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "Tables.h"
#include "LT.h"
#include "IT.h"
#include "GRB.h"
#include "MFST.h"
#include "Polish.h"
#include "Check.h"
#include "Interpretator.h"
#include <iostream>
#define FILE_PATH_ASM "C:\\Users\\Кирилл\\OneDrive\\Documents\\LP_KP\\LKE-2020\\CODE\\CODE.asm"
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try
	{
		cout << "====== Начало трансляции =====\n";

		Parm::PARM parm = Parm::GetParm(argc, argv);
		log = Log::GetLog(parm);
		In::IN in = In::GetIn(parm);

		Log::WriteLine(log, "-----------------------------", "");
		Log::WriteLine(log, "---- Контрольный пример -----", "");
		Log::WriteLine(log, "---- на языке LKE-2020 ------", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);

		Tables::TABLE tbl = Tables::GetTables(parm, in);
		Tables::WriteTable(tbl, "all");

		GRB::Greibach grb = GRB::GetGreibach();
		MFST::Mfst mfst(tbl.lt, grb);
		mfst.Start(log);

		mfst.SaveDeducation();
		mfst.PrintRules(tbl);

		Polish::GetPolish(tbl);
		Semantic::SemanticAnalysis(log, tbl);

		//Tables::WriteTable(tbl, "lt");
		Tables::Close(tbl);

		CodeGen::ConstSegment CnstS(tbl.it.size);
		CodeGen::DataSegment Data(tbl.it.size);
		CodeGen::CodeSegment Code;

		CodeGen::adhere(tbl.it, tbl.lt, CnstS);
		CodeGen::form(tbl.it, tbl.lt, CnstS);
		CodeGen::add(tbl.it, CnstS);
		CodeGen::add(tbl.it, Data);

		CodeGen::CodeSegmentGeneration(Code, tbl.lt, tbl.it);
		CodeGen::startGeneration(FILE_PATH_ASM, CnstS, Data, Code);

		//CodeGen::PrintData(log, CnstS, Data, Code);
		Log::Close(log);

		cout << "====== Конец трансляции ======\n\n";
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		Close(log);
		cout << endl;
	}
	system("pause");
	return 0;
}