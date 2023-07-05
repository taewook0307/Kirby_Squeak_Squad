#include "TitleLevel.h"
#include "CutScene.h"
#include "FadeInObject.h"
#include "FadeOutObject.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel()
{
	GameEnginePath Path;
	Path.SetCurrentPath();
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\BGM\\");

	if (nullptr == GameEngineSound::FindSound("Title.mp3"))
	{
		GameEngineSound::SoundLoad(Path.PlusFilePath("Title.mp3"));
	}

	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\SoundEffects\\");

	if (nullptr == GameEngineSound::FindSound("Move.wav"))
	{
		GameEngineSound::SoundLoad(Path.PlusFilePath("Move.wav"));
	}
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	TitleBGM = GameEngineSound::SoundPlay("Title.mp3");

	CutScene* TitleCutScene = CreateActor<CutScene>(UpdateOrder::PlayUI);
	TitleCutScene->CutSceneAnimationInit("TitleLevel");

	FadeInObject* StartFade = CreateActor< FadeInObject>(UpdateOrder::PlayUI);

	if (nullptr == TitleCutScene)
	{
		MsgBoxAssert("컷신이 제대로 등록되지 않았습니다.");
		return;
	}

	if (nullptr == StartFade)
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
		TitleBGM.Stop();
		GameEngineSound::SoundPlay("Move.wav");
		GameEngineCore::ChangeLevel("FirstStageLevel");
	}
}