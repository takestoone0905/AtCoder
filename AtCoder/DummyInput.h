#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <string_view>
namespace AtCoder::Debug
{
	class DummyInputBuffer : public std::streambuf
	{
	public:
		DummyInputBuffer()
			: mBuffer(1024)
		{
			setg(&mBuffer[0], &mBuffer[0], mBuffer.data() + mBuffer.size());
		}

		void push_bool(bool value) { value ? write("1") : write("0"); }
		void push(char value) { write(std::string_view(&value, 1)); }
		void push(int value) { write(std::to_string(value)); }
		void push(unsigned int value) { write(std::to_string(value)); }
		void push(float value) { write(std::to_string(value)); }
		void push(std::string_view value) { write(value); }
	private:
		void write(std::string_view str)
		{
			auto size = str.size() + 1;
			if (mCurrentPos + size > mBuffer.size())
			{
				mBuffer.resize((mBuffer.size() + size) * 2);
				setg(&mBuffer[0], &mBuffer[mCurrentPos], mBuffer.data() + mBuffer.size());
			}
			std::memcpy(mBuffer.data() + mCurrentPos, str.data(), size);
			mBuffer[mCurrentPos + str.size()] = ' ';
			mCurrentPos += size;
		}

		std::vector<char> mBuffer;
		size_t mCurrentPos = 0;
	};

#define MAKE_DUMMY_INPUT(in, str) auto __buf__ = AtCoder::Debug::DummyInputBuffer(); __buf__.push(str); std::istream in(&__buf__);
}
