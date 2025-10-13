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

		// �{�g���A�b�v�ɍ\�z
		// �t�v�f�B���S�񕪖؂ɂ��邽�ߗv�f����2�̙p�Ɋg������0����
		for (size_t i = 0; i < leafCount; i++)
		{
			nodes[leafCount + i - 1] = i < values.size() ? values[i] : 0;
		}
		// �����m�[�h�B�q�v�f�̘a�ō��
		for (int i = leafCount - 2; i >= 0; i--)
		{
			nodes[i] = nodes[i * 2 + 1] + nodes[i * 2 + 2];
		}
	}
	// idx�Ԗڂ̗t�v�f��newValue�ɍX�V����
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
	// [left,right]�̘a�����߂�
	// left�t�v�f��right�t�v�f���e�Ɍ������ĒH��A��������Ƃ���Řa�����܂�
	T getSpanSum(int left, int right)const
	{
		auto l = getNodeIndex(left);
		auto r = getNodeIndex(right);
		if (l == r) return nodes.at(l);
		T result = 0;
		while (l < r) // left��right����������il==r)�܂��͉��̐����ړ��̏�����left��right����������il>r)�܂ŌJ��Ԃ�
		{
			// left���e���猩�ĉE�̎q�ł���ꍇ�͂��̒l�𑫂��Ă����āA�X�p����1�E�ɏk�߂�
			if (l % 2 == 0) result += nodes.at(l++);
			// right���e���猩�č��̎q�ł���ꍇ�͂��̒l�𑫂��Ă����āA�X�p����1���ɏk�߂�
			if (r % 2 == 1) result += nodes.at(r--);

			// �e�Ɍ������Ĉړ�
			l = (l - 1) / 2;
			r = (r - 1) / 2;

			if (l == r) // ���������炻���𑫂��ďI���B
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

