#include "SecondStageLevel.h"
#include "KirbyNormal.h"
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
	
}

void SecondStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('3'))
	{
		GameEngineCore::ChangeLevel("BossStageLevel");
	}
}