module;
#include <chrono>

module apto.util.Time;

#define MICROSECONDS (1'000'000.0f)

namespace apto
{
	Time::Time() noexcept : 
		_stopped(false), 
		_timeScale(1.0f), 
		_deltaTime(0.0f),
		_totalGameTime(0.0f), 
		_startTime(0), 
		_baseTime(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()),
		_frameCount(0)
	{

	}

	void Time::Start() noexcept
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		_startTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
	}

	void Time::Stop() noexcept
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		_endTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
		_deltaTime = (float)(_endTime - _startTime) / MICROSECONDS;
		_totalGameTime += _deltaTime;
		++_frameCount;
	}

	void Time::Reset() noexcept
	{
		_baseTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}

	void Time::SetTimeScale(float scale) noexcept
	{
		_timeScale = scale;
	}

	float Time::GetTimeScale() const noexcept
	{
		return _timeScale;
	}
	float Time::GetDeltaTime() const noexcept
	{
		return _deltaTime * _timeScale;
	}
	float Time::GetTotalRealTime() const noexcept
	{
		return (float)(_endTime - _baseTime) / MICROSECONDS;
	}
	float Time::GetTotalGameTime() const noexcept
	{
		return _totalGameTime;
	}
	__int64 Time::GetTotalFrame() const noexcept
	{
		return _frameCount;
	}
}