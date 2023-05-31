#include "Kirby.h"
#include "Monster.h"

#include <math.h>
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
	unsigned int XColor = 0;

	if (FlyPos.Y < 0)
	{
		CheckPos = UPCHECKPOS;
		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else
	{
		Color = GetGroundColor(EMPTYCOLOR);
	}
	

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		AddPos(FlyPos);
	}

	if (DirPos.X > 0.0f)
	{
		MovePos = { Speed * _Delta, 0.0f };
		XCheckPos = LEFTMOVECHECKPOS;
		XColor = GetGroundColor(EMPTYCOLOR, LEFTMOVECHECKPOS);
	}
	else
	{
		MovePos = { -Speed * _Delta, 0.0f };
		XCheckPos = RIGHTMOVECHECKPOS;
		XColor = GetGroundColor(EMPTYCOLOR, LEFTMOVECHECKPOS);
	}

	if (XColor == EMPTYCOLOR || XColor == DOORCOLOR)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}
	
	FlyPower -= 25.0f;

	if (true == MainRenderer->IsAnimationEnd() && EMPTYCOLOR != Color
		|| true == MainRenderer->IsAnimationEnd() && DOORCOLOR != Color)
	{
		FlyPower = BASEPOWER;
		ChangeState(KirbyState::DamageLand);
		return;
	}
}

void Kirby::DamageLandUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
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

	// 공격 충돌체 제거
	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->SetCollisionScale(float4::ZERO);
		AttackCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 MonsterPos = float4::ZERO;
	float4 DirPos = float4::ZERO;
	GameEngineActor* MonsterPtr = nullptr;
	float Power = 0.0f;

	// 공격 충돌체 생성
	if (true == GameEngineInput::IsPress('C'))
	{
		if (ActorDir::Left == Dir)
		{
			AttackCollision->SetCollisionPos({ -90.0f, -40.0f });
			AttackCollision->SetCollisionScale({ 90.0f, 90.0f });
			AttackCollision->On();
		}

		else
		{
			AttackCollision->SetCollisionPos({ 90.0f, -40.0f });
			AttackCollision->SetCollisionScale({90.0f, 90.0f});
			AttackCollision->On();
		}
	}

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		BodyCollision->Off();

		Power = 5.0f;

		GameEngineCollision* MonsterCollision = Col[Col.size() - 1];
		MonsterPtr = MonsterCollision->GetActor();
		Monster* KeepMonster = dynamic_cast<Monster*>(MonsterPtr);

		KeepType = KeepMonster->GetMonsterType();
		MonsterPos = KeepMonster->GetPos();
		DirPos = (GetPos() - MonsterPos).NormalizeReturn();

		Power *= 2.0f;

		KeepMonster->AddPos(DirPos *= Power);
		
		if (static_cast<float>(fabs(KeepMonster->GetPos().X - GetPos().X)) < 20.0f)
		{
			KeepMonster->Death();
			ChangeState(KirbyState::Keep);
			return;
		}
	}
}

void Kirby::KeepUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::KeepIdle);
		return;
	}
	if (true == GameEngineInput::IsDown('X'))
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
