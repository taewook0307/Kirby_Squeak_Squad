﻿#include "BossStageLevel.h"
#include "Ground.h"
#include "Kirby.h"
#include "IceKirby.h"
#include "FireKirby.h"
#include "SparkKirby.h"
#include "TornadoKirby.h"
#include "BossMonster.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

BossStageLevel::BossStageLevel()
{
}

BossStageLevel::~BossStageLevel()
{
}

void BossStageLevel::Start()
{
	BossStage = CreateActor<Ground>(RenderOrder::Map);
	BossStage->GroundInit("BossStage", "BossStageBitMap.Bmp");

	Boss = CreateActor<BossMonster>(RenderOrder::Boss);

	LevelPlayer = CreateActor<TornadoKirby>(RenderOrder::Play);
	LevelPlayer->MapChangeAnimationEndReset();
	LevelPlayer->ChangeLevelStart();
}

void BossStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BossStage->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}
}

void BossStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	/*if (GetLevelPlayerForm() == MonsterType::Normal)
	{
		LevelPlayer = CreateActor<Kirby>(RenderOrder::Play);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Fire)
	{
		LevelPlayer = CreateActor<FireKirby>(RenderOrder::Play);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Ice)
	{
		LevelPlayer = CreateActor<IceKirby>(RenderOrder::Play);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Spark)
	{
		LevelPlayer = CreateActor<SparkKirby>(RenderOrder::Play);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}
	else if (GetLevelPlayerForm() == MonsterType::Tornado)
	{
		LevelPlayer = CreateActor<TornadoKirby>(RenderOrder::Play);
		LevelPlayer->MapChangeAnimationEndReset();
		LevelPlayer->ChangeLevelStart();
	}*/

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 못했습니다.");
		return;
	}

	if (nullptr == Boss)
	{
		MsgBoxAssert("보스 몬스터가 생성되지 않았습니다.");
		return;
	}

	{
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
		LevelPlayer->SetGroundBitMap("BossStageBitMap.Bmp");

		GetMainCamera()->SetPos(float4::ZERO);

		Boss->SetPos({ WinScale.Half().X + WinScale.Half().Half().X, WinScale.Half().Half().Y });
		Boss->SetGroundBitMap("BossStageBitMap.Bmp");
	}
}