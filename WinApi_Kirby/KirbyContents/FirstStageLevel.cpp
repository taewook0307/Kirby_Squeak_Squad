﻿#include "FirstStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "Monster.h"
#include "FireMonster.h"
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
	GameEnginePath Path;
	Path.SetCurrentPath();
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\BGM\\");

	if (nullptr == GameEngineSound::FindSound("Play.mp3"))
	{
		GameEngineSound::SoundLoad(Path.PlusFilePath("Play.mp3"));
	}
}

FirstStageLevel::~FirstStageLevel()
{

}

void FirstStageLevel::Start()
{
	Stage = CreateActor<Ground>(UpdateOrder::Player);
	Stage->GroundInit("FirstStage", "FirstStageBitMap.Bmp");
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
		AllMonsterDeath();
		BGM.Stop();
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
	BGM = GameEngineSound::SoundPlay("Play.mp3", 10);

	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	{
		CreateMonster<Monster>({ 2000.0f, 592.0f }, "FirstStageBitMap.Bmp");
		CreateMonster<Monster>({ 2600.0f, 592.0f }, "FirstStageBitMap.Bmp");
		CreateMonster<Monster>({ 4100.0f, 512.0f }, "FirstStageBitMap.Bmp");
		CreateMonster<Monster>({ 4600.0f, 512.0f }, "FirstStageBitMap.Bmp");
		CreateMonster<FireMonster>({ 5400.0f, 521.0f }, "FirstStageBitMap.Bmp");
	}
}