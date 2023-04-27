#pragma once
#include "GameEngineObject.h"

// 설명 : 화면혹은 장면을 표현
// 타이틀 장면
// 플레이 장면
// 엔딩 장면
class GameEngineLevel : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};

