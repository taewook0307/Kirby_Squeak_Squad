#include "SecondStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "SparkKirby.h"
#include "IceKirby.h"
#include "FireKirby.h"
#include "TornadoKirby.h"
#include "Monster.h"
#include "TornadoMonster.h"
#include "HealItem.h"
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
	SecondStage = CreateActor<Ground>(UpdateOrder::Player);
	SecondStage->GroundInit("SecondStage", "SecondStageBitMap.Bmp");

	BackGround* Back = CreateActor<BackGround>(UpdateOrder::PlayUI);
	Back->BackGroundInit("SecondStageLevel.Bmp", "SecondStageBitMap.Bmp");

	LevelMonster = CreateActor<Monster>(UpdateOrder::Monster);

	CheetMonster = CreateActor<TornadoMonster>(UpdateOrder::Monster);

	LevelHealItem = CreateActor<HealItem>(UpdateOrder::PlayerObject);
}

void SecondStageLevel::Update(float _Delta)
{
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
		LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");
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
		LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");
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
		LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");
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
		LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");
	}

	if (GetLevelPlayerForm() != MonsterType::Normal && true == GameEngineInput::IsDown('Z'))
	{
		SetLevelPlayerForm(MonsterType::Normal);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");
		LevelPlayer->ClearForm();
	}

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
		GameEngineCore::ChangeLevel("BossStageLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		SecondStage->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}
}

void SecondStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
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

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 못했습니다.");
		return;
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("SecondStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	LevelMonster->SetPos({ 2550.0f, 592.0f });
	LevelMonster->SetGroundBitMap("SecondStageBitMap.Bmp");

	CheetMonster->SetPos({ 5270.0f, 592.0f });
	CheetMonster->SetGroundBitMap("SecondStageBitMap.Bmp");

	LevelHealItem->SetPos({ 4145.0f, 592.0f });
	LevelHealItem->SetGroundBitMap("SecondStageBitMap.Bmp");
}