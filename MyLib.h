#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

#undef max

namespace myLib
{
	template <typename T>
	std::optional<T> getUserInput(std::istream& stream, bool allowZero = false, bool allowNegative = false, bool checkAllinput = false, bool needClearStream = true);
	std::string getUserInputTxt();
	char getUserInputKey();
	unsigned short getUserSelectedTask(unsigned short qtyTask);
	void clearStream(std::istream& stream);

	template <typename T>
	void printArr(size_t size, T* Arr);

	void printArr(size_t size, bool NeedCnt, unsigned short* Arr);
	void printArr(size_t size, bool NeedCnt, int* Arr);
	void printArr(size_t size, bool NeedCnt, int* Arr, size_t medianPos);

	template <typename T>
	void printVect(const std::vector<T>& vec);

	template <typename T>
	void printContainer(const T& cont);

	std::string getNameFileFromUser(unsigned short indexF);
}

template <typename T>
std::optional<T> myLib::getUserInput(std::istream& stream, bool allowZero, bool allowNegative, bool checkAllinput, bool needClearStream)
{
	while (true)
	{
		T input;
		stream >> input;
		if (stream.fail() || (input < 0) && !allowNegative || (input == 0) && !allowZero)
		{
			std::cout << "Ошибка ввода, повторите ввод: ";
			stream.clear();
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return std::nullopt;
		}
		else
		{
			if ((stream.peek() != stream.widen('\n')) && checkAllinput)
			{
				std::cout << "Ошибка ввода, повторите ввод: ";
				stream.clear();
				stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return std::nullopt;
			}
			else
			{
				if (needClearStream)
				{
					stream.clear();
					stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				return input;
			}
		}
	}
}

template<typename T>
void myLib::printArr(size_t size, T* Arr)
{
	std::cout << "Кол-во элементов = " << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << Arr[i] << ' ';
	}
	std::cout << std::endl;
}

template<typename T>
void myLib::printVect(const std::vector<T>& vec)
{
	std::cout << "Кол-во элементов = " << vec.size() << std::endl;
	for (auto i : vec)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;
}

template<typename T>
void myLib::printContainer(const T& cont)
{
	const size_t size = cont.size();
	std::for_each(cont.begin(), cont.end(),
		[count = 0, &size](const auto& i) mutable
		{
			count++;
			std::cout << i;
			if (count != size) std::cout << ", ";
		});
	std::cout << std::endl;
}