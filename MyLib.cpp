#include"MyLib.h"

namespace myLib
{
	std::string getUserInputTxt()
	{
		while (true)
		{
			std::string input;
			std::cin >> input;
			if (std::cin.fail())
			{
				std::cout << "Ошибка ввода, повторите ввод: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return input;
			}
		}
	}

	char getUserInputKey()
	{
		char c;
		std::cin.get(c);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return c;
	}

	unsigned short getUserSelectedTask(unsigned short qtyTask)
	{
		unsigned short taskNumber = 0;
		std::cin.clear();
		do
		{
			std::cout << "Введите номер задачи от 1 до " << qtyTask << ":" << std::endl;
			taskNumber = getUserInput<int>(std::cin, false).value_or(0);
		} while (taskNumber > qtyTask || taskNumber < 1);

		std::cout << std::endl;

		return taskNumber;
	}

	void clearStream(std::istream& stream)
	{
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	void printArr(size_t size, bool NeedCnt, unsigned short* Arr)
	{
		if (NeedCnt) std::cout << "Кол-во элементов = " << size << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			std::cout << Arr[i] << ' ';
		}
		std::cout << std::endl;
	}

	void printArr(size_t size, bool NeedCnt, int* Arr)
	{
		if (NeedCnt) std::cout << "Кол-во элементов = " << size << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			std::cout << Arr[i] << ' ';
		}
		std::cout << std::endl;
	}

	void printArr(size_t size, bool NeedCnt, int* Arr, size_t medianPos)
	{
		if (NeedCnt) std::cout << "Кол-во элементов = " << size << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			if (medianPos > 0 && medianPos == i) std::cout << "|| ";
			std::cout << Arr[i] << ' ';
		}
		std::cout << std::endl;
	}

	std::string getNameFileFromUser(unsigned short indexF)
	{
		std::cout << "Введите имя";
		switch (indexF)
		{
		case 0:
			break;
		case 100:
			std::cout << " Конечного";
			break;
		default:
			std::cout << " " << indexF << "го";
			break;
		}
		std::cout << " файла(без расширения): ";
		std::string s;
		std::cin >> s;

		return s;
	}
}