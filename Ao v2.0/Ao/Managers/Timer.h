#pragma once

#include <chrono>

namespace ao
{
	class Timer
	{
	public:
		Timer()
		{
			reset();
		}

		void reset()
		{
			m_Start = hrClock::now();
		}

		float elapsed()
		{
			return std::chrono::duration_cast<milliseconds>(hrClock::now() - m_Start).count() / 1000.0f;
		}

		static unsigned long getTime()
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>
				(std::chrono::system_clock::now().time_since_epoch()).count();
		}

		static unsigned long getMicroTime()
		{
			return std::chrono::duration_cast<std::chrono::microseconds>
				(std::chrono::system_clock::now().time_since_epoch()).count();
		}
	private:
		typedef std::chrono::high_resolution_clock hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds;
		std::chrono::time_point<hrClock> m_Start;
	};
}