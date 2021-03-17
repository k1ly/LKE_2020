#pragma once
#include "Error.h"
#include "Log.h"
#include "LT.h"
#include "GRB.h"
#include "Tables.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <iomanip>
#define MFST_DIAGN_NUMBER 3
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE

namespace MFST
{
	class MFSTSTSTACK : public std::stack<short>
	{
	public: using std::stack<short>::c;
	};
	struct Mfststate
	{
		short lenta_position;
		short nrule;
		short nrulechain;
		MFSTSTSTACK st;
		Mfststate() { lenta_position = 0; nrule = -1; nrulechain = -1; };
		Mfststate(short pposition, MFSTSTSTACK pst, short pnrulechain);
		Mfststate(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);
	};
	struct Mfst
	{
		enum RC_STEP { NS_OK, NS_NORULE, NS_NORULECHAIN, NS_ERROR, TS_OK, TS_NOK, LENTA_END, SURPRISE };
		struct MfstDiagnosis
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis() { lenta_position = -1; rc_step = SURPRISE; 	nrule = -1; nrule_chain = -1; }
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		}*diagnosis = new MfstDiagnosis[MFST_DIAGN_NUMBER];
		GRBALPHABET* lenta = 0;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach greibach;
		LT::LexTable lextable;
		MFSTSTSTACK st;
		class MFSTSTATESTACK : public std::stack<Mfststate>
		{
		public: using std::stack<Mfststate>::c;
		} storestate;
		Mfst() { lenta_position = 0; nrule = 0; nrulechain = 0; lenta_size = 0; lextable = { 0 }; };
		Mfst(LT::LexTable &lt, GRB::Greibach &grb);
		char* GetCSt(char* buf);
		char* GetCLenta(char* buf, short pos, short n = 25);
		bool GetDiagnosis(Log::LOG log);
		bool SaveState();
		bool ResetState();
		bool PushChain(GRB::Rule::Chain chain);
		RC_STEP Step();
		bool Start(Log::LOG log);
		bool SaveDiagnosis(RC_STEP prc_step);
		void PrintRules(Tables::TABLE &tbl);
		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		}deducation;
		bool SaveDeducation();
	};
	
}