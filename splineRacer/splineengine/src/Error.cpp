#include "splineengine/Error.hpp"

Error::Error(const std::string& message,  const char* file, const int line)
:_message(message), _file(file), _line(line)
{};

Error::~Error() {};


const void Error::what() {
	std::cerr << "error : " << _message << ", in file "	<< _file << ", line " << _line 	<< std::endl;
};