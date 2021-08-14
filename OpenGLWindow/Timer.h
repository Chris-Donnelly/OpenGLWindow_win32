#pragma once
#include <windows.h>
#include <cstdint>

class Timer 
{
	private:

		double      mSecondsPerCount;
		double      mDeltaTime;
		uint64_t    mBaseTime;
		uint64_t    mPausedTime;
		uint64_t    mStopTime;
		uint64_t    mPrevTime;
		uint64_t    mCurrTime;
		bool        mStopped;

	public:

		Timer();
		~Timer();

		float  TotalTime()const;
		float  DeltaTime()const;
		void   Reset();  // Call before message loop.
		void   Start();  // Call when unpaused.
		void   Stop();   // Call when paused.
		void   Tick();   // Call every frame.

};

