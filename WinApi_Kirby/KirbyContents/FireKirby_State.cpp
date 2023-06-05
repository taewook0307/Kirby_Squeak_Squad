#include "FireKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void FireKirby::AttackLoopUpdate(float _Delta)
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