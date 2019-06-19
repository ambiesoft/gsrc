#include <iostream>
#include <base/cpu.h>

int main()
{
	std::cout << "MYMAIN!" << std::endl;
	
	base::CPU cpu;
	std::cout << "has_sse:" << cpu.has_sse() << std::endl;
	
	return 0;
}