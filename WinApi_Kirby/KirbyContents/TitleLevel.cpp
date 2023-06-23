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

	if (nullptr == TitleCutScene)
	{
		MsgBoxAssert("컷신이 제대로 등록되지 않았습니다.");
		return;
	}

	if (nullptr == CheckFade)
	{
		MsgBoxAssert("페이드 인 효과 오브젝트가 제대로 생성되지 않았습니다.");
		return;
	}
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN)
		|| true == GameEngineInput::IsDown(VK_SPACE))
	{
		GameEngineCore::ChangeLevel("FirstStageLevel");
	}
}