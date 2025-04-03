#include "Logger.hpp"

#include <stdexcept>

void Logger::init(std::ostream &os){
    if(instance)
        throw std::logic_error("the logger is a singleton and can be initialized only once");
    instance.reset(new Logger(os));
}

void Logger::init(const std::string& filePath){
    //Open file and get ostream
    std::unique_ptr<std::ofstream> logFile(new std::ofstream(filePath));
    instance.reset(new Logger(*logFile));
    instance->file.reset(logFile.release());
}

Logger::~Logger(){
    out.flush();// IMPORTANT makes sure everything that was buffered is displayed even when program crashes
    if(file)
        file->close();
}

Logger& Logger::log(){
    if(not instance)
        instance.reset(new Logger());
    return *instance;
}
