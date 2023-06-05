#include "SecondStageLevel.h"
#include "BackGround.h"
#include "Ground.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

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

	MonsterType Check = GetLevelPlayerForm();
}

void SecondStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
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