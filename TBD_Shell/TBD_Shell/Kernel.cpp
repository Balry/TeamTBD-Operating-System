#include "Kernel.h"
#include <direct.h>
#include <string>
#include <iostream>


// Constructor
kernel::kernel(void)
{
}

// Destructor
kernel::~kernel(void)
{
}

//Get Properties
int kernel::Get_Register0()
{
	return register0;
}

int kernel::Get_Register1()
{
	return register1;
}

int kernel::Get_Register2()
{
	return register2;
}

int kernel::Get_Register3()
{
	return register3;
}

// Set Properties
void kernel::Set_Register0(int pValue)
{
	register0 = pValue;
}
void kernel::Set_Register1(char * paddress)
{
	register1 = (int)paddress;
}
void kernel::Set_Register1(const char * paddress)
{
	register1 = (int)paddress;
}
void kernel::Set_Register1(char pChar)
{
	register1 = (int)pChar;
}
void kernel::Set_Register1(int pValue)
{
	register1 = pValue;
}
void kernel::Set_Register1(FILE* pFile)
{
	register1 = (int)pFile;
}
void kernel::Set_Register2(int pValue)
{
	register2 = pValue;

}
void kernel::Set_Register2(char * paddress)
{
	register2 = (int)paddress;
}
void kernel::Set_Register2(const char * paddress)
{
	register2 = (int)paddress;
}
void kernel::System_Call()
{
	switch (register0)
	{
	case(0) :
		exit(0);
		break;
	case(1) :
		input();
		break;
	case(2) :
		outputDisplay();
		break;
	case(3) :
		creatdir();
		break;
	case(4) :
		changedir();
		break;
	case(5) :
		removedir();
		break;
	case(6) :
		createfile();
		break;
	case(7) :
		openfileInput();
		break;
	case(8) :
		openfileOutput();
		break;
	case(9) :
		readfromfile();
		break;
	case(10) :
		writetofile();
		break;
	case(11) :
		closefile();
		break;
	case(12) :
		deletefile();
		break;
	case(13) :
		contentsofDir();
		break;
	case(14) :
		Return_Current_Directory();
		break;
	case(15) :
		dateandtime();
		break;
	default:
		register3 = 1;
		break;
	}

}

//system calls
void kernel::Return_Current_Directory()
{
	char *cCurrentPath = new  char[register_size];	// Get a character array pointer with a length of what was passed in register 1

	_getcwd(cCurrentPath, register_size); // Use the Windows API call to get the directory

	char * sPath = (char *)register1;	//sPath is a pointer to the character array back in the calling program
	strcpy_s(sPath, register_size, cCurrentPath);
	delete[] cCurrentPath;
	register3 = 0;
}
void kernel::outputDisplay()
{
	std::cout<< (char)register1;
	register3 = 0;
	
}
void kernel::input()
{
	char* result=(char*)register2;
	scanf_s("%c", &result);
	register1=(int)result;
	register3 = 0;
}
void kernel::creatdir()
{
	char* cNewdir = (char*)register1;
	register3=_mkdir(cNewdir);
}
void kernel::changedir()
{
	char* newdir = (char*)register1;
	register3=_chdir(newdir);
}
void kernel::removedir()
{
	char* newdir = (char*)register1;
	register3=_rmdir(newdir);
	
}
//returns contenst of dir as int
void kernel::contentsofDir()
{
	if (!system(NULL))return;
	int i = system("dir");
	register1 = i;
	register3 = 0;
}
//puts file in currentDir
//will overwright files that does exist
void kernel::createfile()
{
	char* name = (char*)register1;
	FILE* file;
	fopen_s(&file, name, "w");
	if (file != nullptr)
	{
		fclose(file);
		register3 = 0;
	}
		else register3 = 99;//error

}


void kernel::openfileInput()
{
	char* name = (char*)register1;
	FILE* myfile;
	fopen_s(&myfile,name, "r");
	if (myfile == nullptr)
	{
		register1 = (int)myfile;
		register3 = 99;//file does not exist
		return;
	}
	register1 = (int)myfile;
	register3 = 0;
}


void kernel::openfileOutput()
{
	char* name = (char*)register1;
	FILE* myfile;
	fopen_s(&myfile,name, "w");
	if (myfile == NULL)
	{
		register1 = (int)myfile;
		register3 = 99;//file does not exist
		return;
	}
	register1 = (int)myfile;
	register3 = 0;
}


void kernel::closefile()
{
	FILE* myfile = (FILE*)register1;
	if (myfile == NULL)
	{
		register3 = 99;//file not open
		return;
	}
	register3=fclose(myfile);
}


void kernel::deletefile()
{
	char* name = (char*)register1;
	int error = remove(name);
	if (error != 0)
	{
		register3 = 0;
	}
	else register3 = error;//file could not be deleted
}



void kernel::readfromfile()
{
	FILE* myfile = (FILE*)register1;
	if (myfile != NULL)
	{
		int error;
		if (!feof(myfile))
		{
			register2 = fgetc(myfile);
			error = ferror(myfile);
			if (error)
			{
				register3 = error;//error with file
			}
			else
			{
				register3 = 0;
			}
		}
		else
		{
			register3 = 99;//file has reached eor
		}
	}
	else
	{
		register3 = 99;//file not open
	}
}


void kernel::writetofile()
{
	FILE* myfile = (FILE*)register1;
	if (myfile != NULL)
	{
		int error;
		if (!feof(myfile))
		{
			fputc(register2, myfile);
			error = ferror(myfile);
			if (error)
			{
				register3 = error;//error with file
			}
			else
			{
				register3 = 0;
			}
		}
		else
		{
			register3 = 99;//file has reached eor
		}
	}
	else
	{
		register3 = 99;//file not open
	}
}


void kernel::dateandtime()
{
	register1 = (int)__DATE__;
	register2 = (int)__TIME__;
	register3 = 0;
}