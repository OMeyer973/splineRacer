#include "splineengine/Error.hpp"

Error::Error(const std::string& message, const char* file, const int line)
	:_message(message), _file(file), _line(line)
{};

Error::~Error() {};

const char* Error::what() const noexcept {
	std::string message = "Error : " + _message + ", in file "	+ _file + ", line " + std::to_string(_line);
	std::cout << message << std::endl;
	return message.c_str();
};