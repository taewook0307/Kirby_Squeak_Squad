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
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("BossStage_1.bmp");
}

void BossStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}
}