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
		AllMonsterDeath();
		GameEngineCore::ChangeLevel("ThirdStageLevel");
	}

	if (true == LevelPlayer->GetMapChangeAnimationEnd())
	{
		BGM.Stop();
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
		CreateMonster<IceMonster>({ 1670.0f, 523.0f }, "ThirdStageBitMap.Bmp");
		CreateMonster<Monster>({ 2600.0f, 640.0f }, "ThirdStageBitMap.Bmp");
		CreateMonster<Monster>({ 3000.0f, 640.0f }, "ThirdStageBitMap.Bmp");
		CreateMonster<TornadoMonster>({ 4300.0f, 650.0f }, "ThirdStageBitMap.Bmp");
		CreateMonster<Monster>({ 5000.0f, 650.0f }, "ThirdStageBitMap.Bmp");
	}

	{
		LifeItem->SetPos({ 823.0f, 273.0f });
		LifeItem->SetGroundBitMap("ThirdStageBitMap.Bmp");
	}
}