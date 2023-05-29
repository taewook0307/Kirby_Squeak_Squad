#include "Monster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Monster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Monster::WalkStart()
{
	ChangeAnimationState("Walk");
}

void Monster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Monster::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Monster::IdleUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}

	static float IdleTimer = 0.0f;

	if (IdleTimer > 3.0f)
	{
		IdleTimer = 0.0f;
		ChangeState(MonsterState::Walk);
		return;
	}

	if (true == BodyCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Damage);
		return;
	}

	IdleTimer += _Delta;
}

void Monster::WalkUpdate(float _Delta)
{
	static float MoveTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 이동
	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTMOVECHECKPOS;
	}

	// 오른쪽 이동
	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTMOVECHECKPOS;
	}

	// 이동 방향 앞에 장애물 여부 확인 후 이동
	{
		unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

		if (EMPTYCOLOR == Color)
		{
			AddPos(MovePos);
		}
		else
		{
			DirChange();
		}
	}

	// 이동하지 않을 시 대기 상태 이동
	if (MoveTimer >= 5.0f)
	{
		MoveTimer = 0.0f;
		ChangeState(MonsterState::Idle);
		return;
	}

	Col.reserve(Col.size() + 1);

	if (true == BodyCollision->Collision(CollisionOrder::Attack, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Damage);
		return;
	}

	MoveTimer += _Delta;
}

void Monster::AttackUpdate(float _Delta)
{
	BodyCollision->Off();
}

void Monster::DamageUpdate(float _Delta)
{
	if (true == BodyCollision->Collision(CollisionOrder::Attack, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* CurPlayerCollision = Col[Col.size() - 1];

		GameEngineActor* CurPlayer = CurPlayerCollision->GetActor();

		float Check = CurPlayer->GetPos().X;

		if (Check < GetPos().X - 40.0f)
		{
			ChangeState(MonsterState::Attack);
			return;
		}
	}

	else
	{
		ChangeState(MonsterState::Idle);
		return;
	}
}