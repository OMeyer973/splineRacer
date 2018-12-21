#pragma once
#ifndef __TESTA__HPP
#define __TESTA__HPP

#include <string>
#include <glimac/TestB.hpp>

namespace splineengine {

class TestA {
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default TestA Constructor
		TestA();
		/// \brief TestA Constructor from parameter
		TestA(std::string text);
		/// \brief TestA Destructor
		~TestA() {};

		// METHODS
		/// \brief print text from A and B
		void printAB() const;

	private:
		std::string _textA;
		glimac::TestB _testB;
};

}

#endif