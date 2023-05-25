#include "Kirby.h"

#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Kirby::DamageLandStart()
{
	ChangeAnimationState("DamageLand");
}

// 충돌 체크 후 방향지정필요
void Kirby::DamageUpdate(float _Delta)
{
	float4 FlyPos = float4::UP * FlyPower * 0.5f * _Delta;
	float4 MovePos = float4::ZERO;
	float4 XCheckPos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	unsigned int Color = 0;

	if (FlyPos.Y < 0)
	{
		CheckPos = UPCHECKPOS;
		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else
	{
		Color = GetGroundColor(EMPTYCOLOR);
	}
	

	if (EMPTYCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	if (ActorDir::Left == Dir)
	{
		MovePos = { Speed * _Delta * 0.8f, 0.0f };
		XCheckPos = LEFTMOVECHECKPOS;
	}
	else
	{
		MovePos = { -Speed * _Delta * 0.8f, 0.0f };
		XCheckPos = RIGHTMOVECHECKPOS;
	}

	AddPos(MovePos);
	CameraMove(MovePos);

	FlyPower -= 25.0f;

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::DamageLand);
		return;
	}
}

void Kirby::DamageLandUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}