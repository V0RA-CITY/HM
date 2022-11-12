#pragma once
#include <map>
#include <string>

std::string trimSpecialCharacters(const std::string& str)
{
	std::string ignore(" \n\t\r");
	const auto begin = str.find_first_not_of(ignore);
	const auto end = str.find_last_not_of(ignore);
	return (begin != std::string::npos) ? str.substr(begin, end - begin + 1) : std::string{};
}

std::multimap<uint32_t, std::string> lengthsOfSentences(std::string& txt)
{
	std::multimap<uint32_t, std::string> result;
	auto endTextIterator = end(txt);
	auto beginTextIterator = begin(txt);
	auto intermediateTextIterator = std::find(beginTextIterator, endTextIterator, '.');
	while (beginTextIterator != endTextIterator && std::distance(beginTextIterator, intermediateTextIterator))
	{
		std::string str = trimSpecialCharacters({ beginTextIterator, intermediateTextIterator });
		uint32_t qte = std::count(str.begin(), str.end(), ' ') + 1;
		result.insert(std::make_pair(qte, std::move(str)));
		beginTextIterator = std::next(intermediateTextIterator, 1);
		intermediateTextIterator = std::find(beginTextIterator, endTextIterator, '.');
		if (intermediateTextIterator == endTextIterator) break;
	}
	return result;
}
