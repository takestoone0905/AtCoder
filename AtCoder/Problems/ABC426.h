#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <queue>
#include "../Lib.h"

void A(std::istream& in)
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

void B(std::istream& in)
{
	std::string s;
	in >> s;

	char a = s[0];
	if (s[1] == a)
	{
		for (size_t i = 2; i < s.length(); i++)
		{
			if (s[i] != a)
			{
				std::cout << s[i] << std::endl;
				return;
			}
		}
	}

	char b = s[1];
	std::cout << (s[2] == a ? b : a) << std::endl;
}

void C(std::istream& in)
{
	int N, Q;
	in >> N >> Q;
	std::vector<int> nodes(N, 1);
	int oldest = 1;

	// x以下のバージョンを持つ台のバージョンをyに更新する。
	// x以下のバージョンを持つ台は存在しなくなる。
	auto update = [&](int x, int y)
	{
		if (x < oldest) {
			// x以下のバージョンを持つ台は存在しない。
			return 0;
		}

		auto res = 0;
		while (oldest <= x)
		{
			auto count = nodes[oldest - 1];
			nodes[oldest - 1] = 0;
			nodes[y - 1] += count;
			res += count;
			oldest++;
		}
		return res;
	};

	for (size_t i = 0; i < Q; i++)
	{
		int x, y;
		in >> x >> y;
		auto updatedNodes = update(x, y);
		std::cout<< updatedNodes << std::endl;
	}
}

void C2(std::istream& in)
{
	int N, Q;
	in >> N >> Q;
	std::vector<int> nodes(N, 1);

	auto segTree = SegTree<int>(nodes);
	int oldest = 1;

	for (size_t i = 0; i < Q; i++)
	{
		int x, y;
		in >> x >> y;

		auto result = 0;
		{
			// oldest未満のバージョンを持つ台は存在しない。
			if (x >= oldest)
			{
				// x以下のバージョンを持つ台のバージョンをyに更新する。
				// x以下のバージョンを持つ台は存在しなくなる。
				result = segTree.getSpanSum(oldest - 1, x - 1);
				while (oldest <= x)
				{
					segTree.update(0, (oldest++) - 1);
				}
				segTree.update(segTree.getLeaf(y - 1) + result, y - 1);
			}
		}
		std::cout << result << std::endl;
	}
}


#ifndef LOCAL_TEST
int main()
{
	C2(std::cin);
	return 0;
}
#endif // !LOCAL_TEST
