#include <string>
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

};