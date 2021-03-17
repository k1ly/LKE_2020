#include "MFST.h"

int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];

#define MFST_TRACE_START std::cout	<< std::setw(4) << std::left << "Шаг " << ": "\
									<< std::setw(20) << std::left << " Правило"\
									<< std::setw(30) << std::left << " Входная лента"\
									<< std::setw(20) << std::left << " Стек"\
									<< std::endl

#define MFST_TRACE1 std::cout	<< std::setw(4) << std::left << ++FST_TRACE_n << ": "\
								<< std::setw(20) << std::left << rule.GetCRule(rbuf, nrulechain)\
								<< std::setw(30) << std::left << GetCLenta(lbuf, lenta_position)\
								<< std::setw(20) << std::left << GetCSt(sbuf)\
								<< std::endl
#define MFST_TRACE2 std::cout	<< std::setw(4) << std::left << FST_TRACE_n << ": "\
								<< std::setw(20) << std::left << " "\
								<< std::setw(30) << std::left << GetCLenta(lbuf, lenta_position)\
								<< std::setw(20) << std::left << GetCSt(sbuf)\
								<< std::endl
#define MFST_TRACE3 std::cout	<< std::setw(4) << std::left << ++FST_TRACE_n << ": "\
								<< std::setw(20) << std::left << " "\
								<< std::setw(30) << std::left << GetCLenta(lbuf, lenta_position)\
								<< std::setw(20) << std::left << GetCSt(sbuf)\
								<< std::endl
#define MFST_TRACE4(n) std::cout	<< std::setw(4) << std::left << ++FST_TRACE_n << ": "\
									<< std::setw(20) << std::left << n << std::endl
#define MFST_TRACE5(n) std::cout	<< std::setw(4) << std::left << FST_TRACE_n << ": "\
									<< std::setw(20) << std::left << n << std::endl
#define MFST_TRACE6(n,k) std::cout	<< std::setw(4) << std::left << FST_TRACE_n << ": "\
									<< std::setw(20) << std::left << n << k << std::endl
#define MFST_TRACE7 std::cout	<< std::setw(4) << std::left << state.lenta_position << ": "\
								<< std::setw(20) << std::left << rule.GetCRule(rbuf, state.nrulechain) << std::endl
#define MFST_TRACE7_2 *tbl.stream << std::setw(4) << std::left << state.lenta_position << ": "\
								<< std::setw(20) << std::left << rule.GetCRule(rbuf, state.nrulechain) << std::endl

#define MFST_TRACE_CLEAR	for (int r = 0; rbuf[r] != 0; r++) rbuf[r] = 0;\
							for (int s = 0; sbuf[s] != 0; s++) sbuf[s] = 0;\
							for (int l = 0; lbuf[l] != 0; l++) lbuf[l] = 0


namespace MFST
{
	Mfststate::Mfststate(short pposition, MFSTSTSTACK pst, short pnrulechain)
	{
		lenta_position = pposition;
		nrulechain = pnrulechain;
		st = pst;
	}
	Mfststate::Mfststate(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{
		lenta_position = pposition;
		nrule = pnrule;
		nrulechain = pnrulechain;
		st = pst;
	}
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	}
	Mfst::Mfst(LT::LexTable& lt, GRB::Greibach& grb)
	{
		lextable = lt;
		greibach = grb;
		lenta = new GRBALPHABET[lenta_size = lt.size + 1];
		for (int i = 0; i < lenta_size - 1; i++)
			lenta[i] = GRB::Rule::Chain::T(lt.table[i].lexema);
		lenta[lenta_size - 1] = greibach.stbottomT;
		lenta_position = 0;
		st.push(greibach.stbottomT);
		st.push(greibach.startN);
		nrule = -1;
		nrulechain = -1;
	}
	char* Mfst::GetCSt(char* buf)
	{
		for (int i = (signed)st.size() - 1; i >= 0; --i)
		{
			short p = st.c[i];
			buf[st.size() - i - 1] = GRB::Rule::Chain::AlphabetToChar(p);
		}
		buf[st.size()] = 0;
		return buf;
	}
	char* Mfst::GetCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)
			buf[i - pos] = GRB::Rule::Chain::AlphabetToChar(lenta[i]);
		buf[i - pos] = 0;
		return buf;
	}
	bool Mfst::GetDiagnosis(Log::LOG log)
	{
		bool rc = 0;
		int errid = 0;
		int lpos = -1;
		Log::WriteLine(log, "\n-----------------------------", "");
		for (int i = 0; i < MFST_DIAGN_NUMBER && (lpos = diagnosis[i].lenta_position) >= 0; i++)
		{
			rc = 1;
			errid = greibach.GetRule(diagnosis[i].nrule).iderror;
			Error::ERROR err = Error::geterrorpos(errid, lextable.table[lpos].sn);
			if (i == MFST_DIAGN_NUMBER - 1)
				throw err;
			else
				Log::WriteError(log, err);
		}
		return rc;
	}
	bool Mfst::SaveState()
	{
		storestate.push(Mfststate(lenta_position, st, nrule, nrulechain));
		//MFST_TRACE6("SAVESTATE:", storestate.size());
		return 1;
	}
	bool Mfst::ResetState()
	{
		bool rc = 0;
		Mfststate state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			//MFST_TRACE5("RESSTATE");
			//MFST_TRACE2;
			MFST_TRACE_CLEAR;
		}
		return rc;
	}
	bool Mfst::PushChain(GRB::Rule::Chain chain)
	{
		for (int i = chain.size - 1; i >= 0; i--)
			st.push(chain.nt[i]);
		return 1;
	}

	Mfst::RC_STEP Mfst::Step()
	{
		RC_STEP rc = SURPRISE;
		if (lenta_position < lenta_size)
		{
			if (GRB::Rule::Chain::IsN(st.top()))
			{
				GRB::Rule rule;
				if ((nrule = greibach.GetRule(st.top(), rule)) >= 0)
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.GetNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						//MFST_TRACE1;
						SaveState(); st.pop(); PushChain(chain); rc = NS_OK;
						//MFST_TRACE2;
						MFST_TRACE_CLEAR;
					}
					else
					{
						//MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE");
						SaveDiagnosis(NS_NORULECHAIN); rc = ResetState() ? NS_NORULECHAIN : NS_NORULE;
					}
				}
				else rc = NS_ERROR;
			}
			else if (st.top() == lenta[lenta_position])
			{
				lenta_position++; st.pop(); nrulechain = -1; rc = TS_OK;
				//MFST_TRACE3;
				MFST_TRACE_CLEAR;
			}
			else
			{
				//MFST_TRACE4("TS_NOK/NS_NORULECHAIN");
				rc = ResetState() ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			//MFST_TRACE4("LENTA_END");
			rc = LENTA_END;
		}
		return rc;
	}
	bool Mfst::Start(Log::LOG log)
	{
		//MFST_TRACE_START;
		std::cout << "\n------ SYNTAX ANALYSIS -------\n";
		bool rc = 0;
		RC_STEP rc_step = SURPRISE;
		rc_step = Step();
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = Step();
		switch (rc_step)
		{
		case LENTA_END: //MFST_TRACE4("------>LENTA_END");
			std::cout << "\nВсего строк: " << lenta_size << ", синтаксический анализ выполнен без ошибок" << std::endl;
			rc = 1;
			break;
		case NS_NORULE: //MFST_TRACE4("------>NS_NORULE");
			GetDiagnosis(log);
			break;
		case NS_NORULECHAIN: //MFST_TRACE4("------>NS_NORULECHAIN");
			break;
		case NS_ERROR: //MFST_TRACE4("------>NS_ERROR");
			break;
		case SURPRISE: //MFST_TRACE4("------>SURPRISE");
			break;
		}
		return rc;
	}

	bool Mfst::SaveDiagnosis(RC_STEP prc_step)
	{
		bool rc = 0;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position)
			k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short i = k + 1; i < MFST_DIAGN_NUMBER; i++)
				diagnosis[i].lenta_position = -1;
		}
		return rc;
	}
	void Mfst::PrintRules(Tables::TABLE &tbl)
	{
		*tbl.stream << "\n-------- PARSE TREE ------------\n\n";
		Mfststate state;
		GRB::Rule rule;
		for (unsigned int i = 0; i < storestate.size(); i++)
		{
			state = storestate.c[i];
			rule = greibach.GetRule(state.nrule);
			//MFST_TRACE7;
			MFST_TRACE7_2;
			MFST_TRACE_CLEAR;
		}
	}
	bool Mfst::SaveDeducation()
	{
		Mfststate state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = (short)storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (int i = 0; i < (int)storestate.size(); i++)
		{
			state = storestate.c[i];
			deducation.nrules[i] = state.nrule;
			deducation.nrulechains[i] = state.nrulechain;
		}
		return 1;
	}
}
