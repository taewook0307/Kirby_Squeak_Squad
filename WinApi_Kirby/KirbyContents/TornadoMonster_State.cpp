#include "TornadoMonster.h"

#include <math.h>
#include <GameEngineCore/GameEngineRenderer.h>

void TornadoMonster::IdleUpdate(float _Delta)
{
	BodyCollision->On();

	if (true == MainRenderer->IsAnimationEnd())
	{
		DirChange();
		ChangeState(MonsterState::Walk);
		return;
	}
}

void TornadoMonster::WalkUpdate(float _Delta)
{
	static float WalkTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float MovePower = 3.0f;

	if (Dir == ActorDir::Left)
	{
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		MovePos = float4::LEFT * MovePower;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		SearchCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
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
		ChangeState(MonsterState::Attack);
		return;
	}

	if (WalkTimer > 2.0f)
	{
		WalkTimer = 0.0f;
		ChangeState(MonsterState::Idle);
		return;
	}

	WalkTimer += _Delta;
}

void TornadoMonster::AttackUpdate(float _Delta)
{
	AttackCollision->On();

	float AttackSpeed = 5.0f;

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* PlayerBodyCollision = Col[Col.size() - 1];
		GameEngineActor* Player = PlayerBodyCollision->GetActor();
		float4 PlayerPos = Player->GetPos();
		float4 MonsterPos = GetPos();
		float4 MovePos = (PlayerPos - MonsterPos).NormalizeReturn();

		AddPos(MovePos * AttackSpeed);
	}
	else
	{
		AttackCollision->Off();
		ChangeState(MonsterState::Idle);
		return;
	}
}