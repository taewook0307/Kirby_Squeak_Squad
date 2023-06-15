#include "BossMonster.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>

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

	if (IdleTimer > 2.0f)
	{
		int StateNumber = GameEngineRandom::MainRandom.RandomInt(0, 1);

		IdleTimer = 0.0f;

		if (StateNumber == 0)
		{
			ChangeState(BossState::JumpReady);
			return;
		}
		else
		{
			ChangeState(BossState::Walk);
			return;
		}
	}

	if (true == SearchCollision->Collision(CollisionOrder::Body, BossCol, CollisionType::Rect, CollisionType::Rect))
	{
		int AttackStateNumber = GameEngineRandom::MainRandom.RandomInt(0, 1);

		IdleTimer = 0.0f;

		if (AttackStateNumber == 0)
		{
			ChangeState(BossState::AttackReady);
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

	if (true == SearchCollision->Collision(CollisionOrder::Body, BossCol, CollisionType::Rect, CollisionType::Rect))
	{
		int AttackStateNumber = GameEngineRandom::MainRandom.RandomInt(0, 1);

		WalkTimer = 0.0f;

		if (AttackStateNumber == 0)
		{
			ChangeState(BossState::AttackReady);
			return;
		}
		else
		{
			ChangeState(BossState::MonsterSummonReady);
			return;
		}
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
	
	WalkTimer += _Delta;
}