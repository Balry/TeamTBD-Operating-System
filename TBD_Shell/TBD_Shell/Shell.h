#include <string>
#include <sstream>
#include <vector>
#include "Kernel.h"
#pragma once

class Shell
{
public:
	Shell(){}
	void CommanLineInterface()
	{
		std::string command;
		do
		{
			command = CommandInput();
			std::string result = transducer(command);
			output(result);
		} while (command != "quit");
	}
private:
	kernel mykenrel;
	std::string CommandInput()
	{
		std::string result;
		char temp;
		do
		{
			mykenrel.Set_Register0(1);
			mykenrel.Set_Register2(temp);
			mykenrel.System_Call();
			result += (char)mykenrel.Get_Register1();
		} while (temp != 0);
	}
	std::string transducer(std::string command)
	{
		try
		{
			std::string result;
			std::vector<std::string>token = makeToken(command);
			if (token[0] == "dir")
			{
				result = getDir(token[1]);
			}
			else if (token[0] == "cd")
			{
				if (token.size == 2)
				{
					result = changeDir(token[1]);
				}
				else throw(99);
			}
			else if (token[0] == "copy")
			{
				if (token.size == 3)
				{
					result = copyFile(token[1], token[2]);
				}
				else throw(99);
			}
			else if (token[0] == "delete")
			{
				if (token.size == 2){ result = deleteFile(token[1]); }
				else throw(99);
			}
			else if (token[0] == "mkdir")
			{
				if (token.size == 2){ result = makeDir(token[1]); }
				else throw(99);
			}
			else if (token[0] == "dstat")
			{
				result = systemInfo();
			}
			else if (token[0] == "dfile")
			{
				if (token.size == 2){ result = fileContents(token[1]); }
				else throw(99);
			}
			else if (token[0] == "quit")
			{
				result = quit();
			}
			else throw (100);
		}
		catch (int e)
		{
			switch (e)
			{
			case(99):
				output("Invalid Parameters");
				break;
			case(100) :
				output("Invalid Command");
				break;
			case(101) :
				output("Error");
				break;
			default:
				break;
			}
		}
	}
	std::string getDir(std::string dir)
	{
		mykenrel.Set_Register0(12);
		mykenrel.System_Call();
		if (mykenrel.Get_Register3() != 0)
		{
			throw mykenrel.Get_Register3();
		}
		return intToString(mykenrel.Get_Register1());
	}
	std::string changeDir(std::string newDir);
	std::string copyFile(std::string fileName, std::string destination)
	{
		mykenrel.Set_Register0(7);
		mykenrel.Set_Register1(fileName.c_str);
		mykenrel.System_Call();
		if (mykenrel.Get_Register3() != 0)throw (101);
		FILE* myfile = (FILE*)mykenrel.Get_Register1();
		std::string fileContent;
		while (!feof(myfile))
		{
			mykenrel.Set_Register0(9);
			mykenrel.Set_Register1(myfile);

		}

	}
	std::string quit()
	{
		mykenrel.Set_Register0(0);
		mykenrel.System_Call();
		if (mykenrel.Get_Register1() != 0)
			throw mykenrel.Get_Register1();
		return "Exited program";
	}
	std::string fileContents(std::string fileName);
	std::string systemInfo()
	{
		mykenrel.Set_Register0(15); //Set Register 0 = 15
		mykenrel.System_Call(); //call SystemCall() function
		if (mykenrel.Get_Register3() != 0) //If Register3 is not 0
		{
			throw mykenrel.Get_Register3(); //throw value in Register 3
		}
		std::string result = "Date ";
		result += (char*)mykenrel.Get_Register1();
		result += "time";
		result += (char*)mykenrel.Get_Register2();
		return result; //return contents of register 1 & 2 as strings
		
	}
	std::string makeDir(std::string dirName)
	{
		std::string results;
		mykenrel.Set_Register0(3);
		mykenrel.Set_Register1(dirName.c_str);
		mykenrel.System_Call();
		if (mykenrel.Get_Register3() != 0)throw(101);
		results = dirName + " Created";
	}
	std::string deleteFile(std::string fileName);
	void output(std::string out)
	{
		for (int i = 0; i < out.length - 1; i++)
		{
			mykenrel.Set_Register0(2);
			mykenrel.Set_Register1(out[i]);
			mykenrel.System_Call();
		}
	}
	std::vector<std::string> makeToken(std::string com)
	{
		std::vector<std::string> vs;
		std::string s;
		std::istringstream is(com);
		while (!is.eof())
		{
			if (vs.size == 0)
			{
				getline(is, s, ' ');
			}
			else
			{
				getline(is, s, ';');
			}
			vs.push_back(s);
		}
		return vs;
	}

	std::string changeDir(std::string name)
	{
		mykenrel.Set_Register0(4);
		mykenrel.Set_Register1(name);
		mykenrel.changedir();
		if (mykenrel.GetRegister3() != 0)
		{
			throw mykenrel.getRegister3();
		}
		std::string result = "Moved to new directory";
		return result;

	}
	
	//Auxiliary
	std::string intToString(int x)
	{
		std::string result;
		char temp[256];
		//itoa(x,temp,10);
		//_itoa(x,temp,10);
		_itoa_s(x, temp, 255, 10);
		result = temp;
		return result;
	}

};