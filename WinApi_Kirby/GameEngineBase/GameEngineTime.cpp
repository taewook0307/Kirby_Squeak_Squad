#include "GameEngineTime.h"

GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime()
{
	QueryPerformanceFrequency(&Count);
	Reset();
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Cur);
	Prev = Cur;
}

// 프레임 사이에서 실행되어야할 함수들
void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur);
	Tick = Cur.QuadPart - Prev.QuadPart;

	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart;
	FloatDelta = static_cast<float>(DoubleDelta);
}