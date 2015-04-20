#include <string>
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
	std::string CommandInput()
	{
		std::string result;
		char temp;
		do
		{

		}
	}
	std::string transducer(std::string command);
	void output(std::string);

};