#include "GameEngineRenderer.h"
#include "ResourcesManager.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐입니다" + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("이미지를 세팅하지 않은 렌더러입니다");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
}