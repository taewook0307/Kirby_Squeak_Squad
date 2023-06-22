#include "BossEntranceLevel.h"
#include "Ground.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

BossEntranceLevel::BossEntranceLevel()
{
}

BossEntranceLevel::~BossEntranceLevel()
{
}

void BossEntranceLevel::Start()
{
	Stage = CreateActor<Ground>(UpdateOrder::PlayUI);
	Stage->GroundInit("BossEntranceStage", "BossEntranceStageBitMap.Bmp");
}

void BossEntranceLevel::Update(float _Delta)
{
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
}