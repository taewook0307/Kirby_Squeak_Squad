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

void Kirby::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Kirby::IdleUpdate(float _Delta)
{
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

	if (MovePos == float4::ZERO)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	AddPos(MovePos);
}