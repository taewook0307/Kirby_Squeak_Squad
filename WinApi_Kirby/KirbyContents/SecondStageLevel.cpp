#include "SecondStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "Monster.h"
#include "TornadoMonster.h"
#include "HealItem.h"
#include "Obstacle.h"
#include "TranslucentBlock.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

SecondStageLevel::SecondStageLevel()
{
}

SecondStageLevel::~SecondStageLevel()
{
}

void SecondStageLevel::Start()
{
	Stage = CreateActor<Ground>(UpdateOrder::Player);
	Stage->GroundInit("SecondStage", "SecondStageBitMap.Bmp");

	BackGround* Back = CreateActor<BackGround>(UpdateOrder::PlayUI);
	Back->BackGroundInit("SecondStageLevel.Bmp");

	LevelMonster = CreateActor<Monster>(UpdateOrder::Monster);

	CheetMonster = CreateActor<TornadoMonster>(UpdateOrder::Monster);

	LevelHealItem = CreateActor<HealItem>(UpdateOrder::PlayerObject);

	LevelObstacle = CreateActor<Obstacle>(UpdateOrder::PlayerObject);

	LevelBiggerObstacle = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
}

void SecondStageLevel::Update(float _Delta)
{
	FormChange("SecondStageBitMap.Bmp");

	// 플레이어 데스 부분
	if (0 < GetPlayerLife() && true == LevelPlayer->GetDeathCheck())
	{
		SetLevelPlayerForm(MonsterType::Normal);
		LevelPlayer->HpReset();
		MinusPlayerLife();
		LevelPlayer->Death();
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}

	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("BossEntranceLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		Stage->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}
}

void SecondStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	LevelMonster->SetPos({ 2550.0f, 592.0f });
	LevelMonster->SetGroundBitMap("SecondStageBitMap.Bmp");

	CheetMonster->SetPos({ 5270.0f, 592.0f });
	CheetMonster->SetGroundBitMap("SecondStageBitMap.Bmp");

	LevelHealItem->SetPos({ 3300.0f, 520.0f });
	LevelHealItem->SetGroundBitMap("SecondStageBitMap.Bmp");

	LevelObstacle->SetPos({ 1310.0f, 456.0f });
	LevelObstacle->SetGroundBitMap("SecondStageBitMap.Bmp");

	LevelBiggerObstacle->SetRendererRatio(2.0f);
	LevelBiggerObstacle->SetPos({ 4740.0f, 593.0f });
	LevelBiggerObstacle->SetGroundBitMap("SecondStageBitMap.Bmp");
}