#pragma once
#include "GameEngineObject.h"

#include <string>
#include <list>
#include <GameEngineBase/GameEngineMath.h>

// 설명 : 화면안에 존재하는 플레이어 몬스터 총알 등이 존재한다고 치고 위치가 있다면 이 녀석으로 표현
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	float4 GetPos()
	{
		return Pos;
	}

	float4 GetScale()
	{
		return Scale;
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

protected:

private:
	float4 Pos = float4::ZERO;
	float4 Scale = float4::ZERO;
	GameEngineLevel* Level = nullptr;
	std::list<GameEngineRenderer*> AllRenderer;

	void PushMainCameraRenderer(GameEngineRenderer*);
};