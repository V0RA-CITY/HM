#include"MyLib.h"

namespace myLib
{
	std::string getUserInputTxt()
	{
		while (true)
		{
			std::string input;
			cin >> input;
			if (cin.fail())
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

	char getUserInputKey()
	{
		char c;
		cin.get(c);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return c;
	}

	unsigned short getUserSelectedTask(unsigned short qtyTask)
	{
		unsigned short taskNumber = 0;
		do
		{
			cout << "Введите номер задачи от 1 до " << qtyTask << ":" << endl;
			taskNumber = getUserInput<int>(false);
		} while (taskNumber > qtyTask || taskNumber < 1);

		cout << endl;

		return taskNumber;
	}

	void printArr(size_t size, bool NeedCnt, unsigned short* Arr)
	{
		if (NeedCnt) cout << "Кол-во элементов = " << size << endl;
		for (size_t i = 0; i < size; i++)
		{
			cout << Arr[i] << ' ';
		}
		cout << endl;
	}

	void printArr(size_t size, bool NeedCnt, int* Arr)
	{
		if (NeedCnt) cout << "Кол-во элементов = " << size << endl;
		for (size_t i = 0; i < size; i++)
		{
			cout << Arr[i] << ' ';
		}
		cout << endl;
	}

	void printArr(size_t size, bool NeedCnt, int* Arr, size_t medianPos)
	{
		if (NeedCnt) cout << "Кол-во элементов = " << size << endl;
		for (size_t i = 0; i < size; i++)
		{
			if (medianPos > 0 && medianPos == i) cout << "|| ";
			cout << Arr[i] << ' ';
		}
		cout << endl;
	}

	string getNameFileFromUser(unsigned short indexF)
	{
		cout << "Введите имя";
		switch (indexF)
		{
		case 0:
			break;
		case 100:
			cout << " Конечного";
			break;
		default:
			cout << " " << indexF << "го";
			break;
		}
		cout << " файла(без расширения): ";
		string s;
		cin >> s;

		return s;
	}
}