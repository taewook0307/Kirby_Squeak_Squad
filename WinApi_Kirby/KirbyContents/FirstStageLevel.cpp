#include "FirstStageLevel.h"
#include "BackGround.h"
#include "Map.h"
#include "Kirby.h"
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
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("FirstStageLevel.Bmp");

	Map* FirstStageMap = CreateActor<Map>(RenderOrder::Map);
	FirstStageMap->Init("FirstStageMap_1.bmp");

	Player = CreateActor<Kirby>(RenderOrder::Play);
	Player->FormInit("NormalKirby", "Kirby_Idle_1.bmp");
}

void FirstStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}
}