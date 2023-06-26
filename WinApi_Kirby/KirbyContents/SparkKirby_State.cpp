#include "SparkKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void SparkKirby::AttackStart()
{
	ChangeAnimationState("Attack");
	GameEngineSound::SoundPlay("Spark.wav");
	GameEngineSound::SoundPlay("Spark_2.wav");
}

void SparkKirby::JumpUpdate(float _Delta)
{
	Kirby::JumpUpdate(_Delta);

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void SparkKirby::JumpToDropUpdate(float _Delta)
{
	Kirby::JumpToDropUpdate(_Delta);

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void SparkKirby::DropUpdate(float _Delta)
{
	Kirby::DropUpdate(_Delta);

	if (true == GameEngineInput::IsPress('C'))
	{
		ChangeState(KirbyState::Attack);
		return;   
	}
}

void SparkKirby::AttackUpdate(float _Delta)
{
	DirCheck();
	KirbyGravity(_Delta);

	AttackCollision->On();
	BodyCollision->Off();

 	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;

		if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
		{
			MovePos = { -Speed * _Delta, 0.0f };
			CheckPos = LEFTBOTCHECKPOS;
		}

		if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
		{
			MovePos = { Speed * _Delta, 0.0f };
			CheckPos = RIGHTBOTCHECKPOS;
		}

		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}

		if (true == GameEngineInput::IsUp('C'))
		{
			AttackCollision->Off();
			BodyCollision->On();

			ChangeState(KirbyState::Drop);
			return;
		}
	}
	else
	{
		if (true == GameEngineInput::IsUp('C'))
		{
			AttackCollision->Off();
			BodyCollision->On();

			if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
			{
				ChangeState(KirbyState::Walk);
				return;
			}

			ChangeState(KirbyState::AttackToIdle);
			return;
		}
	}
}