#include "SparkMonster.h"

#include <GameEngineCore/GameEngineRenderer.h>

void SparkMonster::IdleUpdate(float _Delta)
{
	static float IdleTimer = 0.0f;

	BodyCollision->On();

	if (IdleTimer > 1.0f)
	{
		IdleTimer = 0.0f;
		ChangeState(MonsterState::Walk);
		return;
	}
	IdleTimer += _Delta;
}

void SparkMonster::WalkUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (Color == EMPTYCOLOR || Color == DOORCOLOR)
	{
		Gravity(_Delta);
	}

	float4 MovePos = float4::UP * 15.0f * _Delta;

	if (Dir == ActorDir::Left)
	{
		MovePos += float4::LEFT * 5.0f * _Delta;
	}
	else
	{
		MovePos += float4::RIGHT * 5.0f * _Delta;
	}

	AddPos(MovePos);

	if(Color != EMPTYCOLOR && Color != DOORCOLOR)
	{	
		GravityReset();
		ChangeState(MonsterState::Attack);
		return;
	}
}

void SparkMonster::AttackUpdate(float _Delta)
{
	AttackCollision->On();

	if (true == BodyCollision->Collision(CollisionOrder::Attack, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == BodyCollision->Collision(CollisionOrder::SpecialAttack, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Damage);
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		AttackCollision->Off();
		DirChange();
		ChangeState(MonsterState::Idle);
		return;
	}
}