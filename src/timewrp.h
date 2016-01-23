#ifndef TIMEWRP_H
#define TIMEWRP_H
#include <ctime>

struct Seconds
{
	constexpr Seconds() noexcept : 
		m_seconds(0)
	{
	
	}

	constexpr Seconds::Seconds(float seconds)  noexcept :
		m_seconds(cexpr_div((float)CLOCKS_PER_SEC, seconds))
	{
	}
	
	Seconds& operator=(const float seconds) noexcept {
		m_seconds = cexpr_div((float)CLOCKS_PER_SEC, seconds);
	}

	constexpr operator std::clock_t() noexcept {
		return static_cast<clock_t>(m_seconds);
	}
private:
	std::clock_t m_seconds;
};



#endif