#include "Monster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Monster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Monster::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Monster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Monster::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Monster::IdleUpdate(float _Delta)
{
	DirChange(0);
}

void Monster::WalkUpdate(float _Delta)
{

}

void Monster::AttackUpdate(float _Delta)
{

}

void Monster::DamageUpdate(float _Delta)
{

}