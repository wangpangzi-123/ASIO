#include <iostream>
#include <string>
#include "boost/lexical_cast.hpp"

void f()
{
	static int runtime = 0;
	int a = 10;
	static void* once = [&a](void) ->void* {
		a = a + 1;
		std::puts("once");
		return NULL;
	}();
	[](auto a, auto&& b)->void {
		if (a < b)
		{
			std::cout << "a < b" << std::endl;
		}
		}(3, 3.14);
	
	std::cout << ++runtime << std::endl;
}

int main()
{
	

	f();
	f();
}