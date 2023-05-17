#include "ThirdStageLevel.h"
#include "BackGround.h"
#include "Map.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

ThirdStageLevel::ThirdStageLevel()
{
}

ThirdStageLevel::~ThirdStageLevel()
{
}

void ThirdStageLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("ThirdStageLevel.Bmp");

	Map* ThirdStage = CreateActor<Map>(RenderOrder::Map);
	ThirdStage->MapInit("ThirdStage");
}

void ThirdStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("BossStageLevel");
	}
}