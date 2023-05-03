#include "GameEngineTime.h"

GameEngineTime::GameEngineTime()
{
	QueryPerformanceFrequency(&Count);
	Reset();

	// QueryPerformanceCounter(&Prev);
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

}