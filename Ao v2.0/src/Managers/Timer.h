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
	private:
		typedef std::chrono::high_resolution_clock hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds;
		std::chrono::time_point<hrClock> m_Start;
	};
}