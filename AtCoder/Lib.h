#pragma once
#include <vector>
#include <string>
#include <iostream>

#pragma region SegTree

template<typename T>
struct SegTree
{
	SegTree(const std::vector<T>& values)
	{
		auto n = values.size();
		leafCount = powerOf2(n);
		nodes = std::vector<T>(2 * leafCount - 1, (T)0);

		// ボトムアップに構築
		// 葉要素。完全二分木にするため要素数を2の冪に拡張して0埋め
		for (size_t i = 0; i < leafCount; i++)
		{
			nodes[leafCount + i - 1] = i < values.size() ? values[i] : 0;
		}
		// 内部ノード。子要素の和で作る
		for (int i = leafCount - 2; i >= 0; i--)
		{
			nodes[i] = nodes[i * 2 + 1] + nodes[i * 2 + 2];
		}
	}
	// idx番目の葉要素をnewValueに更新する
	void update(int newValue, int idx)
	{
		auto nodeIdx = getNodeIndex(idx);
		auto diff = newValue - nodes[nodeIdx];
		while (true)
		{
			nodes[nodeIdx] += diff;
			if (nodeIdx == 0) break;
			nodeIdx = (nodeIdx - 1) / 2;
		}
	}
	// [left,right]の和を求める
	// left葉要素とright葉要素が親に向かって辿り、合流するところで和が求まる
	T getSpanSum(int left, int right)const
	{
		auto l = getNodeIndex(left);
		auto r = getNodeIndex(right);
		if (l == r) return nodes.at(l);
		T result = 0;
		while (l < r) // leftとrightが合流する（l==r)または下の水平移動の処理でleftとrightが交差する（l>r)まで繰り返す
		{
			// leftが親から見て右の子である場合はその値を足しておいて、スパンを1つ右に縮める
			if (l % 2 == 0) result += nodes.at(l++);
			// rightが親から見て左の子である場合はその値を足しておいて、スパンを1つ左に縮める
			if (r % 2 == 1) result += nodes.at(r--);

			// 親に向かって移動
			l = (l - 1) / 2;
			r = (r - 1) / 2;

			if (l == r) // 合流したらそこを足して終わり。
			{
				result += nodes.at(l);
				break;
			}
		}
		return result;
	}
	T getLeaf(int idx) const { return nodes.at(getNodeIndex(idx)); }
private:
	static int powerOf2(int v)
	{
		auto pv = 1;
		while (pv < v)
		{
			pv <<= 1;
		}
		return pv;
	}
	int getNodeIndex(int idx) const { return leafCount + idx - 1; }
	std::vector<T> nodes;
	int leafCount;
};

#pragma endregion

