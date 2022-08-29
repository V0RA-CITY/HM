#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Pair1
{
public:
	Pair1( T f, T s)
	{
		 first = f;
		 second = s;
	};

	~Pair1(){};


	T First() const
	{
		return first;
	}

	T Second() const
	{
		return second;
	}

private:
	    T first;
	    T second;

};


template <typename N, typename U>
class Pair2
{
public:
	Pair2(N f, U s)
	{
		first = f;
		second = s;
	};

	~Pair2() {};


	N First() const
	{
		return first;
	}

	U Second() const
	{
		return second;
	}

private:
	N first;
	U second;

};

template<class T1, class T2>
class Pair
{
private:
	T1 m_first;
	T2 m_second;

public:
	Pair(T1 first, T2 second) : m_first(first), m_second(second)
	{

	}

	const T1& first() const { return m_first; }
	const T2& second() const { return m_second; }

};

template<class T>
class StringValuePair : public Pair<std::string, T>
{
public:
	StringValuePair(std::string v1, T v2) : Pair<std::string, T>(v1, v2)
	{

	}

};

int main()
{

	Pair1<int> p1(6, 9);
	cout << "Pair: " << p1.First() << ' ' << p1.Second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	cout << "Pair: " << p2.First() << ' ' << p2.Second() << '\n';





	Pair2<int, double> p4(6, 7.8);
	cout << "Pair: " << p4.First() << ' ' << p4.Second() << '\n';

	const Pair2<double, int> p5(3.4, 5);
	cout << "Pair: " << p5.First() << ' ' << p5.Second() << '\n';




	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;

}
