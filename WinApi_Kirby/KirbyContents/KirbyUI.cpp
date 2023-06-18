#include "KirbyUI.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

KirbyUI::KirbyUI()
{
}

KirbyUI::~KirbyUI()
{
}

void KirbyUI::Start()
{
	if (ResourcesManager::GetInst().FindTexture("Normal_Icon.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\UI\\FormIcon\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Normal_Icon.Bmp"));
	}

	FormUI = CreateUIRenderer("Normal_Icon.Bmp", RenderOrder::PlayUI);
	FormUI->SetRenderPos(float4::ZERO);
	FormUI->SetRenderScale({ 120.0f, 100.0f });

	if (ResourcesManager::GetInst().FindTexture("LifeBar_1.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\UI\\LifeBar\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeBar_1.Bmp"));
	}

	HpBar = CreateUIRenderer("LifeBar_1.Bmp", RenderOrder::PlayUI);
	HpBar->SetRenderPos({200.0f, 30.0f});
	HpBar->SetRenderScale({ 200.0f, 30.0f });
}

void KirbyUI::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		IsCheckPosPointChange();
	}
}

void KirbyUI::Render(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	if (true == IsCheckPosPoint)
	{
		Data.Pos = WinScale.Half();
		Data.Scale = { 120, 100 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = { WinScale.Half().X, WinScale.Half().Y + WinScale.Half().Half().Y };
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}