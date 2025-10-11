#pragma once
#include <vector>
#include <string>
#include <iostream>

static void A(std::istream& in)
{
	std::vector<std::string> animals = { "Ocelot", "Serval", "Lynx" };
	std::string x, y;
	in >> x >> y;
	for (size_t i = 0; i < animals.size(); i++)
	{
		if (animals[i] == y) {
			std::cout << "Yes" << std::endl;
			return;
		}
		if (animals[i] == x) {
			std::cout << "No" << std::endl;
			return;
		}
	}
}

#ifndef LOCAL_TEST
int main()
{
	A(std::cin);
	return 0;
}
#endif // !LOCAL_TEST
