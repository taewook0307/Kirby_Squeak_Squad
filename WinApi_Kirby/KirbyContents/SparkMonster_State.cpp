#include "SparkMonster.h"

#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void SparkMonster::AttackStart()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	if (GetPos().X > CameraPos.X
		&& GetPos().Y > CameraPos.Y
		&& GetPos().X <= CameraPos.X + WinScale.X
		&& GetPos().Y <= CameraPos.Y + WinScale.Y)
	{
		GameEngineSound::SoundPlay("Spark.wav");
	}
	ChangeAnimationState("Attack");
}

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

	float4 MovePos = float4::UP * Speed * 2.0f * _Delta;

	if (Dir == ActorDir::Left)
	{
		MovePos += float4::LEFT * Speed * _Delta;
	}
	else
	{
		MovePos += float4::RIGHT * Speed * _Delta;
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