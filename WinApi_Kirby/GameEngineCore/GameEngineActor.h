#pragma once
#include "GameEngineObject.h"

// 설명 : 화면안에 존재하는 플레이어 몬스터 총알 등이 존재한다고 치고 위치가 있다면 이 녀석으로 표현
class GameEngineActor : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:

private:

};

