#include "CutScene.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

CutScene::CutScene()
{
}

CutScene::~CutScene()
{
}

void CutScene::CutSceneAnimationInit(const std::string& _FolderName, float Inter /*= 0.5f*/)
{
	GameEnginePath FolderPath;

	FolderPath.SetCurrentPath();
	FolderPath.MoveParentToExistsChild("Resources");

	FolderPath.MoveChild("Resources\\CutScene\\");

	MainSprite = ResourcesManager::GetInst().CreateSpriteFolder(_FolderName, FolderPath.PlusFilePath(_FolderName));

	Scale = GameEngineWindow::MainWindow.GetScale();

	MainRenderer = CreateRenderer(RenderOrder::BackGround);
	MainRenderer->CreateAnimation(_FolderName, _FolderName, -1, -1, Inter, true);
	MainRenderer->ChangeAnimation(_FolderName);
	MainRenderer->SetRenderPos(Scale.Half());
	MainRenderer->SetRenderScale(Scale);
}

void CutScene::CutSceneImageInit(const std::string& _FileName, const std::string& _FolderName /*= ""*/)
{
	GameEnginePath FolderPath;

	FolderPath.SetCurrentPath();
	FolderPath.MoveParentToExistsChild("Resources");

	FolderPath.MoveChild("Resources\\CutScene\\");

	if (_FolderName != "")
	{
		FolderPath.MoveChild(_FolderName);
	}

	Scale = GameEngineWindow::MainWindow.GetScale();

	MainRenderer = CreateRenderer(RenderOrder::BackGround);
	MainRenderer->SetTexture(_FileName);
	MainRenderer->SetRenderPos(Scale.Half());
	MainRenderer->SetRenderScale(Scale);
}