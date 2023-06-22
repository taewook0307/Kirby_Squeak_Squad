#include "Kirby.h"
#include "KirbyGameEnum.h"
#include "AttackObject.h"
#include "Monster.h"
#include "BossAttackObject.h"

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
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		KirbyGravity(_Delta);
	}
	else
	{
		GravityReset();
	}

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

	AttackCollision->On();

	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color || DOORCOLOR == Color)
	{
		KirbyGravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	// 흡수 충돌체 제거
	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 MonsterPos = float4::ZERO;
	float4 DirPos = float4::ZERO;
	GameEngineActor* MonsterPtr = nullptr;

	// 흠수 충돌체 생성
	if (true == GameEngineInput::IsPress('C'))
	{
		if (ActorDir::Left == Dir)
		{
			AttackCollision->SetCollisionPos(LEFTINHALECOLLSIONSCALE);
		}

		else
		{
			AttackCollision->SetCollisionPos(RIGHTINHALECOLLSIONSCALE);
		}
	}

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		BodyCollision->Off();

		static float Power = 30.0f;

		GameEngineCollision* MonsterCollision = Col[Col.size() - 1];
		MonsterPtr = MonsterCollision->GetActor();
		Monster* KeepMonster = dynamic_cast<Monster*>(MonsterPtr);

		KeepType = KeepMonster->GetMonsterType();
		MonsterPos = KeepMonster->GetPos();
		DirPos = (GetPos() - MonsterPos).NormalizeReturn();

		KeepMonster->AddPos(DirPos *= Power * _Delta);

		if (Power < 500.0f)
		{
			Power += 50.0f;
		}
		
		if (static_cast<float>(fabs(KeepMonster->GetPos().X - GetPos().X)) < 20.0f)
		{
			if (KeepMonster != nullptr)
			{
				KeepMonster->Death();
				KeepMonster = nullptr;
			}
			AttackCollision->Off();
			ChangeState(KirbyState::Keep);
			return;
		}
	}

	if (true == AttackCollision->Collision(CollisionOrder::BossAttackBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		BodyCollision->Off();

		static float Power = 30.0f;
		GameEngineCollision* BossAttackCollision = Col[Col.size() - 1];
		GameEngineActor* BossAttack = BossAttackCollision->GetActor();

		KeepType = MonsterType::Normal;
		DirPos = (GetPos() - BossAttack->GetPos()).NormalizeReturn();

		BossAttack->AddPos(DirPos *= Power * _Delta);

		if (Power < 500.0f)
		{
			Power += 50.0f;
		}

		if (static_cast<float>(fabs(BossAttack->GetPos().X - GetPos().X)) < 30.0f)
		{
			if (BossAttack != nullptr)
			{
				BossAttack->Death();
				BossAttack = nullptr;
			}
			AttackCollision->Off();
			ChangeState(KirbyState::Keep);
			return;
		}
	}
}

void Kirby::AttackToIdleUpdate(float _Delta)
{
	if (StarAttack == nullptr && KeepType == MonsterType::Normal)
	{
		StarAttack = GetLevel()->CreateActor<AttackObject>(UpdateOrder::PlayerObject);
		StarAttack->SetPos(GetPos());
		StarAttack->SetDir(Dir);
		StarAttack->SetGroundBitMap(GetGroundBitMap());
	}

	if (MainRenderer->IsAnimationEnd())
	{
		StarAttack = nullptr;

		unsigned int Color = GetGroundColor(EMPTYCOLOR);

		if (EMPTYCOLOR == Color || DOORCOLOR == Color)
		{
			GravityReset();
			ChangeState(KirbyState::Drop);
			return;
		}
		else
		{
			if (true == GameEngineInput::IsPress('A') || true == GameEngineInput::IsPress('D'))
			{
				ChangeState(KirbyState::Walk);
				return;
			}

			ChangeState(KirbyState::Idle);
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
}