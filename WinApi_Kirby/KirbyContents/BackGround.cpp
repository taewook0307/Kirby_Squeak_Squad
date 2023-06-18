#include "BackGround.h"
#include "Ground.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
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

void BackGround::BackGroundInit(const std::string& _FileName, const std::string& _GroundFileName /* = "" */)
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

	if (_GroundFileName == "")
	{
		Scale = GameEngineWindow::MainWindow.GetScale();
	}

	else if (true == ResourcesManager::GetInst().IsLoadTexture(_GroundFileName) && _GroundFileName != "")
	{
		MapTexture = ResourcesManager::GetInst().FindTexture(_GroundFileName);

		Scale = { MapTexture->GetScale().X, GameEngineWindow::MainWindow.GetScale().Y };
	}

	else if (false == ResourcesManager::GetInst().IsLoadTexture(_GroundFileName) && _GroundFileName != "")
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

void BackGround::BackGroundAnimationFolderInit(const std::string& _FolderName, const std::string& _GroundFileName /* = "" */, float Inter /*= 0.5f*/)
{
	{
		GameEnginePath FolderPath;

		FolderPath.SetCurrentPath();
		FolderPath.MoveParentToExistsChild("Resources");

		FolderPath.MoveChild("Resources\\BackGround\\");

		MainSprite = ResourcesManager::GetInst().CreateSpriteFolder(_FolderName, FolderPath.PlusFilePath(_FolderName));
	}

	if (_GroundFileName == "")
	{
		Scale = GameEngineWindow::MainWindow.GetScale();
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::BackGround);
		MainRenderer->CreateAnimation(_FolderName, _FolderName, -1, -1, Inter, true);
		MainRenderer->ChangeAnimation(_FolderName);
		MainRenderer->SetRenderPos(Scale.Half());
		MainRenderer->SetRenderScale(Scale);
	}
}