#include "BossStageLevel.h"
#include "Ground.h"
#include "BossMonster.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

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
}

void BossStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Boss)
	{
		MsgBoxAssert("보스 몬스터가 생성되지 않았습니다.");
		return;
	}

	{
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		Boss->SetPos({ WinScale.Half().X + WinScale.Half().Half().X, WinScale.Half().Half().Y });
		Boss->SetGroundBitMap("BossStageBitMap.Bmp");
	}
}