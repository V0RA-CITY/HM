#pragma once
#include <unordered_set>

template <typename Type, typename Iterator>
void printUniqueElements(const Iterator& begin, const Iterator& end)
{
	std::unordered_set<Type> elements;
	std::copy(begin, end, std::inserter(elements, elements.end()));
	std::copy(elements.begin(), elements.end(), std::ostream_iterator<Type>(std::cout, ", "));
	std::cout << std::endl;
}
