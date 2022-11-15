#pragma once
#include <sstream>
#include <mutex>

std::mutex coutLock;

class pcout
{
public:
	pcout()
	{
		coutLock.lock();
	}

	~pcout()
	{
		coutLock.unlock();
	}

	template <typename T>
	pcout& operator<< (const T& t)
	{
		std::cout << t;
		return *this;
	}

	pcout& operator<< (std::ostream& (*fp)(std::ostream&))
	{
		std::cout << fp;
		return *this;
	}
};

class pcout2 : public std::stringstream
{
public:
	static inline std::mutex coutLock2;
	~pcout2()
	{
		std::lock_guard<std::mutex> lock(coutLock2);
		std::cout << rdbuf();
		std::cout.flush();
	}
};
