#include "BossMonster.h"

#include <GameEnginePlatform/GameEngineInput.h>

void BossMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void BossMonster::WalkStart()
{
	ChangeAnimationState("Walk");
}

void BossMonster::IdleUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}
}

void BossMonster::WalkUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	float4 MovePos = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}

	AddPos(MovePos);
}