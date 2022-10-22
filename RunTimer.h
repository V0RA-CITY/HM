#pragma once
#include <chrono>
#include <iostream>


class RunTimer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::string m_name;
	std::chrono::time_point<clock_t> m_beg;
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
public:
	RunTimer() : m_beg(clock_t::now())
	{};
	RunTimer(std::string name) : m_name(name), m_beg(clock_t::now())
	{};

	void start(std::string name)
	{
		m_name = name;
		m_beg = clock_t::now();
	}
	void print() const {
		std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
	}
};
