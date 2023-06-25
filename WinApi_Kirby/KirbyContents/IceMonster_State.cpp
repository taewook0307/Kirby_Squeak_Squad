#include "IceMonster.h"

#include <math.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void IceMonster::AttackStart()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	if (GetPos().X > CameraPos.X
		&& GetPos().Y > CameraPos.Y
		&& GetPos().X <= CameraPos.X + WinScale.X
		&& GetPos().Y <= CameraPos.Y + WinScale.Y)
	{
		GameEngineSound::SoundPlay("Ice.wav");
	}
	ChangeAnimationState("Attack");
}

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
	float4 CheckPos = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * 0.5f * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * 0.5f * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* PlayerBodyCollision = Col[Col.size() - 1];
		GameEngineActor* Player = PlayerBodyCollision->GetActor();
		float4 PlayerPos = Player->GetPos();
		float4 MonsterPos = GetPos();
		
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