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
			result += (char)mykenrel.Get_Register1();
		} while (temp != 0);
	}
	std::string transducer(std::string command);
	void output(std::string);

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

};