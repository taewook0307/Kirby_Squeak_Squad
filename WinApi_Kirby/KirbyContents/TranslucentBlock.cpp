#include "TranslucentBlock.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

TranslucentBlock::TranslucentBlock()
{
}

TranslucentBlock::~TranslucentBlock()
{
}

void TranslucentBlock::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindTexture("FadeObject.Bmp"))
	{
		GameEnginePath Path;

		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\UI\\Fade\\");
		ResourcesManager::GetInst().TextureLoad(Path.PlusFilePath("FadeObject.Bmp"));
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	MainRenderer = CreateUIRenderer(RenderOrder::Fade);
	MainRenderer->SetTexture("FadeObject.bmp");
	MainRenderer->SetRenderPos(WinScale.Half());
	MainRenderer->SetRenderScale(WinScale);
	MainRenderer->SetAlpha(static_cast<unsigned char>(50));
}