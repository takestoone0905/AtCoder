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

void B(std::istream& in)
{
	int N, M, K; in >> N >> M >> K;
	std::vector<int> A(N, 0);
	for (size_t i = 0; i < K; i++)
	{
		int a, b; in >> a >> b;
		A[a - 1]++;
		if (A[a - 1] == M)
		{
			std::cout << a << " ";
		}
	}
}

int main()
{
	B(std::cin);
	return 0;
}