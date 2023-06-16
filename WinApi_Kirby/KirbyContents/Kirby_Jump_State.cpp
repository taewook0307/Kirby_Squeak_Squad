#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::JumpStart()
{
	ChangeAnimationState("Jump");
	SetGravityVector(float4::UP * JumpPower);
}

void Kirby::JumpToDropStart()
{
	ChangeAnimationState("JumpToDrop");
}

void Kirby::JumpToLandStart()
{
	ChangeAnimationState("JumpToLand");
}

void Kirby::JumpUpdate(float _Delta)
{
	DirCheck();

	unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		ChangeState(KirbyState::JumpToDrop);
		return;
	}
	
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::Breathe);
		return;
	}


	if (GetGravityVector().Y >= 0.0f)
	{
		GravityReset();
		ChangeState(KirbyState::JumpToDrop);
		return;
	}
}

void Kirby::JumpToDropUpdate(float _Delta)
{
	DirCheck();

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			MovePos = { -Speed * _Delta, 0.0f };
			CheckPos = LEFTBOTCHECKPOS;

			unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == Color || DOORCOLOR == Color)
			{
				AddPos(MovePos);
				CameraMove(MovePos);
			}
		}

		if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
		{
			MovePos = { Speed * _Delta, 0.0f };
			CheckPos = RIGHTBOTCHECKPOS;

			unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == Color || DOORCOLOR == Color)
			{
				AddPos(MovePos);
				CameraMove(MovePos);
			}
		}
	}
	else
	{
		GravityReset();

		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::JumpToLand);
		return;
	}
}

void Kirby::JumpToLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		ChangeState(KirbyState::Idle);
		return;
	}
}
