#include "GameEngineTime.h"

#include <Windows.h>

GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime()
{
	// Count = 1초당 누른 횟수
	QueryPerformanceFrequency(&Count);
	Reset();
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	// Prev = 컴퓨터가 실행된 후 지금까지 누른 횟수
	QueryPerformanceCounter(&Cur);
	Prev = Cur;
}

// 프레임 사이에서 실행되어야할 함수들
void GameEngineTime::Update()
{
	// Cur = 실행될 때 누른 횟수
	QueryPerformanceCounter(&Cur);

	// Cur - Prev = (Update가 실행될 때까지의 누른 횟수) - (Reset이 실행되기 전까지 누른 횟수)
	Tick = Cur.QuadPart - Prev.QuadPart;

	// 한 프레임이 실행되는 사이에 누른 횟수 / 1초당 누른 횟수
	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart;
	FloatDelta = static_cast<float>(DoubleDelta);
}