#include "FirstStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "Monster.h"
#include "FireMonster.h"
#include "IceMonster.h"
#include "SparkMonster.h"
#include "TornadoMonster.h"
#include "LifeCountPlusItem.h"
#include "HealItem.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

FirstStageLevel::FirstStageLevel()
{
}

FirstStageLevel::~FirstStageLevel()
{

}

void FirstStageLevel::Start()
{
	Stage = CreateActor<Ground>(UpdateOrder::Player);
	Stage->GroundInit("FirstStage", "FirstStageBitMap.Bmp");

	BackGround* Back = CreateActor<BackGround>(UpdateOrder::PlayUI);
	Back->BackGroundInit("FirstStageLevel.Bmp");

	LevelMonster = CreateActor<SparkMonster>(UpdateOrder::Monster);
}

void FirstStageLevel::Update(float _Delta)
{
	FormChange("FirstStageBitMap.Bmp");

	// 플레이어 데스 부분
	if (0 < GetPlayerLife() && true == LevelPlayer->GetDeathCheck())
	{
		SetLevelPlayerForm(MonsterType::Normal);
		LevelPlayer->HpReset();
		MinusPlayerLife();
		LevelPlayer->Death();
		GameEngineCore::ChangeLevel("FirstStageLevel");
	}

	// 맵 이동
	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}

	// 디버그용
	if (true == GameEngineInput::IsDown('J'))
	{
		Stage->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}
}

void FirstStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	{
		LevelMonster->SetPos({ 2500.0f, 592.0f });
		LevelMonster->SetGroundBitMap("FirstStageBitMap.Bmp");
	}
}