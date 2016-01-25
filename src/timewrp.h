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

	// implicit clock_t conversion / operators
	constexpr operator std::clock_t() const noexcept {
		return m_seconds;
	}

	template<typename T>
	std::enable_if_t<std::is_integral<T>::value, Seconds&>
	operator/(const T x) noexcept {
		m_seconds /= static_cast<std::clock_t>(x);
		return *this;
	}

private:
	std::clock_t m_seconds;

private:
	static constexpr float mul(const float x, const float y) noexcept { return x * y; }
	static constexpr std::clock_t toClock_t(float value) noexcept {
		return ((value - static_cast<std::clock_t>(value)) > 0.5f) 
					? static_cast<std::clock_t>(++value)
					: static_cast<std::clock_t>(value);
	}

};


class Chrono
{
public:
	Chrono() noexcept :
		m_clock(0),
		m_seconds(0),
		m_isRunning(false)
	{

	}

	Chrono(const Seconds timeToElapse, const bool startNow = false)  noexcept :
		m_clock((startNow ? std::clock() : 0)),
		m_seconds(timeToElapse),
		m_isRunning(startNow)
	{

	}
	
	void setTime(const Seconds newSecs) noexcept {
		m_seconds = newSecs;
	}

	bool isRunning() const noexcept {
		return m_isRunning;
	}
	
	void start() noexcept {
		m_isRunning = true;
		m_clock = std::clock();
	}


	bool finished() noexcept
	{
		if ((std::clock() - m_clock) > m_seconds)
			return ! (m_isRunning = false); // assign false to m_isRunning, and return true
		else
			return false;
	}

	struct ChronoGuard;

private:
	std::clock_t m_clock;
	Seconds m_seconds;
	bool m_isRunning;

};


struct Chrono::ChronoGuard
{
public:
		// this make sure to call start on a Chrono object at the end of scope
		ChronoGuard(Chrono& ref) noexcept : m_chronoRef(ref) {}
		~ChronoGuard() { m_chronoRef.start(); }
private:
		Chrono& m_chronoRef;
	
};

#endif
