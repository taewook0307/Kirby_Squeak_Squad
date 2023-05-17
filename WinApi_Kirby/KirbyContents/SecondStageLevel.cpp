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

	Map* SecondStage = CreateActor<Map>(RenderOrder::Map);
	SecondStage->MapInit("SecondStage");
}

void SecondStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("ThirdStageLevel");
	}
}