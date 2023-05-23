#include "GameEngineActorSubObject.h"
#include "GameEngineActor.h"

GameEngineActorSubObject::GameEngineActorSubObject() 
{
}

GameEngineActorSubObject::~GameEngineActorSubObject() 
{
}


bool GameEngineActorSubObject::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}