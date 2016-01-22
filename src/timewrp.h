#ifndef TIMEWRP_H
#define TIMEWRP_H
#include <ctime>

struct Seconds
{
	Seconds() = default;
	constexpr Seconds::Seconds(float seconds)  noexcept :
	m_seconds(cexpr_div((float)CLOCKS_PER_SEC, seconds))
	{
	}
	operator std::clock_t() {
		return static_cast<clock_t>(m_seconds);
	}
private:
	std::clock_t m_seconds;
};



#endif