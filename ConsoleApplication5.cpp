#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "MyLib.h"
#include <optional>
#include <list>


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

class Matrix
{
public:
	Matrix(std::istream& stream);

	void printMatrix();
	void printAnswer();

protected:
	Matrix(const Matrix& prevMatrix, const size_t& expansion_string_element_index);
	void calculate();

private:
	std::vector<std::vector<int32_t>> matrix;
	size_t size;
	std::optional<int64_t> determinant;
	std::vector<Matrix> minors;
};

Matrix::Matrix(const Matrix& prevMatrix, const size_t& expansion_string_element_index) : determinant(std::nullopt), size(prevMatrix.size - 1)
{
	matrix.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		matrix.push_back(std::vector<int32_t>());
		matrix[i].reserve(size);
		for (size_t j = 0; j < prevMatrix.size; j++)
		{
			if (expansion_string_element_index != j) matrix[i].push_back(prevMatrix.matrix[i + 1][j]);
		}
	}
	calculate();
}

void Matrix::calculate()
{
	switch (size)
	{
	case 1:
		determinant = matrix[0][0];
		break;
	case 2:
		determinant = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		break;
	default:
		minors.reserve(size);
		determinant = 0;
		for (size_t i = 0; i < size; i++)
		{
			minors.push_back(Matrix(*this, i));
			determinant.emplace() = determinant.value() + matrix[0][i] * minors[i].determinant.value() * (i % 2 == 0 ? 1 : (-1));
		}
		break;
	}
}

Matrix::Matrix(std::istream& stream) : determinant(std::nullopt)
{
	std::cout << "Введите размер матрицы: ";
	size = myLib::getUserInput<int32_t>(std::cin).value_or(0);

	matrix.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		matrix.push_back(std::vector<int32_t>());
		matrix[i].reserve(size);
		for (size_t j = 0; j < size; j++)
		{
			std::optional a = myLib::getUserInput<int32_t>(stream, true, true, false, false);
			if (a) matrix[i].push_back(a.value());
			else
			{
				std::cout << std::endl;
				for (size_t ii = 0; ii <= i; ii++)
				{
					for (size_t jj = 0; jj < ((ii < i) ? size : j); jj++)
					{
						std::cout << std::setw(3) << matrix[ii][jj] << std::setw(2) << "";
					}
					if (ii < i) std::cout << std::endl;
				}
				j--;
			}
		}
	}
	myLib::clearStream(stream);
	calculate();
}

void Matrix::printMatrix()
{
	for (const auto& i : matrix)
	{
		for (const auto& j : i)
		{
			std::cout << std::setw(3) << j << std::setw(2) << "";
		}
		std::cout << std::endl;
	}
}

void Matrix::printAnswer()
{
	if (determinant) std::cout << "Определитель матрицы = " << determinant.value();
	else std::cout << "Определитель не найден";
	std::cout << std::endl;
}


template<typename T>
class RangeIterator sealed
{
public:
	typedef T RangeType;
	typedef RangeIterator<RangeType> SelfType;
	typedef typename RangeType::ValueType ValueType;

private:
	const RangeType* const m_range;
	ValueType m_value;

public:
	RangeIterator(const RangeType* const range, ValueType startValue)
		: m_range(range), m_value(startValue)
	{};

	operator ValueType() const
	{
		return m_value;
	}
	ValueType operator*() const
	{
		return m_value;
	}
	SelfType& operator++()
	{
		m_value += m_range->step();
		return *this;
	}
	SelfType operator++(int)
	{
		SelfType tempIt(*this);
		++(*this);
		return tempIt;
	}
	bool operator!= (const SelfType& right)
	{
		return !(*this == right);
	}
};

template <typename T>
class Range
{
private:
	T m_min, m_max, m_step;

public:
	typedef size_t SizeType;
	typedef T ValueType;
	typedef T RangeType;

	Range(T min, T max, T step = T(1))
		: m_min(min), m_max(max), m_step(step)
	{};

	ValueType operator[](RangeType& i) const
	{
		return (m_min + (i * m_step));
	}
	SizeType size()
	{
		return static_cast<SizeType>((m_max - m_min) / m_step);
	}
	ValueType step() const
	{
		return m_step;
	}
	RangeIterator<Range<T>> begin()
	{
		return RangeIterator<Range<T>>(this, m_min);
	}
	RangeIterator<Range<T>> end()
	{
		return RangeIterator<Range<T>>(this, m_min + size() * m_step);
	}
};

template <typename T>
void push_back_average(std::list<T>& lst)
{
	T average = 0;
	for (const auto& elem : lst)
	{
		average += elem;
	}
	lst.push_back(average / static_cast<T>(lst.size()));
}

void Task1()
{
	std::cout << "Работа с Функцией push_back_average:" << std::endl << std::endl;
	std::list<float_t> myList{ 1.1f, 4.3f, 3.f, 4.f, 5.f, 6.5f, 3.2f, 8.3f, 9.f };
	push_back_average(myList);
	for (const auto& i : myList)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void Task2()
{
	std::cout << "Работа с Классом Matrix:" << std::endl << std::endl;
	Matrix mtrx(std::cin);
	std::cout << std::endl;
	mtrx.printMatrix();
	mtrx.printAnswer();
}


void Task3()
{
	std::cout << "Работа с Классом Range:" << std::endl << std::endl;
	for (const auto& i : Range<int32_t>(10, 20))
		std::cout << i << " ";
	std::cout << std::endl;
	for (const auto& i : Range<float_t>(5, 15, 0.5f))
		std::cout << i << " ";
	std::cout << std::endl;
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