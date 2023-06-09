#include "SparkKirby.h"
#include "Monster.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void SparkKirby::AttackUpdate(float _Delta)
{
	DirCheck();

	AttackCollision->On();

	if (true == GameEngineInput::IsUp('C'))
	{
		AttackCollision->Off();
		ChangeState(KirbyState::AttackToIdle);
		return;
	}
}