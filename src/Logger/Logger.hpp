#pragma once

#include <iostream>
#include <memory>
#include <fstream>

class Logger{
	std::ostream& out = std::cout;
	std::unique_ptr<std::ofstream> file = nullptr;
	unsigned indentation = 0;
	bool disabled = false;

	inline static std::unique_ptr<Logger> instance;

	constexpr static unsigned INDENTATION_SIZE = 4;

	Logger() = default;
	Logger(std::ostream& os):out(os){}
public:

	static void init(std::ostream& os);
	static void init(const std::string& filePath);

	static void disable(){log().disabled = true;}

	static Logger& log();

	template<typename T>
	constexpr inline Logger& operator<<(const T& content){
		if(disabled)
			return *this;
		if(indentation)
			out << std::string((indentation-1) * INDENTATION_SIZE,' ');
		out << content << '\n';
		return *this;
	}

	enum class Indent{ENTER,LEAVE};

	Logger& operator<<(Indent indentMarker){
		if(disabled)
			return *this;

		switch(indentMarker){
			case Indent::ENTER:
				++indentation;
				break;
			case Indent::LEAVE:
				if(indentation)
					--indentation;
				break;
		}
		return *this;
	}

	~Logger();
};