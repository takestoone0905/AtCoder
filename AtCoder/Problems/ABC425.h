#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <queue>

void A(std::istream& in)
{
	int n; in >> n;

	auto sum = 0;
	auto sgn = -1;
	for (size_t i = 1; i <= n; i++)
	{
		sum += sgn * i * i * i;
		sgn *= -1;
	}
	std::cout << sum << std::endl;
}

void B(std::istream& in)
{
	int n; in >> n;
	std::vector<bool> used(n, false);
	std::vector<int> rawA(n, 0);
	for (size_t i = 0; i < n; i++)
	{
		int a; in >> a;
		rawA[i] = a;
		if (a == -1) continue;
		if (used[a - 1])
		{
			// 2回以上同じ数が出たら再現不能
			std::cout << "No" << std::endl;
			return;
		}
		else
		{
			used[a - 1] = true;
		}
	}

	std::cout << "Yes" << std::endl;
	for (size_t i = 0; i < n; i++)
	{
		if (rawA[i] != -1)
		{
			std::cout << rawA[i] << " ";
			continue;
		}

		// 適当に未使用の数を割り当てる
		for (size_t j = 0; j < n; j++)
		{
			if (!used[j])
			{
				used[j] = true;
				std::cout << (j + 1) << " ";
				break;
			}
		}
	}
	std::cout << std::endl;
}

void C(std::istream& in)
{
	unsigned long long N, Q; in >> N >> Q;
	std::vector<unsigned long long> A(2 * N);

	std::vector<unsigned long long> Sum(2 * N + 1, 0);

	unsigned long long offset = 0;
	for (size_t i = 0; i < N; i++)
	{
		in >> A[i];
		A[i + N] = A[i];
	}
	for (size_t i = 1; i <= 2 * N; i++)
	{
		Sum[i] = Sum[i - 1] + A[i - 1];
	}
	for (size_t q = 0; q < Q; q++)
	{
		auto query = 0; in >> query;
		switch (query)
		{
			case 1:
			{
				unsigned long long x; in >> x;
				offset = (offset + x) % N;
				break;
			}
			case 2:
			{
				unsigned long long l, r; in >> l >> r;
				std::cout << Sum[(r + offset)] - Sum[(l + offset - 1)] << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "OFFSET = " << offset << std::endl;
				for (size_t i = 0; i < N; i++)
				{
					std::cout << "A[" << i + offset << "] = " << A[i + offset] << " ";
				}
				std::cout << std::endl;
				for (size_t i = 1; i <= N; i++)
				{
					for (size_t j = i; j <= N; j++)
					{
						std::cout << "Sum(" << i << "," << j << ") = " << Sum[j + offset] - Sum[i + offset - 1] << " ";
					}
				}
				std::cout << std::endl;
				break;
			}
		}
	}
}

int main()
{
	C(std::cin);
	return 0;
}
