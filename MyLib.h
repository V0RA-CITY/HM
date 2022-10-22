#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;
#undef max

namespace myLib
{
	template <typename T>
	T getUserInput(bool allowZero = false, bool allowNegative = false, bool checkAllinput = false);
	std::string getUserInputTxt();
	char getUserInputKey();
	unsigned short getUserSelectedTask(unsigned short qtyTask);

	template <typename T>
	void printArr(size_t size, T* Arr);

	void printArr(size_t size, bool NeedCnt, unsigned short* Arr);
	void printArr(size_t size, bool NeedCnt, int* Arr);
	void printArr(size_t size, bool NeedCnt, int* Arr, size_t medianPos);

	template <typename T>
	void printVect(const std::vector<T>& vec);

	string getNameFileFromUser(unsigned short indexF);
}

template <typename T>
T myLib::getUserInput(bool allowZero, bool allowNegative, bool checkAllinput)
{
	while (true)
	{
		T input;
		cin >> input;
		if (cin.fail() || (input < 0) && !allowNegative || (input == 0) && !allowZero)
		{
			cout << "Ошибка ввода, повторите ввод: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			if ((cin.peek() != cin.widen('\n')) && checkAllinput)
			{
				cout << "Ошибка ввода, повторите ввод: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return input;
			}
		}
	}
}

template<typename T>
void myLib::printArr(size_t size, T* Arr)
{
	cout << "Кол-во элементов = " << size << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << Arr[i] << ' ';
	}
	cout << endl;
}

template<typename T>
void myLib::printVect(const std::vector<T>& vec)
{
	cout << "Кол-во элементов = " << vec.size() << endl;
	for (auto i : vec)
	{
		cout << i << ' ';
	}
	cout << endl;
}