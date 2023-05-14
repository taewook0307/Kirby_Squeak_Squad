#include "SecondStageLevel.h"
#include "BackGround.h"
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
	CreateActor<BackGround>(RenderOrder::BackGround);
}

void SecondStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('3'))
	{
		GameEngineCore::ChangeLevel("BossStageLevel");
	}
}