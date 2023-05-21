#include "Kirby.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void Kirby::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Kirby::DownStart()
{
	ChangeAnimationState("Down");
}

void Kirby::SlideStart()
{
	ChangeAnimationState("Slide");
}

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

void Kirby::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Kirby::IdleUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	if (RGB(255, 255, 255) == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(KirbyState::Walk);
		return;
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		DirCheck();
		ChangeState(KirbyState::Down);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		DirCheck();
		ChangeState(KirbyState::Jump);
		return;
	}
}

void Kirby::DownUpdate(float _Delta)
{
	DirCheck();

	if (true == GameEngineInput::IsDown('A') && Dir == ActorDir::Left
		|| true == GameEngineInput::IsDown('D') && Dir == ActorDir::Right)
	{
		ChangeState(KirbyState::Slide);
	}

	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Down);
		return;
	}

	if (true == GameEngineInput::IsUp('S'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::SlideUpdate(float _Delta)
{
	float4 StartPos = GetPos();
	float4 MovePos = float4::ZERO;
	float CopySpeed = Speed / 1.5f;

	static float SlideTimer = 0.0f;

	if (Dir == ActorDir::Left && SlideTimer <= 1.0f)
	{
		MovePos = { -CopySpeed * _Delta, 0.0f };

		AddPos(MovePos);
		GetLevel()->GetMainCamera()->AddPos(MovePos);
		SlideTimer += _Delta;
		return;
	}

	if (Dir == ActorDir::Right && SlideTimer <= 1.0f)
	{
		MovePos = { CopySpeed * _Delta, 0.0f };

		AddPos(MovePos);
		GetLevel()->GetMainCamera()->AddPos(MovePos);
		SlideTimer += _Delta;
		return;
	}

	if (SlideTimer <= 1.2f || SlideTimer >= 1.0f)
	{
		SlideTimer += _Delta;
	}

	if (SlideTimer >= 1.2f)
	{
		SlideTimer = 0.0f;
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::JumpUpdate(float _Delta)
{
	DirCheck();

	static float JumpTimer = 0.0f;

	float4 MovePos = float4::UP * _Delta * JumpPower;

	AddPos(MovePos);

	float4 MoveXPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MoveXPos = { -Speed * _Delta, 0.0f };
		AddPos(MoveXPos);
		GetLevel()->GetMainCamera()->AddPos(MoveXPos);
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MoveXPos = { Speed * _Delta, 0.0f };
		AddPos(MoveXPos);
		GetLevel()->GetMainCamera()->AddPos(MoveXPos);
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

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	if (RGB(255, 255, 255) == Color)
	{
		Gravity(_Delta);

		float4 MovePos = float4::ZERO;

		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			MovePos = { -Speed * _Delta, 0.0f };
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}

		if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
		{
			MovePos = { Speed * _Delta, 0.0f };
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
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
	DirCheck();

	static float LandTimer = 0.0f;

	LandTimer += _Delta;

	if (LandTimer >= 0.5f)
	{
		LandTimer = 0.0f;
		ChangeState(KirbyState::Idle);
		return;
	}
}


void Kirby::WalkUpdate(float _Delta)
{
	DirCheck();
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::Jump);
		return;
	}

	if (MovePos == float4::ZERO)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	AddPos(MovePos);
}