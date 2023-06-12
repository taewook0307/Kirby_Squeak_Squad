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
	return true == GameEngineObject::IsDeath() || true == Master->IsDeath();
}

bool GameEngineActorSubObject::IsUpdate()
{
	return true == GameEngineObject::IsUpdate() && true == Master->IsUpdate();
}

