#include "IceMonster.h"

#include <math.h>
#include <GameEngineCore/GameEngineRenderer.h>

void IceMonster::IdleUpdate(float _Delta)
{
	BodyCollision->On();

	static float IdleTimer = 0.0f;

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Walk);
		return;
	}

	if (Dir == ActorDir::Left)
	{
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
	}
	else
	{
		SearchCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
	}

	if (IdleTimer > 3.0f)
	{
		DirChange();
		IdleTimer = 0.0f;
	}

	IdleTimer += _Delta;
}

void IceMonster::WalkUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* PlayerBodyCollision = Col[Col.size() - 1];
		GameEngineActor* Player = PlayerBodyCollision->GetActor();
		float4 PlayerPos = Player->GetPos();
		float4 MonsterPos = GetPos();
		float4 MovePos = (PlayerPos - MonsterPos).NormalizeReturn() * _Delta;

		AddPos(MovePos);

		float Distance = static_cast<float>(fabs((PlayerPos - MonsterPos).X));

		if (Distance < ATTACKDISTANCE)
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

void IceMonster::AttackUpdate(float _Delta)
{
	AttackCollision->On();

	if (true == MainRenderer->IsAnimationEnd())
	{
		AttackCollision->Off();
		ChangeState(MonsterState::Idle);
		return;
	}
}