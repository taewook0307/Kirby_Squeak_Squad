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

void Monster::InhaleStart()
{
	ChangeAnimationState("Inhale");
}

void Monster::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Monster::DeathStart()
{
	ChangeAnimationState("Death");
}

void Monster::IdleUpdate(float _Delta)
{
	DamageMove();

	BodyCollision->On();

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
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

	IdleTimer += _Delta;
}

void Monster::WalkUpdate(float _Delta)
{
	DamageMove();

	static float MoveTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	// 왼쪽 이동
	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTCHECKPOS;
	}

	// 오른쪽 이동
	if (Dir == ActorDir::Right)
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

	MoveTimer += _Delta;
}

void Monster::InhaleUpdate(float _Delta)
{
	if (false == BodyCollision->Collision(CollisionOrder::Inhale, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Idle);
		return;
	}
}

void Monster::DamageUpdate(float _Delta)
{
	BodyCollision->Off();

	static float DamageTimer = 0.0f;

	float4 MovePos = float4::ZERO;

	if (ActorDir::Left == DeathDir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
	}

	if (DamageTimer > 1.0f)
	{
		DamageTimer = 0.0f;
		ChangeState(MonsterState::Death);
		return;
	}

	AddPos(MovePos);
	DamageTimer += _Delta;
}

void Monster::DeathUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		return;
	}
}

void Monster::DamageMove()
{
	if (true == BodyCollision->Collision(CollisionOrder::Inhale, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Inhale);
		return;
	}

	if (true == BodyCollision->Collision(CollisionOrder::Attack, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* PlayerAttackCollision = Col[Col.size() - 1];
		GameEngineActor* CurPlayer = PlayerAttackCollision->GetActor();
		float4 DirPos = GetPos() - CurPlayer->GetPos();

		if (0.0f > DirPos.X)
		{
			Dir = ActorDir::Right;
			DeathDir = ActorDir::Left;
			ChangeState(MonsterState::Damage);
			return;
		}
		else
		{
			Dir = ActorDir::Left;
			DeathDir = ActorDir::Right;
			ChangeState(MonsterState::Damage);
			return;
		}
	}
}