#include "SparkMonster.h"

#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void SparkMonster::WalkStart()
{
	SetGravityVector(float4::UP * Speed * 3.0f);
	ChangeAnimationState("Walk");
}

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
	unsigned int Color = 0;

	if (GetGravityVector().Y < 0.0f)
	{
		Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);
	}
	else
	{
		Color = GetGroundColor(EMPTYCOLOR);
	}

	Gravity(_Delta);

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == ActorDir::Left)
	{
		MovePos += float4::LEFT * Speed * 2.0f * _Delta;
		CheckPos = LEFTBOTCHECKPOS;
	}
	else
	{
		MovePos += float4::RIGHT * Speed * 2.0f * _Delta;
		CheckPos = RIGHTBOTCHECKPOS;
	}

	unsigned int XColor = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == XColor || DOORCOLOR == XColor)
	{
		AddPos(MovePos);
	}
	
	if(FLOORCOLOR == Color)
	{	
		GravityReset();
		unsigned int CheckColor = GetGroundColor(EMPTYCOLOR, float4::UP);

		while (CheckColor != EMPTYCOLOR && CheckColor != DOORCOLOR)
		{
			CheckColor = GetGroundColor(EMPTYCOLOR, float4::UP);
			AddPos(float4::UP);
		}
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