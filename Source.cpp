#include <windows.h>
#include <thread>
#include <chrono>

#include "MyLib.h"
#include "pcout.h"


void Task1()
{
	std::cout << "Работа с cout:" << std::endl << std::endl;

	const size_t countThreads = 17;

	std::vector<std::thread> threads;
	threads.reserve(countThreads);

	for (size_t i = 0; i < countThreads; i++)
	{
		threads.emplace_back([=]() {
			std::cout << "start thread " << i << " thread id: " << std::this_thread::get_id() << std::endl;
			});
	}
	for (auto& i : threads) i.join();

	std::cout << std::endl;
	std::cout << "Работа с потокобезопасным pcout:" << std::endl << std::endl;

	threads.clear();

	for (size_t i = 0; i < countThreads; i++)
	{
		threads.emplace_back([=]() {
			pcout{} << "start thread " << i << " thread id: " << std::this_thread::get_id() << std::endl;
			});
	}
	for (auto& i : threads) i.join();
	std::cout << std::endl;

	std::cout << "Работа с потокобезопасным pcout2:" << std::endl << std::endl;

	threads.clear();

	for (size_t i = 0; i < countThreads; i++)
	{
		threads.emplace_back([=]() {
			pcout2{} << "start thread " << i << " thread id: " << std::this_thread::get_id() << std::endl;
			});
	}
	for (auto& i : threads) i.join();
	std::cout << std::endl;
}

void Task2()
{
	std::cout << "Сортировка предложений по длинне: " << std::endl << std::endl;
	std::cout << "Вставьте свой текст: " << std::endl << std::endl;

}

void Task3()
{
	std::cout << "Сортировка предложений по длинне: " << std::endl << std::endl;
	std::cout << "Вставьте свой текст: " << std::endl << std::endl;

}


int main()
{
	setlocale(LC_ALL, "RU");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned short taskNumber = 0;
	while (true)
	{
		taskNumber = myLib::getUserSelectedTask(3);
		switch (taskNumber)
		{
		case 1: Task1();
			break;
		case 2: Task2();
			break;
		case 3: Task3();
			break;
		}
		std::cout << std::endl;
	}

	return 0;
}