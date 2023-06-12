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



	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		ChangeState(BossState::MonsterSummon);
		return;
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
}