#include "IceKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void IceKirby::AttackLoopUpdate(float _Delta)
{
	DirCheck();

	if (true == GameEngineInput::IsPress('C'))
	{
		if (ActorDir::Left == Dir)
		{
			AttackCollision->SetCollisionPos(LEFTATTACKCOLLISIONPOS);
			AttackCollision->On();
		}

		else
		{
			AttackCollision->SetCollisionPos(RIGHTTATTACKCOLLISIONPOS);
			AttackCollision->On();
		}
	}

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		float Timer = 0.0f;
		GameEngineCollision* MonsterCollision = Col[Col.size() - 1];
		GameEngineActor* MonsterPtr = MonsterCollision->GetActor();
		Monster* KeepMonster = dynamic_cast<Monster*>(MonsterPtr);

		float4 MonsterPos = KeepMonster->GetPos();
		float4 DirPos = (MonsterPos - GetPos()).NormalizeReturn();

		KeepMonster->AddPos(DirPos);

		if (Timer > 3.0f)
		{
			KeepMonster->Death();
			Timer = 0.0f;
		}

		Timer += _Delta;
	}

	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->Off();
		ChangeState(KirbyState::Attack);
		return;
	}
}