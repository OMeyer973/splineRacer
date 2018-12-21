#pragma once
#ifndef __TESTB__HPP
#define __TESTB__HPP

#include <string>
#include <glimac/TestB.hpp>

namespace glimac {

class TestB {
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default TestB Constructor
		TestB();
		/// \brief TestB Constructor from parameter
		TestB(std::string text);
		/// \brief TestB Destructor
		~TestB() {};

		// METHODS
		/// \brief print text from B
		void print() const;

	private:
		std::string _textB;
};

}

#endif