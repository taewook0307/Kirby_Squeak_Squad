#include "BossStageLevel.h"
#include "Ground.h"
#include "KirbyGameEnum.h"

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