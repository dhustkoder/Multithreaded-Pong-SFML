#ifndef TIMEWRP_H
#define TIMEWRP_H
#include <ctime>

struct Seconds
{
	// constructors...
	Seconds() noexcept = default;
	
	constexpr Seconds(const float seconds) noexcept :
		m_seconds(0) 
	{
		const float result = mul((float)CLOCKS_PER_SEC, seconds);
		m_seconds = static_cast<std::clock_t>(result);
		if(( result - static_cast<float>(m_seconds)) > 0.4f)
			++m_seconds;
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
		const float result = static_cast<float>(CLOCKS_PER_SEC) * seconds;
		m_seconds = result;
		if( (result - m_seconds) > 0.4f)
			++m_seconds;
		
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

};



#endif
