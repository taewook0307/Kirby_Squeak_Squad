#include "FirstStageLevel.h"
#include "KirbyNormal.h"
#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

FirstStageLevel::FirstStageLevel()
{
}

FirstStageLevel::~FirstStageLevel()
{
}

void FirstStageLevel::Start()
{
	CreateActor<KirbyNormal>(RenderOrder::Play);
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("FirstStage_1.Bmp");
}

void FirstStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}
}