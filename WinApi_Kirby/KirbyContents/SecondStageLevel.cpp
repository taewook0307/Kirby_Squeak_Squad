#include "SecondStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "SparkKirby.h"
#include "IceKirby.h"
#include "FireKirby.h"
#include "TornadoKirby.h"
#include "KirbyGameEnum.h"

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
	SecondStage = CreateActor<Ground>(RenderOrder::Map);
	SecondStage->GroundInit("SecondStage", "SecondStageBitMap.Bmp");

	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->BackGroundInit("SecondStageLevel.Bmp", "SecondStageBitMap.Bmp");

}

void SecondStageLevel::Update(float _Delta)
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
		LevelPlayer->ClearForm();
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
}