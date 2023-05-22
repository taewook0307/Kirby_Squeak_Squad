#include "BackGround.h"
#include "Map.h"
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

void BackGround::BackGroundInit(const std::string& _FileName, const std::string& _MapFileName /* = "" */)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\BackGround\\" + _FileName);

		MainTexture = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	if (_MapFileName == "")
	{
		Scale = GameEngineWindow::MainWindow.GetScale();
	}

	else if (true == ResourcesManager::GetInst().IsLoadTexture(_MapFileName) && _MapFileName != "")
	{
		MapTexture = ResourcesManager::GetInst().FindTexture(_MapFileName);

		Scale = { MapTexture->GetScale().X, GameEngineWindow::MainWindow.GetScale().Y };
	}

	else if (false == ResourcesManager::GetInst().IsLoadTexture(_MapFileName) && _MapFileName != "")
	{
		MsgBoxAssert("등록되지 않은 Map 이미지로 배경의 크기를 지정하려 했습니다.");
		return;
	}

	{
		MainRenderer = CreateRenderer(_FileName, RenderOrder::BackGround);
		MainRenderer->SetRenderPos(Scale.Half());
		MainRenderer->SetRenderScale(Scale);
	}
}