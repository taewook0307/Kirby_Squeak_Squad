﻿#include "FirstStageLevel.h"
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

	LevelMonster1 = CreateActor<Monster>(UpdateOrder::Monster);
	LevelMonster2 = CreateActor<Monster>(UpdateOrder::Monster);
	LevelMonster3 = CreateActor<Monster>(UpdateOrder::Monster);
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
	Back = CreateActor<BackGround>(UpdateOrder::PlayUI);

	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	{
		LevelMonster1->SetPos({ 2000.0f, 592.0f });
		LevelMonster1->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelMonster2->SetPos({ 4100.0f, 512.0f });
		LevelMonster2->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelMonster3->SetPos({ 4600.0f, 512.0f });
		LevelMonster3->SetGroundBitMap("FirstStageBitMap.Bmp");
	}
}