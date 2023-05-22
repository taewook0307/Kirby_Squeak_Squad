#pragma once

#include "GameEngineObject.h"

#include <map>
#include <vector>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

enum class CollisionType
{
	Point,
	Rect,
	Circle,
	Max
};

class GameEngineActor;
class GameEngineCollision : public GameEngineObject
{
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	void SetCollisionScale(const float4& _Value)
	{
		CollisionScale = _Value;
	}

	void SetCollisionPos(const float4& _Value)
	{
		CollisionPos = _Value;
	}

	void SetOrder(int _Order) override;

	GameEngineActor* GetActor()
	{
		return Master;
	}

	bool Collision(int _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::Circle, CollisionType _OrderType = CollisionType::Circle);

	template<typename EnumType>
	bool Collision(EnumType _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::Circle, CollisionType _OrderType = CollisionType::Circle)
	{
		return Collision(static_cast<int>(_Order), _Result, _ThisType, _OrderType);
	}

	bool CollisionCheck(GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType);
protected:

private:
	GameEngineActor* Master = nullptr;
	float4 CollisionPos;
	float4 CollisionScale;
};

