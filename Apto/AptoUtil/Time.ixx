export module apto.util.Time;


export namespace apto
{
	class __declspec(dllexport) Time
	{
	public:
		Time() noexcept;
		Time(const Time&) noexcept = default;
		Time(Time&&) noexcept = default;
		Time& operator=(const Time&) noexcept = default;
		Time& operator=(Time&&) noexcept = default;
		~Time() noexcept = default;
		void Start() noexcept;
		void Stop() noexcept;
		void Reset() noexcept;
		void SetTimeScale(float scale) noexcept;
		float GetTimeScale() const noexcept;

		float GetDeltaTime() const noexcept;
		float GetTotalRealTime() const noexcept;
		float GetTotalGameTime() const noexcept;
		__int64 GetTotalFrame() const noexcept;
	private:
		bool _stopped;
		float _timeScale;
		float _deltaTime;
		float _totalGameTime;
		__int64 _startTime;
		__int64 _endTime;
		__int64 _baseTime;
		__int64 _frameCount;
	};
}