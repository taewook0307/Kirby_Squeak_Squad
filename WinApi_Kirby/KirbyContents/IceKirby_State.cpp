#include "IceKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void IceKirby::AttackUpdate(float _Delta)
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
		GameEngineCollision* MonsterCollision = Col[Col.size() - 1];
		GameEngineActor* MonsterPtr = MonsterCollision->GetActor();

		FrozenMonsterPos = MonsterPtr->GetPos();

		MonsterPtr->Death();
	}

	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->Off();
		ChangeState(KirbyState::AttackToIdle);
		return;
	}
}