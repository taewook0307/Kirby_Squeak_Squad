#include "GameEngineTime.h"

#include <Windows.h>

GameEngineTime::GameEngineTime()
{
	QueryPerformanceFrequency(&Count);
	QueryPerformanceCounter(&Cur);

	// QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}