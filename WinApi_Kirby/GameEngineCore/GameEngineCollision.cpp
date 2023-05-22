#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"

#include <list>

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

void GameEngineCollision::SetOrder(int _Order)
{
	std::list<GameEngineCollision*>& PrevCollisions = Master->GetLevel()->AllCollision[GetOrder()];
	PrevCollisions.remove(this);

	GameEngineObject::SetOrder(_Order);

	std::list<GameEngineCollision*>& NextCollisions = Master->GetLevel()->AllCollision[GetOrder()];
	NextCollisions.push_back(this);
}

bool GameEngineCollision::Collision(int _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType = CollisionType::Circle, CollisionType _OrderType = CollisionType::Circle)
{
	return false;
}

bool GameEngineCollision::CollisionCheck(GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType)
{
	return false;
}