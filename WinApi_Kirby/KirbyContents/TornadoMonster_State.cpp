#include "TornadoMonster.h"

#include <math.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void TornadoMonster::AttackStart()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	if (GetPos().X > CameraPos.X
		&& GetPos().Y > CameraPos.Y
		&& GetPos().X <= CameraPos.X + WinScale.X
		&& GetPos().Y <= CameraPos.Y + WinScale.Y)
	{
		GameEngineSound::SoundPlay("Tornado.wav");
	}
	ChangeAnimationState("Attack");
}

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
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (WalkTimer < 0.0f)
	{
		WalkTimer = 2.0f;
		ChangeState(MonsterState::Idle);
		return;
	}

	if (Dir == ActorDir::Left)
	{
		SearchCollision->SetCollisionPos(LEFTSEARCHCOLLISIONPOS);
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else
	{
		SearchCollision->SetCollisionPos(RIGHTTSEARCHCOLLISIONPOS);
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	unsigned int Color = GetGroundColor(EMPTYCOLOR, CheckPos);

	if (Color == EMPTYCOLOR || Color == DOORCOLOR)
	{
		AddPos(MovePos);
	}
	else
	{
		WalkTimer = 2.0f;
		ChangeState(MonsterState::Idle);
		return;
	}

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Attack);
		return;
	}

	WalkTimer -= _Delta;
}

void TornadoMonster::AttackUpdate(float _Delta)
{
	AttackCollision->On();

	float AttackSpeed = 250.0f;

	if (true == SearchCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* PlayerBodyCollision = Col[Col.size() - 1];
		GameEngineActor* Player = PlayerBodyCollision->GetActor();
		float4 PlayerPos = Player->GetPos();
		float4 MonsterPos = GetPos();
		float4 MovePos = (PlayerPos - MonsterPos).NormalizeReturn();

		AddPos(MovePos * AttackSpeed * _Delta);
	}
	else
	{
		AttackCollision->Off();
		ChangeState(MonsterState::Idle);
		return;
	}
}