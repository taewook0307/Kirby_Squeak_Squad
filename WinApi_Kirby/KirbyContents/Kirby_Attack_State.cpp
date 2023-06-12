#include "Kirby.h"
#include "KirbyGameEnum.h"
#include "AttackObject.h"
#include "Monster.h"

#include <math.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

void Kirby::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}

void Kirby::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Kirby::AttackToIdleStart()
{
	ChangeAnimationState("AttackToIdle");
}

void Kirby::KeepStart()
{
	ChangeAnimationState("Keep");
}

void Kirby::AttackReadyUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::Attack);
		return;
	}
	if (true == GameEngineInput::IsUp('C'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::AttackUpdate(float _Delta)
{
	DirCheck();

	InhaleCollision->On();

	// 공격 충돌체 제거
	if (true == GameEngineInput::IsUp('C'))
	{
		InhaleCollision->Off();
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
			InhaleCollision->SetCollisionPos(LEFTINHALECOLLSIONSCALE);
		}

		else
		{
			InhaleCollision->SetCollisionPos(RIGHTINHALECOLLSIONSCALE);
		}
	}

	if (true == InhaleCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		BodyCollision->Off();

		Power = 5.0f;

		GameEngineCollision* MonsterCollision = Col[Col.size() - 1];
		MonsterPtr = MonsterCollision->GetActor();
		Monster* KeepMonster = dynamic_cast<Monster*>(MonsterPtr);

		KeepType = KeepMonster->GetMonsterType();
		MonsterPos = KeepMonster->GetPos();
		DirPos = (GetPos() - MonsterPos).NormalizeReturn();

		Power *= 3.0f;

		KeepMonster->AddPos(DirPos *= Power);
		
		if (static_cast<float>(fabs(KeepMonster->GetPos().X - GetPos().X)) < 20.0f)
		{
			if (KeepMonster != nullptr)
			{
				KeepMonster->Death();
				KeepMonster = nullptr;
			}
			InhaleCollision->Off();
			ChangeState(KirbyState::Keep);
			return;
		}
	}
}

void Kirby::AttackToIdleUpdate(float _Delta)
{
	if (StarAttack == nullptr && KeepType == MonsterType::Normal)
	{
		StarAttack = GetLevel()->CreateActor<AttackObject>(RenderOrder::Play);
		StarAttack->SetPos(GetPos());
		StarAttack->SetDir(Dir);
		StarAttack->SetGroundBitMap(GetGroundBitMap());
	}

	if (MainRenderer->IsAnimationEnd())
	{
		StarAttack = nullptr;
		ChangeState(KirbyState::Idle);
		return;
	}
}

void Kirby::KeepUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::KeepIdle);
		return;
	}
}