#include "FadeOutObject.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

FadeOutObject::FadeOutObject()
{
}

FadeOutObject::~FadeOutObject()
{
}

void FadeOutObject::Start()
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

void FadeOutObject::Update(float _Delta)
{
	if (255.0f < AlphaValue)
	{
		FadeEffectEnd = true;
	}
	else
	{
		AlphaValue += _Delta * FadeSpeed;
	}
	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaValue));
}