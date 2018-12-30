#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>

#ifndef __ERROR_HPP__
#define __ERROR_HPP__

//more simple exception class available in TP8
class Error : public std::exception {

public:
	///\brief constructor
	Error(
		const std::string& message = "no exception message",
		const char* file = __FILE__,
		const int line = __LINE__
	);

	///\brief destructor
	~Error();
	/// \brief return error infos
	const void what();

private:
	std::string _message;
	std::string _file;
	int _line;

};

#endif