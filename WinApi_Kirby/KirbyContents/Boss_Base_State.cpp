#include "BossMonster.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

void BossMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void BossMonster::WalkStart()
{
	ChangeAnimationState("Walk");
}

void BossMonster::IdleUpdate(float _Delta)
{
	DirChange();

	static float IdleTimer = 0.0f;

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (IdleTimer > 2.0f && FLOORCOLOR == Color)
	{
		int StateNumber = 0;

		if (true == Manual)
		{
			if (true == GameEngineInput::IsPress(VK_F1))
			{
				StateNumber = 1;
			}
			else if (true == GameEngineInput::IsPress(VK_F2))
			{
				StateNumber = 2;
			}
			else if (true == GameEngineInput::IsPress(VK_F3))
			{
				StateNumber = 3;
			}
			else if (true == GameEngineInput::IsPress(VK_F4))
			{
				StateNumber = 4;
			}
			else
			{
				StateNumber = 0;
			}
		}
		else
		{
			StateNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);
		}

		IdleTimer = 0.0f;

		if (StateNumber == 0)
		{
			ChangeState(BossState::Idle);
			return;
		}
		else if (StateNumber == 1)
		{
			ChangeState(BossState::Walk);
			return;
		}
		else if (StateNumber == 2)
		{
			ChangeState(BossState::AttackReady);
			return;
		}
		else if (StateNumber == 3)
		{
			ChangeState(BossState::FlyReady);
			return;
		}
		else
		{
			ChangeState(BossState::MonsterSummonReady);
			return;
		}
	}

	IdleTimer += _Delta;
}

void BossMonster::WalkUpdate(float _Delta)
{
	static float WalkTimer = 0.0f;

	if (2.0f < WalkTimer)
	{
		ChangeState(BossState::Idle);
		return;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}
	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor)
	{
		AddPos(MovePos);
	}
	else
	{
		WalkTimer = 0.0f;
		ChangeState(BossState::Idle);
		return;
	}
	
	WalkTimer += _Delta;
}