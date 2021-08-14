#include "Timer.h"
#include <cmath>

Timer::Timer() : mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false) 
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

Timer::~Timer() 
{
}

float Timer::TotalTime()const 
{
	return static_cast<float>(mStopped ? ((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount: ((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
}

float Timer::DeltaTime()const 
{
	return static_cast<float>(mDeltaTime);
}

void Timer::Reset() 
{
	__int64 currTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
	mBaseTime  = currTime;
	mPrevTime  = currTime;
	mStopTime  = 0;
	mStopped   = false;
}

void Timer::Start() 
{
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);
		mPrevTime   = startTime;
		mStopTime   = 0;
		mStopped    = false;
	}
}

void Timer::Stop() 
{
	if (!mStopped) 	
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mStopTime  = currTime;
		mStopped   = true;
	}
}

void Timer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime   = currTime;
	mDeltaTime  = (mCurrTime - mPrevTime) * mSecondsPerCount;
	mPrevTime   = mCurrTime;

	// Force nonnegative: CPU Power states can shift code across cores,
	// which can cause negative values
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = std::fabs(mDeltaTime);
	}
}

