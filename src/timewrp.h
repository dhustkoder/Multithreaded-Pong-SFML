#ifndef TIMEWRP_H
#define TIMEWRP_H
#include <ctime>

struct Seconds
{
	// constructors...
	Seconds() noexcept = default;
	
	constexpr Seconds(const float seconds) noexcept :
		m_seconds(toClock_t(mul((float)CLOCKS_PER_SEC, seconds))) 
	{
		
	}
	
	constexpr Seconds(const Seconds& rhs) noexcept :
		m_seconds(rhs.m_seconds)
	{
	}

	// assignments
	Seconds& operator=(const Seconds& rhs) noexcept {
		m_seconds = rhs.m_seconds;
		return *this;
	}
	
	Seconds& operator=(const float seconds) noexcept {
		m_seconds = toClock_t(mul((float)CLOCKS_PER_SEC, seconds));
		return *this;
	}

	// implicit clock_t conversion
	constexpr operator std::clock_t() const noexcept {
		return m_seconds;
	}
private:
	std::clock_t m_seconds;

private:
	constexpr static float mul(const float x, const float y) noexcept { return x * y; }
	constexpr static std::clock_t toClock_t(float value) noexcept {
		return ((value - static_cast<std::clock_t>(value)) > 0.4f) 
					? static_cast<std::clock_t>(++value)
					: static_cast<std::clock_t>(value);
	}

};



#endif
