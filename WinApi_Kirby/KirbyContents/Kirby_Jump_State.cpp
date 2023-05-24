#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::JumpStart()
{
	ChangeAnimationState("Jump");
}

void Kirby::JumpToDownStart()
{
	ChangeAnimationState("JumpToDown");
}

void Kirby::JumpToLandStart()
{
	ChangeAnimationState("JumpToLand");
}

void Kirby::JumpUpdate(float _Delta)
{
	DirCheck();

	static float JumpTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 JumpPos = float4::UP * _Delta * JumpPower;
	float4 CheckPos = { 0.0f, -80.0f };

	float4 UpPos = GetPos() += JumpPos;

	if (UpPos.Y > 100.0f)
	{
		AddPos(JumpPos);
	}

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = { -50.0f, -80.0f };

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
		CheckPos = { 50.0f, -80.0f };

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsPress('Q') && Dir == ActorDir::Left)
	{
		MovePos = { -RunSpeed * _Delta, 0.0f };
		CheckPos = { -50.0f, -80.0f };

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (true == GameEngineInput::IsPress('E') && Dir == ActorDir::Right)
	{
		MovePos = { RunSpeed * _Delta, 0.0f };
		CheckPos = { 50.0f, -80.0f };

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (JumpTimer >= 1.0f)
	{
		JumpTimer = 0.0f;
		ChangeState(KirbyState::JumpToDown);
		return;
	}
	JumpTimer += _Delta;
}

void Kirby::JumpToDownUpdate(float _Delta)
{
	DirCheck();

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			MovePos = { -Speed * _Delta, 0.0f };
			CheckPos = { -50.0f, -30.0f };

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

		if (true == GameEngineInput::IsPress('Q') && Dir == ActorDir::Left)
		{
			MovePos = { -RunSpeed * _Delta, 0.0f };
			CheckPos = { -50.0f, -30.0f };

			unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == Color)
			{
				AddPos(MovePos);
				CameraMove(MovePos);
			}
		}

		if (true == GameEngineInput::IsPress('E') && Dir == ActorDir::Right)
		{
			MovePos = { RunSpeed * _Delta, 0.0f };
			CheckPos = { 50.0f, -30.0f };

			unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == Color)
			{
				AddPos(MovePos);
				CameraMove(MovePos);
			}
		}
	}
	else
	{
		GravityReset();
		ChangeState(KirbyState::JumpToLand);
		return;
	}
}

void Kirby::JumpToLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}
