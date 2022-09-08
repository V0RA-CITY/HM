#include <iostream>
#include<string>
#include<ostream>

template<typename T>
T div(T value1, T value2)
{

	if (value2 == 0) { throw "DivisionByZero"; };
	return value1 / value2;
}

class Ex
{
public:
	Ex(double temp);
	~Ex();

	double what() const noexcept { return x; };

private:
	double x;
};

Ex::Ex(double temp) 
{
	x = temp;
}

Ex::~Ex()
{
}

class Bar
{
public:
	Bar();
	~Bar();

	void set(double a)
	{
		if (y + a > 100)
		{
			throw Ex(a * y);
		}
		else
		{
			y = a;
		}
	}

private:
	double y;
};

Bar::Bar()
{
	y = 0;
}

Bar::~Bar()
{
}

int main()
{
	try
	{
		std::cout << div<double>(5, 2) << std::endl;
	}
	catch (const char* ex)
	{
		std::cout << "Error DivisionByZero" << std::endl;
	}

	Bar test;
	try
	{
		double temp;
		do
		{
			std::cin >> temp;
			test.set(temp);
		} while (temp != 0);
	}
	catch (const Ex& xe)
	{
		std::cout << "Error Ex with parameters :" << "(" << xe.what() << ")" << std::endl;
	}

}

