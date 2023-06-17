#include "BossMonster.h"
#include "Kirby.h"

#include <GameEngineCore/GameEngineRenderer.h>

void BossMonster::FlyReadyStart()
{
	ChangeAnimationState("FlyReady");
}

void BossMonster::FlyUpStart()
{
	ChangeAnimationState("FlyUp");
	SetGravityVector(float4::UP * BossJumpPower);
}

void BossMonster::FlyStart()
{
	ChangeAnimationState("Fly");
}

void BossMonster::FlyDropStart()
{
	ChangeAnimationState("FlyDrop");
}

void BossMonster::FlyReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::FlyUp);
		return;
	}
}

void BossMonster::FlyUpUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetGravityVector().Y >= 0.0f)
	{
		ChangeState(BossState::Fly);
		return;
	}

}

void BossMonster::FlyUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == Color)
	{
		AddPos(MovePos);
	}

	float KirbyPosX = Kirby::GetMainKirby()->GetPos().X;
	float PosX = GetPos().X;
	float DistanceX = static_cast<float>(fabs(KirbyPosX - PosX));

	if (DistanceX < 30.0f)
	{
		ChangeState(BossState::FlyDrop);
		return;
	}
}

void BossMonster::FlyDropUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(BossState::Idle);
		return;
	}
}