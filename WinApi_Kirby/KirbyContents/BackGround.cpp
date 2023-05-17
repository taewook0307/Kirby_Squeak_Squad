#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\BackGround\\" + _FileName);

		MainTexture = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
		
		Scale = GameEngineWindow::MainWindow.GetScale();
	}
	{
		MainRenderer = CreateRenderer(_FileName, RenderOrder::BackGround);
		MainRenderer->SetRenderPos(Scale.Half());
		MainRenderer->SetRenderScale(Scale);
	}
}