#include "EndingLevel.h"
#include "FadeOutObject.h"
#include "FadeInObject.h"
#include "CutScene.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

EndingLevel::EndingLevel()
{
	GameEnginePath Path;
	Path.SetCurrentPath();
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\CutScene\\EndingLevel\\");

	if (nullptr == ResourcesManager::GetInst().FindTexture("Ending.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(Path.PlusFilePath("Ending.Bmp"));
	}
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	CutScene* EndingTexture = CreateActor<CutScene>(RenderOrder::PlayUI);
	EndingTexture->CutSceneImageInit("Ending.Bmp", "EndingLevel\\");

	{
		FadeInObject* EndFade = CreateActor< FadeInObject>(UpdateOrder::PlayUI);

		if (nullptr == EndFade)
		{
			MsgBoxAssert("페이드 아웃 효과 오브젝트가 제대로 생성되지 않았습니다.");
			return;
		}
	}
}

void EndingLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN) || true == GameEngineInput::IsDown(VK_SPACE))
	{
		GameEngineWindow::MainWindow.WindowLoopOff();
	}
}