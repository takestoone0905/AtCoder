#pragma once
#include <vector>
#include <string>
#include <iostream>

void A(std::istream& in)
{
	int a, b; in >> a >> b;
	if (a == b)
	{
		std::cout << "Yes" << std::endl;
		return;
	}

	int c; in >> c;

	if (a == c || b == c)
	{
		std::cout << "Yes" << std::endl;
		return;
	}
	std::cout << "No" << std::endl;
}

int main()
{
	A(std::cin);
	return 0;
}