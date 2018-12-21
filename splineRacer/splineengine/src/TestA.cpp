#include <splineengine/TestA.hpp>
#include <iostream>

namespace splineengine {
TestA::TestA()
	:_textA(""), _testB("")
{};

TestA::TestA(std::string text)
	:_textA(text), _testB(text)
{};

void TestA::printAB() const {	
	glimac::TestB testB("this is text B");
	std::cout << _textA << std::endl;
	testB.print();
	_testB.print();
}

}
