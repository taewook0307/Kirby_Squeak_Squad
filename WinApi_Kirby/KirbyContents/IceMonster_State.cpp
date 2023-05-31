#include "IceMonster.h"

void IceMonster::IdleUpdate(float _Delta)
{
	static float IdleTimer = 0.0f;

	Col.resize(Col.size() + 1);

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Walk);
		return;
	}

	if (Dir == ActorDir::Left)
	{
		SearchCollision->SetCollisionPos({ -140.0f, -30.0f });
	}
	else
	{
		SearchCollision->SetCollisionPos({ 140.0f, -30.0f });
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
		float4 MovePos = (PlayerPos - MonsterPos).NormalizeReturn();

		AddPos(MovePos);
	}
	else
	{
		ChangeState(MonsterState::Idle);
		return;
	}
}

void IceMonster::DamageUpdate(float _Delta)
{

}

void IceMonster::AttackUpdate(float _Delta)
{

}