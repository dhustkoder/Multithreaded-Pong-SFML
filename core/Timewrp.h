#ifndef TIMEWRP_H
#define TIMEWRP_H
#include <ctime>
#include "sfe.h"
SFE_NAMESPACE
namespace clock {




class Seconds
{
	template<typename T>
	static constexpr float inClocks(const T value) noexcept {
		return static_cast<float>(CLOCKS_PER_SEC) * static_cast<float>(value);
	}

	template<typename T>
	static constexpr std::enable_if_t <std::is_arithmetic<T>::value,
		std::clock_t>
		toSeconds(const T value) noexcept
	{
		return ((inClocks(value) - static_cast<std::clock_t>(value)) > 0.5f)
			? static_cast<std::clock_t>(inClocks(value) + 1.f)
			: static_cast<std::clock_t>(inClocks(value));
	}

public:
	// constructors...
	Seconds() noexcept = default;
	
	constexpr Seconds(const float seconds) noexcept :
		m_seconds(toSeconds(seconds))
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
		m_seconds = toSeconds(seconds);
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

	struct Guard;

private:
	std::clock_t m_clock;
	Seconds m_seconds;
	bool m_isRunning;

};


struct Chrono::Guard
{
public:
		
	Guard(const Guard&) = delete;
	Guard& operator=(const Guard&) = delete;
	///////////////////////////////////////////////////
	/// \brief ChronoGuard
	/// An object of this struct makes sure that Chrono::start();
	/// is called at the end of scope for the given Chrono object 'ref'.
	//////////////////////////////////////////////////
	Guard(Chrono& ref) noexcept : m_chronoRef(ref) {}
	~Guard() { m_chronoRef.start(); }
private:
	Chrono& m_chronoRef;
	
};




}
NAMESPACE_END

#endif
