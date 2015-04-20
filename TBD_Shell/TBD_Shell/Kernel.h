#include <stdio.h>
#pragma once

class kernel
{
private:
	int register0;
	int register1;
	int register2;
	int register3;
	const int register_size = 255;
	void Return_Current_Directory();
	void outputDisplay();
	void outputInt();
	void input();
	void creatdir();
	void changedir();
	void removedir();
	void contentsofDir();
	void createfile();
	void openfileInput();
	void openfileOutput();
	void closefile();
	void deletefile();
	void readfromfile();
	void writetofile();
	void dateandtime();

public:
	kernel(void);
	~kernel(void);
	int Get_Register0();
	int Get_Register1();
	int Get_Register2();
	int Get_Register3();
	void Set_Register0(int pValue);
	void Set_Register1(char * pAddress);
	void Set_Register1(const char * paddress);
	void Set_Register1(char pChar);
	void Set_Register1(int pValue);
	void Set_Register1(FILE* pFile);
	void Set_Register2(int pValue);
	void Set_Register2(char * pAddress);
	void Set_Register2(const char * paddress);
	void System_Call();
};