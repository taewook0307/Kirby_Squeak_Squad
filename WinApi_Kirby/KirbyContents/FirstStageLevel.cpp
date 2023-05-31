#include "FirstStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "SparkKirby.h"
#include "IceKirby.h"
#include "Monster.h"
#include "IceMonster.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

FirstStageLevel::FirstStageLevel()
{
}

FirstStageLevel::~FirstStageLevel()
{
	
}

void FirstStageLevel::Start()
{
	FirstStage = CreateActor<Ground>(RenderOrder::Map);
	FirstStage->GroundInit("FirstStage", "FirstStageBitMap.Bmp");

	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->BackGroundInit("FirstStageLevel.Bmp", "FirstStageBitMap.Bmp");

	LevelPlayer = CreateActor<Kirby>(RenderOrder::Play);

	LevelMonster = CreateActor<IceMonster>(RenderOrder::Play);

	/*if (nullptr == NewMonster)
	{
		MsgBoxAssert("몬스터를 만들지 못했습니다 : FirstLevel");
	}

	LevelMonsters.push_back(NewMonster);*/
}

void FirstStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		FirstStage->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}
}

void FirstStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	{
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");

		GetMainCamera()->SetPos(float4::ZERO);

		LevelMonster->SetPos({ 1000.0f, 735.0f });
		LevelMonster->SetGroundBitMap("FirstStageBitMap.Bmp");
	}
}