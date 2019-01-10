#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>

#ifndef __ERROR__HPP
#define __ERROR__HPP

///\brief Handle Exceptions
class Error : public std::exception {

public:
	///\brief Constructor
	Error(const std::string& message, const char* file, const int line);

	///\brief Destructor
	~Error();
	/// \brief return error infos
	const char* what() const noexcept;

private:
	std::string _message;
	std::string _file;
	int _line;

};

#endif