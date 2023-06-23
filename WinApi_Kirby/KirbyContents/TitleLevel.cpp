#include "TitleLevel.h"
#include "CutScene.h"
#include "FadeInObject.h"
#include "FadeOutObject.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	CutScene* TitleCutScene = CreateActor<CutScene>(UpdateOrder::PlayUI);
	TitleCutScene->CutSceneAnimationInit("TitleLevel");

	FadeInObject* CheckFade = CreateActor< FadeInObject>(UpdateOrder::PlayUI);
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN)
		|| true == GameEngineInput::IsDown(VK_SPACE))
	{
		GameEngineCore::ChangeLevel("FirstStageLevel");
	}
}