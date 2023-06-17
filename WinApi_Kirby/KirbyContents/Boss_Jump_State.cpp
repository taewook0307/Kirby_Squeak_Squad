#include "BossMonster.h"

#include <GameEngineCore/GameEngineRenderer.h>

void BossMonster::JumpReadyStart()
{
	ChangeAnimationState("JumpReady");
}

void BossMonster::JumpStart()
{
	ChangeAnimationState("Jump");
	SetGravityVector(float4::UP * BossJumpPower);
}

void BossMonster::DropStart()
{
	ChangeAnimationState("Drop");
}

void BossMonster::JumpReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Jump);
		return;
	}
}

void BossMonster::JumpUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

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

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor)
	{
		AddPos(MovePos);
	}

	if (GetGravityVector().Y > 0.0f)
	{
		ChangeState(BossState::Drop);
		return;
	}
}

void BossMonster::DropUpdate(float _Delta)
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

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor)
	{
		AddPos(MovePos);
	}
}