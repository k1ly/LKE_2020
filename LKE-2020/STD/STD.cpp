#include "pch.h"
#include "framework.h"
#include <iostream>
#include <math.h>
#include <Windows.h>
#pragma warning(disable: 4996)

extern "C"
{
	int _stdcall comprnotes(char* s1, char* s2)
	{
		if (!s1 || !s2)
		{
			std::cout << "ERROR: Null Pointer parameter!" << std::endl;
			system("pause");
			ExitProcess(0);
		}
		int i = strcmp(s1, s2);
		if (i != 0)
			i = 0;
		else
			i = 1;
		return i;
	}
	int _stdcall notelength(char* s)
	{
		if (!s)
		{
			std::cout << "ERROR: Null Pointer parameter!" << std::endl;
			system("pause");
			ExitProcess(0);
		}
		else
			return strlen(s);
	}
	int _stdcall copynote(char* s1, char* s2)
	{
		if (!s1 || !s2)
		{
			std::cout << "ERROR: Null Pointer parameter!" << std::endl;
			system("pause");
			ExitProcess(0);
		}
		strcpy(s1, s2);
		return 1;
	}
	char* _stdcall cncatnotes(char* s1, char* s2)
	{
		char* buf;
		if (!s1 || !s2)
		{
			std::cout << "ERROR: Null Pointer parameter!" << std::endl;
			system("pause");
			ExitProcess(0);
		}
		else
		{
			if (strlen(s1) + strlen(s2) > 255)
			{
				std::cout << "ERROR: Result string length is over StringMaxSize(255)!" << std::endl;
				system("pause");
				ExitProcess(0);
			}
			buf = new char[255];
			strcpy(buf, s1);
			strcat(buf, s2);
		}
		return  buf;
	}
	int _stdcall powerunit(int u, int n)
	{
		return (int)pow(u, n);
	}
	void _stdcall writenote(char* n)
	{
		if (n != nullptr)
				std::cout << n;
		else
			std::cout << "Empty line!";
	}
	void _stdcall writeidle(int i)
	{
		if (i == 0)
			std::cout << "false";
		else
			std::cout << "true";
	}
	void _stdcall writeunit(int u)
	{
		if (u < 0)
			std::cout << (unsigned)u;
		else
			std::cout << u;
	}
}