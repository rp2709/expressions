#include "ArgumentParser.hpp"

ArgumentParser::ArgumentParser(int argc, char** argv){
    for(int i = 0; i < argc; ++i){
        char* argi = argv[i];
        if(argi[0] != '-'){
            arguments.emplace(argi);
            continue;
        }
        bool secondHyphen = argi[1] == '-';
        parameters.emplace(argi + (1 + secondHyphen),argv[++i]);
    }
}

const std::string& ArgumentParser::getParamValue(const std::string& parameter, const std::string& fallback){
    if(parameters.contains(parameter))
        return parameters[parameter];
    return fallback;
}

std::string ArgumentParser::getNextArg(){
    std::string arg(std::move(arguments.front()));
    arguments.pop();
    return arg;
}
