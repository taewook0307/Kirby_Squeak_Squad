#include "BossEntranceLevel.h"
#include "Ground.h"
#include "Kirby.h"
#include "HealItem.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

BossEntranceLevel::BossEntranceLevel()
{
	GameEnginePath Path;
	Path.SetCurrentPath();
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\BGM\\");

	if (nullptr == GameEngineSound::FindSound("BossReady.mp3"))
	{
		GameEngineSound::SoundLoad(Path.PlusFilePath("BossReady.mp3"));
	}
}

BossEntranceLevel::~BossEntranceLevel()
{
}

void BossEntranceLevel::Start()
{
	Stage = CreateActor<Ground>(UpdateOrder::PlayUI);
	Stage->GroundInit("BossEntranceStage", "BossEntranceStageBitMap.Bmp");

	HealItem1 = CreateActor<HealItem>(UpdateOrder::PlayerObject);
	HealItem2 = CreateActor<HealItem>(UpdateOrder::PlayerObject);
}

void BossEntranceLevel::Update(float _Delta)
{
	FormChange("BossEntranceStageBitMap.Bmp");

	if (GetLevelPlayerForm() != MonsterType::Normal && true == GameEngineInput::IsDown('Z'))
	{
		SetLevelPlayerForm(MonsterType::Normal);
		SavePos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<Kirby>(UpdateOrder::Player);
		LevelPlayer->SetPos(SavePos);
		LevelPlayer->SetGroundBitMap("BossEntranceStageBitMap.Bmp");
		LevelPlayer->ClearForm();
	}

	// 플레이어 데스 부분
	if (0 < GetPlayerLife() && true == LevelPlayer->GetDeathCheck())
	{
		SetLevelPlayerForm(MonsterType::Normal);
		LevelPlayer->HpReset();
		MinusPlayerLife();
		LevelPlayer->Death();
	}

	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		BGM.Stop();
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

void BossEntranceLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGM = GameEngineSound::SoundPlay("BossReady.mp3");
	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ 100.0f, 350.0f });
	LevelPlayer->SetGroundBitMap("BossEntranceStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 못했습니다.");
		return;
	}

	{
		HealItem1->SetPos({ 290.0f, 320.0f });
		HealItem1->SetGroundBitMap("BossEntranceStageBitMap.Bmp");

		HealItem2->SetPos({ 735.0f, 320.0f });
		HealItem2->SetGroundBitMap("BossEntranceStageBitMap.Bmp");
	}
}