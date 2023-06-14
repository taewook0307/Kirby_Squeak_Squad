#include "FireMonster.h"

#include <math.h>
#include <GameEngineCore/GameEngineRenderer.h>

void FireMonster::IdleUpdate(float _Delta)
{
	BodyCollision->On();

	static float IdleTimer = 0.0f;

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

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		IdleTimer = 0.0f;
		ChangeState(MonsterState::Walk);
		return;
	}

	if (IdleTimer > 2.0f)
	{
		DirChange();
		IdleTimer = 0.0f;
		ChangeState(MonsterState::Walk);
		return;
	}

	IdleTimer += _Delta;
}

void FireMonster::WalkUpdate(float _Delta)
{
	static float WalkTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float MovePower = 4.0f;

	if (Dir == ActorDir::Left)
	{
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		MovePos = float4::LEFT * MovePower;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		SearchCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
		MovePos = float4::RIGHT * MovePower;
		CheckPos = RIGHTCHECKPOS;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (Color == EMPTYCOLOR || Color == DOORCOLOR)
	{
		AddPos(MovePos);
	}

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* PlayerBodyCollision = Col[Col.size() - 1];
		GameEngineActor* Player = PlayerBodyCollision->GetActor();
		float4 PlayerPos = Player->GetPos();
		float4 MonsterPos = GetPos();
		MovePos = (PlayerPos - MonsterPos).NormalizeReturn();

		AddPos(MovePos);

		float Distance = static_cast<float>(fabs((PlayerPos - MonsterPos).X));

		if (Distance < ATTACKDISTANCE)
		{
			ChangeState(MonsterState::Attack);
			return;
		}
	}

	if (WalkTimer > 2.0f)
	{
		WalkTimer = 0.0f;
		ChangeState(MonsterState::Idle);
		return;
	}

	WalkTimer += _Delta;
}

void FireMonster::AttackUpdate(float _Delta)
{
	AttackCollision->On();

	if (true == MainRenderer->IsAnimationEnd())
	{
		AttackCollision->Off();
		ChangeState(MonsterState::Idle);
		return;
	}
}