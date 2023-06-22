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
	FirstStage = CreateActor<Ground>(UpdateOrder::Player);
	FirstStage->GroundInit("FirstStage", "FirstStageBitMap.Bmp");

	BackGround* Back = CreateActor<BackGround>(UpdateOrder::PlayUI);
	Back->BackGroundInit("FirstStageLevel.Bmp", "FirstStageBitMap.Bmp");

	LevelMonster = CreateActor<SparkMonster>(UpdateOrder::Monster);

	LevelTornadoMonster = CreateActor<TornadoMonster>(UpdateOrder::Monster);

	LevelSparkMonster = CreateActor<SparkMonster>(UpdateOrder::Monster);

	LevelIceMonster = CreateActor<IceMonster>(UpdateOrder::Monster);

	LevelLifeItem = CreateActor<LifeCountPlusItem>(UpdateOrder::PlayerObject);
	LevelLifeItem->SetPos({ 2170.0f, 735.0f });
	LevelLifeItem->SetGroundBitMap("FirstStageBitMap.Bmp");
}

void FirstStageLevel::Update(float _Delta)
{
	// --------------------------------------------------------------------------------------------------------------
	// 폼체인지 부분
	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Ice)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Ice);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<IceKirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Spark)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Spark);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<SparkKirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Fire)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Fire);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<FireKirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (true == GameEngineInput::IsDown('C')
		&& LevelPlayer->GetKirbyState() == KirbyState::KeepIdle
		&& LevelPlayer->GetKeepType() == MonsterType::Tornado)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		SetLevelPlayerForm(MonsterType::Tornado);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<TornadoKirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
	}

	if (GetLevelPlayerForm() != MonsterType::Normal && true == GameEngineInput::IsDown('Z'))
	{
		SetLevelPlayerForm(MonsterType::Normal);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");
		LevelPlayer->ClearForm();
	}
	// --------------------------------------------------------------------------------------------------------------

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
		FirstStage->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}
}

void FirstStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (GetLevelPlayerForm() == MonsterType::Normal)
	{
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();

	}
	else if (GetLevelPlayerForm() == MonsterType::Fire)
	{
		LevelPlayer = CreateActor<FireKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Ice)
	{
		LevelPlayer = CreateActor<IceKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Spark)
	{
		LevelPlayer = CreateActor<SparkKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Tornado)
	{
		LevelPlayer = CreateActor<TornadoKirby>(UpdateOrder::Player);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("FirstStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
		return;
	}

	{
		LevelMonster->SetPos({ 2500.0f, 590.0f });
		LevelMonster->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelTornadoMonster->SetPos({ 7000.0f, 660.0f });
		LevelTornadoMonster->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelSparkMonster->SetPos({ 5100.0f, 660.0f });
		LevelSparkMonster->SetGroundBitMap("FirstStageBitMap.Bmp");

		LevelIceMonster->SetPos({ 5700.0f, 660.0f });
		LevelIceMonster->SetGroundBitMap("FirstStageBitMap.Bmp");
	}
}