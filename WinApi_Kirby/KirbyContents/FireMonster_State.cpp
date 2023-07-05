#include "FireMonster.h"

#include <math.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void FireMonster::AttackStart()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	if (GetPos().X > CameraPos.X
		&& GetPos().Y > CameraPos.Y
		&& GetPos().X <= CameraPos.X + WinScale.X
		&& GetPos().Y <= CameraPos.Y + WinScale.Y)
	{
		GameEngineSound::SoundPlay("Fire.wav");
	}
	ChangeAnimationState("Attack");
}

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
	if (true == BodyCollision->Collision(CollisionOrder::Obstacle, Col, CollisionType::Rect, CollisionType::Rect))
	{
		DirChange();
	}

	static float WalkTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (Dir == ActorDir::Left)
	{
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		SearchCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
		AttackCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (EMPTYCOLOR == Color && false == BodyCollision->Collision(CollisionOrder::Obstacle, Col, CollisionType::Rect, CollisionType::Rect)
		|| DOORCOLOR == Color && false == BodyCollision->Collision(CollisionOrder::Obstacle, Col, CollisionType::Rect, CollisionType::Rect))
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

		if (EMPTYCOLOR == Color && false == BodyCollision->Collision(CollisionOrder::Obstacle, Col, CollisionType::Rect, CollisionType::Rect)
			|| DOORCOLOR == Color && false == BodyCollision->Collision(CollisionOrder::Obstacle, Col, CollisionType::Rect, CollisionType::Rect))
		{
			AddPos(MovePos);

			float Distance = static_cast<float>(fabs((PlayerPos - MonsterPos).X));

			if (Distance < ATTACKDISTANCE)
			{
				ChangeState(MonsterState::Attack);
				return;
			}
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
		DirChange();
		ChangeState(MonsterState::Idle);
		return;
	}
}