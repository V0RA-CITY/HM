#include <iostream>
#include <tuple>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

class Person
{
private:
	std::string surname, first_name;
	std::optional<std::string>	patronymic;

public:
	Person(const std::string& sname, const std::string& fname, const std::optional<std::string>& ptr) : surname(sname), first_name(fname), patronymic(ptr)
	{};

	std::string getSurname() const { return surname; };

	friend std::ostream& operator<< (std::ostream& out, const Person& person);
	friend bool operator< (const Person& persL, const Person& persR);
	friend bool operator== (const Person& persL, const Person& persR);
};

class PhoneNumber
{
private:
	uint16_t countryCode, cityÑode;
	std::string number;
	std::optional<uint16_t> extension;

public:
	PhoneNumber() = default;
	PhoneNumber(uint16_t couC, uint16_t citC, const std::string& num, const std::optional<uint16_t>& ext) : countryCode(couC), cityÑode(citC), number(num), extension(ext)
	{};

	friend bool operator< (const PhoneNumber& phNumL, const PhoneNumber& phNumR);
	friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& phNum);
};

class PhoneBook
{
private:
	std::vector<std::pair<Person, PhoneNumber>> record;

public:
	PhoneBook(std::ifstream& fstr);

	void SortByName();
	void SortByPhone();
	std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname);
	void ChangePhoneNumber(const Person& person, const PhoneNumber& newPhNum);

	friend std::ostream& operator<< (std::ostream& out, PhoneBook phBook);
};

class Less
{
private:
	bool sortByPhone;

public:
	Less(bool flag = false) : sortByPhone(flag)
	{};

	bool operator() (const std::pair<Person, PhoneNumber>& left, const std::pair<Person, PhoneNumber>& right)
	{
		if (left.first == right.first || sortByPhone)
			return left.second < right.second;
		else return left.first < right.first;
	}
};


std::ostream& operator<< (std::ostream& out, const Person& person)
{
	out << std::setw(12) << person.surname << " " << std::setw(9) << person.first_name << " " << std::setw(14) << person.patronymic.value_or("");
	/*if (person.patronymic.has_value())
	{
		out << " " << std::setw(14) << person.patronymic.value();
	}
	else
	{
		out << "   " << std::setw(15);
	}*/
	return out;
}

bool operator<(const Person& persL, const Person& persR)
{
	return std::tie(persL.surname, persL.first_name, persL.patronymic) < std::tie(persR.surname, persR.first_name, persR.patronymic);
	/*if (persL.surname != persR.surname)
		return persL.surname < persR.surname;
	if (persL.first_name != persR.first_name)
		return persL.first_name < persR.first_name;
	if (persL.patronymic.has_value())
	{
		if (persR.patronymic.has_value())
		{
			return persL.patronymic.value() < persR.patronymic.value();
		}
		else return false;
	}
	else return true;*/
}

bool operator==(const Person& persL, const Person& persR)
{
	return std::tie(persL.surname, persL.first_name, persL.patronymic) == std::tie(persR.surname, persR.first_name, persR.patronymic);
	/*if (persL.surname != persR.surname)
		return false;
	if (persL.first_name != persR.first_name)
		return false;
	if (!(persL.patronymic.has_value() ^ persR.patronymic.has_value()))
	{
		if (persL.patronymic.has_value()) return persL.patronymic.value() == persR.patronymic.value();
	}
	return false;*/
}

std::ostream& operator<<(std::ostream& out, const PhoneNumber& phNum)
{
	out << "+" << phNum.countryCode << "(" << phNum.cityÑode << ")" << phNum.number;
	if (phNum.extension)
		out << " " << phNum.extension.value();
	return out;
}

bool operator<(const PhoneNumber& phNumL, const PhoneNumber& phNumR)
{
	return std::tie(phNumL.countryCode, phNumL.cityÑode, phNumL.number, phNumL.extension) < std::tie(phNumR.countryCode, phNumR.cityÑode, phNumR.number, phNumR.extension);
}

PhoneBook::PhoneBook(std::ifstream& fstr)
{
	std::string surname, first_name;
	std::optional<std::string>	patronymic;
	uint16_t countryCode, cityÑode;
	std::string number;
	std::optional<std::string> ext;
	std::optional<uint16_t> extension;

	if (fstr.is_open())
	{
		while (fstr >> surname >> first_name >> patronymic.emplace() >> countryCode >> cityÑode >> number >> ext.emplace())
		{
			if (patronymic.has_value())
				if (patronymic.value() == "-")
					patronymic = std::nullopt;
			Person person(surname, first_name, patronymic);
			if (ext.has_value())
				if (ext.value() == "-")
					extension = std::nullopt;
				else
					extension.emplace() = std::stoi(ext.value());

			PhoneNumber phoneNum(countryCode, cityÑode, number, extension);

			record.push_back(std::make_pair(person, phoneNum));
		}
	}
	fstr.close();
}

void PhoneBook::SortByName()
{
	Less less;
	std::sort(record.begin(), record.end(), less);
}

void PhoneBook::SortByPhone()
{
	Less less(true);
	std::sort(record.begin(), record.end(), less);
}

std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(const std::string& surname)
{
	PhoneNumber number;
	std::string res = "";
	uint8_t count = 0;
	std::for_each(record.begin(), record.end(),
		[&](const auto& rec)
		{
			if (rec.first.getSurname() == surname)
			{
				number = rec.second;
				count++;
			}
		});
	if (count == 0) res = "not found";
	else if (count > 1) res = "found more than 1";
	return std::make_tuple(res, number);
}

void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& newPhNum)
{
	auto find_rec = std::find_if(record.begin(), record.end(),
		[&person](const auto& rec)
		{
			return rec.first == person;
		});
	if (find_rec != record.end()) find_rec->second = newPhNum;
}

std::ostream& operator<<(std::ostream& out, PhoneBook phBook)
{
	for (const auto& [person, number] : phBook.record)
	{
		out << person << std::setw(5) << number << std::endl;
	}
	return out;
}


int main()
{
	setlocale(LC_ALL, "RU");

	std::ifstream file("Source.txt");
	PhoneBook book(file);
	std::cout << book;

	std::cout << "------SortByPhone-------" << std::endl;
	book.SortByPhone();
	std::cout << book;

	std::cout << "------SortByName--------" << std::endl;
	book.SortByName();
	std::cout << book;

	std::cout << "-----GetPhoneNumber-----" << std::endl;

	// лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой 
	auto print_phone_number = [&book](const std::string& surname) {
		std::cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (std::get<0>(answer).empty())
			std::cout << std::get<1>(answer);
		else
			std::cout << std::get<0>(answer);
		std::cout << std::endl;
	};

	// вызовы лямбды
	print_phone_number("Ivanov");
	print_phone_number("Petrov");

	std::cout << "----ChangePhoneNumber----" << std::endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
		PhoneNumber{ 7, 123, "15344458", std::nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
		PhoneNumber{ 16, 465, "9155448", 13 });
	std::cout << book;

	return 0;
}