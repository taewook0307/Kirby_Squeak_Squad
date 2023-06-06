#include "TornadoKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void TornadoKirby::AttackUpdate(float _Delta)
{
	DirCheck();

	AttackCollision->On();
	BodyCollision->Off();

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* MonsterCollision = Col[Col.size() - 1];
		GameEngineActor* MonsterPtr = MonsterCollision->GetActor();
		Monster* KeepMonster = dynamic_cast<Monster*>(MonsterPtr);

		KeepMonster->Death();
	}
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D') && Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}
	
	unsigned int Color = GetGroundColor(EMPTYCOLOR, MovePos);

	if (Color == EMPTYCOLOR)
	{
		AddPos(MovePos);
		CameraMove(MovePos);
	}

	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->Off();
		BodyCollision->On();
		ChangeState(KirbyState::Attack);
		return;
	}
}