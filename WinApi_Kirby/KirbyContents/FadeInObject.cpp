#include "FadeInObject.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

FadeInObject::FadeInObject()
{
}

FadeInObject::~FadeInObject()
{
}

void FadeInObject::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindTexture("FadeObject.Bmp")
		|| nullptr == ResourcesManager::GetInst().FindTexture("FadeObject_White.Bmp"))
	{
		GameEnginePath Path;

		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\UI\\Fade\\");

		ResourcesManager::GetInst().TextureLoad(Path.PlusFilePath("FadeObject.Bmp"));
		ResourcesManager::GetInst().TextureLoad(Path.PlusFilePath("FadeObject_White.Bmp"));
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	MainRenderer = CreateUIRenderer(RenderOrder::Fade);
	MainRenderer->SetTexture("FadeObject.bmp");
	MainRenderer->SetRenderPos(WinScale.Half());
	MainRenderer->SetRenderScale(WinScale);
}

void FadeInObject::Update(float _Delta)
{
	AlphaValue -= _Delta * FadeSpeed;
	if (0.0f >= AlphaValue)
	{
		Death();
		return;
	}
	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaValue));
}