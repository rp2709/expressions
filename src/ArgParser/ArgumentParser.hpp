#pragma once

#include <string>
#include <map>
#include <queue>

/*
The argument parser expects parameters to be formated by two standards:
1. --parameter value
2. -p value
The value of a parameter can then be fetched with getParamValue

If some arguments do not respect that syntaxe, it will be register as a simple argument
and can be obtained ONCE in  the order they appeared in
*/
class ArgumentParser{
	std::map<std::string,std::string> parameters;
	std::queue<std::string> arguments;

public:
	ArgumentParser(int argc, char** argv);
	const std::string& getParamValue(const std::string& parameter, const std::string& fallback = "");
	std::string getNextArg();
};