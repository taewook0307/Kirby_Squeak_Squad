#include "SecondStageLevel.h"
#include "BackGround.h"
#include "Map.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

SecondStageLevel::SecondStageLevel()
{
}

SecondStageLevel::~SecondStageLevel()
{
}

void SecondStageLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("SecondStageLevel.Bmp");

	SecondStage = CreateActor<Map>(RenderOrder::Map);
	SecondStage->MapInit("SecondStage", "SecondStageBitMap.Bmp");
}

void SecondStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("ThirdStageLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		SecondStage->SwitchRender();
	}
}