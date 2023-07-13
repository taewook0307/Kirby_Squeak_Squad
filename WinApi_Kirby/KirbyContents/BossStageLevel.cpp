#include "BossStageLevel.h"
#include "Ground.h"
#include "Kirby.h"
#include "BossMonster.h"
#include "BossUI.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

BossStageLevel::BossStageLevel()
{
	GameEnginePath Path;
	Path.SetCurrentPath();
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\BGM\\");

	if (nullptr == GameEngineSound::FindSound("Boss.mp3"))
	{
		GameEngineSound::SoundLoad(Path.PlusFilePath("Boss.mp3"));
	}

	if (nullptr == GameEngineSound::FindSound("BossClear.mp3"))
	{
		GameEngineSound::SoundLoad(Path.PlusFilePath("BossClear.mp3"));
	}
}

BossStageLevel::~BossStageLevel()
{
}

void BossStageLevel::Start()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	Stage = CreateActor<Ground>(UpdateOrder::PlayUI);
	Stage->GroundInit("BossStage", "BossStageBitMap.Bmp");

	BossUIObject = CreateActor<BossUI>(UpdateOrder::PlayUI);
	BossUIObject->SetPos({ WinScale.X - 100.0f, WinScale.Y - 100.0f });
}

void BossStageLevel::Update(float _Delta)
{
	FormChange("BossStageBitMap.Bmp");

	if (GetLevelPlayerForm() != MonsterType::Normal && true == GameEngineInput::IsDown('Z'))
	{
		SetLevelPlayerForm(MonsterType::Normal);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("BossStageBitMap.Bmp");
		LevelPlayer->ClearForm();
	}

	// 플레이어 데스 부분
	if (0 < GetPlayerLife() && true == LevelPlayer->GetDeathCheck())
	{
		SetLevelPlayerForm(MonsterType::Normal);
		LevelPlayer->HpReset();
		MinusPlayerLife();
		LevelPlayer->Death();
		Boss->Death();
		GameEngineCore::ChangeLevel("BossStageLevel");
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

void BossStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGM = GameEngineSound::SoundPlay("Boss.mp3", 10);

	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("BossStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	Boss = CreateActor<BossMonster>(UpdateOrder::Monster);
	Boss->SetPos({ WinScale.Half().X + WinScale.Half().Half().X, WinScale.Half().Half().Y });
	Boss->SetGroundBitMap("BossStageBitMap.Bmp");

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
}