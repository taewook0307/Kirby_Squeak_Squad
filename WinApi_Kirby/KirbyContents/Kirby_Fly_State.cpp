#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>

void Kirby::BreatheStart()
{
	ChangeAnimationState("Breathe");
}

void Kirby::FlyStart()
{
	ChangeAnimationState("Fly");
}

void Kirby::BreatheOutStart()
{
	ChangeAnimationState("BreatheOut");
}

void Kirby::BreatheUpdate(float _Delta)
{
	static float FlyBreatheTimer = 0.0f;

	FlyBreatheTimer += _Delta;

	if (FlyBreatheTimer >= 2.0f)
	{
		FlyBreatheTimer = 0.0f;
		ChangeState(KirbyState::Fly);
		return;
	}
}

void Kirby::FlyUpdate(float _Delta)
{
	DirCheck();

	float4 FlyPos = float4::UP * FlyPower * _Delta;
	float4 FlyCheckPos = { 0.0f, -100.0f };
	float4 DownCheckPos = { 0.0f, 0.0f };

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	unsigned int Color = FlyPos.Y < 0 ? GetGroundColor(EMPTYCOLOR, FlyCheckPos) : GetGroundColor(EMPTYCOLOR, DownCheckPos);

	if (EMPTYCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	FlyPower -= 10.0f;

	if (true == GameEngineInput::IsDown('F'))
	{
		FlyPower = BASEPOWER;
		AddPos(FlyPos);
	}

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = { 50.0f, -30.0f };

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = { 50.0f, -30.0f };

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::BreatheOut);
		return;
	}
}

void Kirby::BreatheOutUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}

	static float BreatheOutTimer = 0.0f;

	BreatheOutTimer += _Delta;

	if (BreatheOutTimer >= 0.6f)
	{
		BreatheOutTimer = 0.0f;
		ChangeState(KirbyState::Idle);
		return;
	}
}
