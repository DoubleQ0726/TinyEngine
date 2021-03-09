#pragma once

namespace TinyEngine
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{

		}
		operator float() { return m_Time; }
		float GetSeconds() const { return m_Time; }
		float GetMillisecond() const { return m_Time * 1000; }

	private:
		float m_Time;
	};
}