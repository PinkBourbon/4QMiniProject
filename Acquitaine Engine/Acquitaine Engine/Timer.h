#pragma once
/// <summary>
/// 시간을 재기 위한 클래스
/// 맴버변수로 deltaTime과 fps를 보관하다가
/// getter를 통해 알려주는 역활
/// </summary>

	class Timer
	{
	public:
		Timer();
		~Timer();

	public:
		/// <summary>
		/// Fps, Frame타임, Deltatime을 업데이트 한다.
		/// 다음에 다시 이 함수가 호출 될 때 까지가 프레임 타임의 측정 기준
		/// </summary>
		void Update();

		/// <summary>
		/// DeltaTIme을 얻어온다.
		/// </summary>
		/// <returns></returns>
		double GetDeltaTime();

		/// <summary>
		/// 프레임 타임을 얻어온다.
		/// </summary>
		/// <returns></returns>
		double GetFrameTime();

		/// <summary>
		/// timescale을 얻어온다.
		/// </summary>
		/// <returns></returns>
		double GetTimeScale();

		/// <summary>
		/// deltatime의 timescale을 설정한다.
		/// </summary>
		void SetTimeScale(double num);
		
		/// <summary>
		/// fps를 얻어온다.
		/// </summary>
		/// <returns></returns>
		double GetFps();

	private:
		double _timeScale;
		double _deltaTime;

		double _frameTime;

		double  _lastTime;
		double  _periodFrequency;

		double  _curTime;
		double _fps;
	};

