#include <glimac/TestB.hpp>
#include <iostream>

namespace glimac {
TestB::TestB()
	:_textB("")
{};

TestB::TestB(std::string text)
	:_textB(text)
{};

void TestB::print() const {
	std::cout << _textB << std::endl;
}

}
