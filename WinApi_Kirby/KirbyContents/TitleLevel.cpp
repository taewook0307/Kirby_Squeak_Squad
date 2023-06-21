#include "TitleLevel.h"
#include "BackGround.h"
#include "FadeInObject.h"
#include "FadeOutObject.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	BackGround* TitleBack = CreateActor<BackGround>(UpdateOrder::PlayUI);
	TitleBack->BackGroundAnimationFolderInit("TitleLevel");

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