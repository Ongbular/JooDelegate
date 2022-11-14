
#include "TestMultiCastDelegate.h"
#include "TestUniCastDelegate.h"

int main()
{
	std::cout << std::endl << "----------Test Uni Cast Delegate----------" << std::endl;
	TestUniCastDelegate();
	std::cout << std::endl << "---------Test Multi Cast Delegate---------" << std::endl;
	TestMultiCastDelegate();
	return 0;
}
