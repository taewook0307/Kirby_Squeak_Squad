#include "TornadoKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void TornadoKirby::AttackReadyStart()
{
	Kirby::AttackReadyStart();
	unsigned int CheckColor = GetGroundColor(EMPTYCOLOR);

	while (FLOORCOLOR == CheckColor)
	{
		AddPos(float4::UP);
		CheckColor = GetGroundColor(EMPTYCOLOR);
	}
	GameEngineSound::SoundPlay("TornadoStart.wav");
	GameEngineSound::SoundPlay("Tornado.wav");
}

void TornadoKirby::AttackStart()
{
	ChangeAnimationState("Attack");
	unsigned int CheckColor = GetGroundColor(EMPTYCOLOR);

	while (FLOORCOLOR == CheckColor)
	{
		AddPos(float4::UP);
		CheckColor = GetGroundColor(EMPTYCOLOR);
	}
	AttackSound = GameEngineSound::SoundPlay("Tornado.wav", 100);
}

void TornadoKirby::JumpUpdate(float _Delta)
{
	Kirby::JumpUpdate(_Delta);

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void TornadoKirby::JumpToDropUpdate(float _Delta)
{
	Kirby::JumpToDropUpdate(_Delta);

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void TornadoKirby::DropUpdate(float _Delta)
{
	Kirby::DropUpdate(_Delta);

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void TornadoKirby::AttackUpdate(float _Delta)
{
	DirCheck();

	AttackCollision->On();
	BodyCollision->Off();

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos += { -Speed * SPEEDUPVALUE * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos += { Speed * SPEEDUPVALUE * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos += { 0.0f, -Speed * SPEEDUPVALUE * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos += { 0.0f, Speed * SPEEDUPVALUE * _Delta };
	}
	
	float4 CheckPos = GetPos() + MovePos;

	unsigned int Color = GetGroundColor(EMPTYCOLOR, MovePos);

	if (Color == EMPTYCOLOR && CheckPos.Y > 100.0f)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}

	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->Off();
		BodyCollision->On();
		AttackSound.Stop();
		ChangeState(KirbyState::AttackToIdle);
		return;
	}
}

void TornadoKirby::AttackToIdleUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (true == MainRenderer->IsAnimationEnd())
	{
		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			Gravity(_Delta);

			float4 MovePos = float4::ZERO;
			float4 CheckPos = float4::ZERO;

			if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
			{
				MovePos = float4::LEFT * Speed * _Delta;
				CheckPos = LEFTBOTCHECKPOS;
			}
			else if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
			{
				MovePos = float4::RIGHT * Speed * _Delta;
				CheckPos = RIGHTBOTCHECKPOS;
			}

			unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

			if (EMPTYCOLOR == Color || DOORCOLOR == Color)
			{
				AddPos(MovePos);
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

			ChangeState(KirbyState::Idle);
			return;
		}
	}
}