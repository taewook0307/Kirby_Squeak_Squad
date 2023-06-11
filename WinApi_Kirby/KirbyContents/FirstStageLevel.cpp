#include "FirstStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "SparkKirby.h"
#include "IceKirby.h"
#include "FireKirby.h"
#include "TornadoKirby.h"
#include "Monster.h"
#include "FireMonster.h"
#include "IceMonster.h"
#include "SparkMonster.h"
#include "TornadoMonster.h"
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
	LevelPlayer->MapChangeAnimationEndReset();

	LevelMonster = CreateActor<TornadoMonster>(RenderOrder::Play);

	LevelFireMonster = CreateActor<Monster>(RenderOrder::Play);

	LevelTornadoMonster = CreateActor<Monster>(RenderOrder::Play);

	LevelSparkMonster = CreateActor<Monster>(RenderOrder::Play);
}

void FirstStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('X')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Ice)
	{
		SetLevelPlayerForm(MonsterType::Ice);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<IceKirby>(RenderOrder::Play);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == GameEngineInput::IsDown('X')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Spark)
	{
		SetLevelPlayerForm(MonsterType::Spark);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<SparkKirby>(RenderOrder::Play);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == GameEngineInput::IsDown('X')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Fire)
	{
		SetLevelPlayerForm(MonsterType::Fire);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<FireKirby>(RenderOrder::Play);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == GameEngineInput::IsDown('X')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Tornado)
	{
		SetLevelPlayerForm(MonsterType::Tornado);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<TornadoKirby>(RenderOrder::Play);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (GetLevelPlayerForm() != MonsterType::Normal && true == GameEngineInput::IsDown('Z'))
	{
		SetLevelPlayerForm(MonsterType::Normal);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(RenderOrder::Play);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (0 < GetPlayerLife() && true == LevelPlayer->GetDeathCheck())
	{
		int Check = GetPlayerLife();
		MinusPlayerLife();
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		SavePos = { LevelPlayer->GetPos().X, WinScale.Half().Half().Y };
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(RenderOrder::Play);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("SecondStageLevel");
	}

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

		LevelFireMonster->SetPos({ 2100.0f, 735.0f });
		LevelFireMonster->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelTornadoMonster->SetPos({ 7000.0f, 660.0f });
		LevelTornadoMonster->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelSparkMonster->SetPos({ 5100.0f, 660.0f });
		LevelSparkMonster->SetGroundBitMap("FirstStageBitMap.Bmp");
	}
}