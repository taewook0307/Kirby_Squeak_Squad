#include "BossStageLevel.h"
#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

BossStageLevel::BossStageLevel()
{
}

BossStageLevel::~BossStageLevel()
{
}

void BossStageLevel::Start()
{
	
}

void BossStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('4'))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}
}