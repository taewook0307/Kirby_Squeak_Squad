#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

void Kirby::DamageStart()
{
	ChangeAnimationState("Damage");
}

void Kirby::DamageLandStart()
{
	ChangeAnimationState("DamageLand");
}

void Kirby::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}

void Kirby::AttackLoopStart()
{
	ChangeAnimationState("AttackLoop");
}

void Kirby::KeepStart()
{
	ChangeAnimationState("Keep");
}

void Kirby::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Kirby::DamageUpdate(float _Delta)
{
	BodyCollision->Off();

	float4 FlyPos = float4::UP * FlyPower * 0.5f * _Delta;
	float4 MovePos = float4::ZERO;
	float4 XCheckPos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	GameEngineCollision* CurMonsterCollision = Col[Col.size() - 1];
	GameEngineActor* CurMonster = CurMonsterCollision->GetActor();
	float4 DirPos = GetPos() - CurMonster->GetPos();
	unsigned int Color = 0;

	if (FlyPos.Y < 0)
	{
		CheckPos = UPCHECKPOS;
		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else
	{
		Color = GetGroundColor(EMPTYCOLOR);
	}
	

	if (EMPTYCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	if (DirPos.X > 0.0f)
	{
		MovePos = { Speed * _Delta * 0.8f, 0.0f };
		XCheckPos = LEFTMOVECHECKPOS;
	}
	else
	{
		MovePos = { -Speed * _Delta * 0.8f, 0.0f };
		XCheckPos = RIGHTMOVECHECKPOS;
	}

	AddPos(MovePos);
	CameraMove(MovePos);

	FlyPower -= 25.0f;

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::DamageLand);
		return;
	}
}

void Kirby::DamageLandUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color)
	{
		BodyCollision->On();
		GravityReset();
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::AttackReadyUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::AttackLoop);
		return;
	}
}

void Kirby::AttackLoopUpdate(float _Delta)
{
	DirCheck();

	if (true == GameEngineInput::IsPress('C'))
	{
		if (ActorDir::Left == Dir)
		{
			AttackCollision->SetCollisionPos({ -100.0f, -40.0f });
			AttackCollision->On();
		}

		else
		{
			AttackCollision->SetCollisionPos({ 100.0f, -40.0f });
			AttackCollision->On();
		}
	}

	Col.reserve(Col.size() + 1);

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		BodyCollision->Off();

		GameEngineCollision* CurMonsterCollision = Col[Col.size() - 1];
		
		GameEngineActor* CurMonster = CurMonsterCollision->GetActor();

		float4 DirPos = (GetPos() - CurMonster->GetPos()).NormalizeReturn();
		CurMonster->AddPos(DirPos);

		float Check = CurMonster->GetPos().X;
		if (CurMonster->GetPos().X < GetPos().X + 40.0f)
		{	
			ChangeState(KirbyState::Keep);
			return;
		}
	}

	if (true == GameEngineInput::IsUp('C'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::KeepUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void Kirby::AttackUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}
