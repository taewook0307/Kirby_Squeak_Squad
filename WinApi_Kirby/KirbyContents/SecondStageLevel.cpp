#include "SecondStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "Monster.h"
#include "FireMonster.h"
#include "SparkMonster.h"
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

	LevelHealItem = CreateActor<HealItem>(UpdateOrder::PlayerObject);	
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
		AllMonsterDeath();
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}

	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("ThirdStageLevel");
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
	Back = CreateActor<BackGround>(UpdateOrder::PlayUI);

	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	{
		CreateMonster<Monster>({ 2550.0f, 592.0f }, "SecondStageBitMap.Bmp");
		CreateMonster<SparkMonster>({ 4100.0f, 592.0f }, "SecondStageBitMap.Bmp");
		CreateMonster<Monster>({ 5270.0f, 592.0f }, "SecondStageBitMap.Bmp");
	}

	LevelHealItem->SetPos({ 3300.0f, 520.0f });
	LevelHealItem->SetGroundBitMap("SecondStageBitMap.Bmp");

	{
		LevelObstacle = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelObstacle->SetPos({ 1310.0f, 456.0f });
		LevelObstacle->SetGroundBitMap("SecondStageBitMap.Bmp");

		LevelFloorObstacle1 = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelFloorObstacle1->ChangeFloorObstacle();
		LevelFloorObstacle1->SetRendererRatio(1.2f);
		LevelFloorObstacle1->SetPos({ 3160.0f, 400.0f });
		LevelFloorObstacle1->SetGroundBitMap("SecondStageBitMap.Bmp");

		LevelFloorObstacle2 = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelFloorObstacle2->ChangeFloorObstacle();
		LevelFloorObstacle2->SetRendererRatio(1.2f);
		LevelFloorObstacle2->SetPos({ 3230.0f, 400.0f });
		LevelFloorObstacle2->SetGroundBitMap("SecondStageBitMap.Bmp");

		LevelFloorObstacle3 = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelFloorObstacle3->ChangeFloorObstacle();
		LevelFloorObstacle3->SetRendererRatio(1.2f);
		LevelFloorObstacle3->SetPos({ 3300.0f, 400.0f });
		LevelFloorObstacle3->SetGroundBitMap("SecondStageBitMap.Bmp");

		LevelFloorObstacle4 = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelFloorObstacle4->ChangeFloorObstacle();
		LevelFloorObstacle4->SetRendererRatio(1.2f);
		LevelFloorObstacle4->SetPos({ 3370.0f, 400.0f });
		LevelFloorObstacle4->SetGroundBitMap("SecondStageBitMap.Bmp");

		LevelFloorObstacle5 = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelFloorObstacle5->ChangeFloorObstacle();
		LevelFloorObstacle5->SetRendererRatio(1.2f);
		LevelFloorObstacle5->SetPos({ 3440.0f, 400.0f });
		LevelFloorObstacle5->SetGroundBitMap("SecondStageBitMap.Bmp");

		LevelBiggerObstacle = CreateActor<Obstacle>(UpdateOrder::PlayerObject);
		LevelBiggerObstacle->SetRendererRatio(2.0f);
		LevelBiggerObstacle->SetPos({ 4740.0f, 593.0f });
		LevelBiggerObstacle->SetGroundBitMap("SecondStageBitMap.Bmp");
	}
}