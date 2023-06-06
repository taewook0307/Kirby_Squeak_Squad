#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Kirby::KeepIdleStart()
{
	ChangeAnimationState("KeepIdle");
}

void Kirby::KeepWalkStart()
{
	ChangeAnimationState("KeepWalk");
}

void Kirby::KeepIdleUpdate(float _Delta)
{
	BodyCollision->On();

	DirCheck();

	KirbyGravity(_Delta);

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(KirbyState::KeepWalk);
		return;
	}

	if (true == GameEngineInput::IsDown('X') && KeepType == MonsterType::Normal)
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void Kirby::KeepWalkUpdate(float _Delta)
{
	DirCheck();

	KirbyGravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 이동
	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	// 오른쪽 이동
	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTCHECKPOS;
	}

	// 이동 방향 앞에 장애물 여부 확인 후 이동
	{
		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			AddPos(MovePos);
			CameraMove(MovePos);
		}
	}

	if (MovePos == float4::ZERO)
	{
		ChangeState(KirbyState::KeepIdle);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}