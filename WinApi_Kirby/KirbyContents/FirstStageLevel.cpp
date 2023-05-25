#include "FirstStageLevel.h"
#include "BackGround.h"
#include "Map.h"
#include "Kirby.h"
#include "SparkKirby.h"
#include "IceKirby.h"
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
	GameEngineSound::SoundLoad("aaa", "aaa");

	FirstStage = CreateActor<Map>(RenderOrder::Map);
	FirstStage->MapInit("FirstStage", "FirstStageBitMapTest.Bmp");

	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->BackGroundInit("FirstStageLevel.Bmp", "FirstStageBitMapTest.Bmp");

	LevelPlayer = CreateActor<Kirby>(RenderOrder::Play);
}

void FirstStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		FirstStage->SwitchRender();
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
		LevelPlayer->SetGroundBitMap("FirstStageBitMapTest.Bmp");

		GetMainCamera()->SetPos(float4::ZERO);
	}
}