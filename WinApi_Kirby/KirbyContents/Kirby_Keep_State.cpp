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

void Kirby::KeepJumpStart()
{
	ChangeAnimationState("KeepJump");
	SetGravityVector(float4::UP * JumpPower * 0.7f);
}

void Kirby::KeepJumpToDropStart()
{
	ChangeAnimationState("KeepJumpToDrop");
}

void Kirby::KeepJumpToLandStart()
{
	ChangeAnimationState("KeepJumpToLand");
}

void Kirby::KeepDamageStart()
{
	ChangeAnimationState("KeepDamage");
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

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::KeepJump);
		return;
	}

	if (true == GameEngineInput::IsDown('C') && KeepType == MonsterType::Normal)
	{
		ChangeState(KirbyState::AttackToIdle);
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

	if (true == GameEngineInput::IsDown('C') && KeepType == MonsterType::Normal)
	{
		ChangeState(KirbyState::AttackToIdle);
		return;
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

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(KirbyState::KeepJump);
		return;
	}
}

void Kirby::KeepJumpUpdate(float _Delta)
{
	DirCheck();

	Gravity(_Delta);

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

	if (true == GameEngineInput::IsDown('C') && KeepType == MonsterType::Normal)
	{
		ChangeState(KirbyState::AttackToIdle);
		return;
	}

	if (GetGravityVector().Y > 0.0f || GetPos().Y < 100.0f)
	{
		GravityReset();
		ChangeState(KirbyState::KeepJumpToDrop);
		return;
	}
}

void Kirby::KeepJumpToDropUpdate(float _Delta)
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

		if (true == GameEngineInput::IsDown('C') && KeepType == MonsterType::Normal)
		{
			ChangeState(KirbyState::AttackToIdle);
			return;
		}
	}
	else
	{
		GravityReset();
		ChangeState(KirbyState::KeepJumpToLand);
		return;
	}
}

void Kirby::KeepJumpToLandUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::KeepIdle);
		return;
	}
}

void Kirby::KeepDamageUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::KeepIdle);
		return;
	}
}