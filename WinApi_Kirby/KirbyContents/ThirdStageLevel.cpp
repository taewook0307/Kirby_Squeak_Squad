#include "ThirdStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "Kirby.h"
#include "IceMonster.h"
#include "TornadoMonster.h"
#include "LifeCountPlusItem.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

ThirdStageLevel::ThirdStageLevel()
{
}

ThirdStageLevel::~ThirdStageLevel()
{
}

void ThirdStageLevel::Start()
{
	Stage = CreateActor<Ground>(UpdateOrder::Player);
	Stage->GroundInit("ThirdStage", "ThirdStageBitMap.Bmp");

	LifeItem = CreateActor<LifeCountPlusItem>(UpdateOrder::PlayerObject);

	LevelMonster1 = CreateActor<IceMonster>(UpdateOrder::Monster);
	LevelMonster2 = CreateActor<Monster>(UpdateOrder::Monster);
	LevelMonster3 = CreateActor<Monster>(UpdateOrder::Monster);
	// LevelMonster4 = CreateActor<Monster>(UpdateOrder::Monster);
}

void ThirdStageLevel::Update(float _Delta)
{
	FormChange("ThirdStageBitMap.Bmp");

	if (0 < GetPlayerLife() && true == LevelPlayer->GetDeathCheck())
	{
		SetLevelPlayerForm(MonsterType::Normal);
		LevelPlayer->HpReset();
		MinusPlayerLife();
		LevelPlayer->Death();
		GameEngineCore::ChangeLevel("ThirdStageLevel");
	}

	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("BossEntranceLevel");
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

void ThirdStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Back = CreateActor<BackGround>(UpdateOrder::PlayUI);

	SubLevel::LevelStart(_PrevLevel);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	LevelPlayer->SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	LevelPlayer->SetGroundBitMap("ThirdStageBitMap.Bmp");

	GetMainCamera()->SetPos(float4::ZERO);

	{
		LevelMonster1->SetPos({ 1670.0f, 523.0f });
		LevelMonster1->SetGroundBitMap("ThirdStageBitMap.Bmp");

		LevelMonster2->SetPos({ 2600.0f, 640.0f });
		LevelMonster2->SetGroundBitMap("ThirdStageBitMap.Bmp");

		LevelMonster3->SetPos({ 3000.0f, 640.0f });
		LevelMonster3->SetGroundBitMap("ThirdStageBitMap.Bmp");
	}

	{
		LifeItem->SetPos({ 823.0f, 273.0f });
		LifeItem->SetGroundBitMap("ThirdStageBitMap.Bmp");
	}
}