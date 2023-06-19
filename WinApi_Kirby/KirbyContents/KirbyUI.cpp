#include "KirbyUI.h"
#include "Kirby.h"
#include "SubLevel.h"
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
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");

	FilePath.MoveChild("Resources\\UI\\FormIcon\\");

	if (ResourcesManager::GetInst().FindTexture("Normal_Icon.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Normal_Icon.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("Ice_Icon.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Ice_Icon.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("Fire_Icon.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Fire_Icon.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("Tornado_Icon.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Tornado_Icon.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("Spark_Icon.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Spark_Icon.Bmp"));
	}

	FilePath.MoveParentToExistsChild("Resources");

	FilePath.MoveChild("Resources\\UI\\LifeCount\\");

	if (ResourcesManager::GetInst().FindTexture("LifeCount_0.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_0.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("LifeCount_1.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_1.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("LifeCount_2.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_2.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("LifeCount_3.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_3.Bmp"));
	}

	/*if (ResourcesManager::GetInst().FindSprite("LifeBar.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\UI\\LifeBar\\");

		ResourcesManager::GetInst().CreateSpriteFolder(FilePath.GetStringPath());
	}

	HpBar = CreateUIRenderer("LifeBar_1.Bmp", RenderOrder::PlayUI);
	HpBar->SetRenderPos({200.0f, 30.0f});
	HpBar->SetRenderScale({ 200.0f, 30.0f });*/
}

void KirbyUI::Update(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// FormUI
	if (MonsterType::Fire == SubLevel::GetLevelPlayerForm())
	{
		FormUI->Death();
		FormUI = CreateUIRenderer("Fire_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Ice == SubLevel::GetLevelPlayerForm())
	{
		FormUI->Death();
		FormUI = CreateUIRenderer("Ice_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Tornado == SubLevel::GetLevelPlayerForm())
	{
		FormUI->Death();
		FormUI = CreateUIRenderer("Tornado_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Spark == SubLevel::GetLevelPlayerForm())
	{
		FormUI->Death();
		FormUI = CreateUIRenderer("Spark_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Normal == SubLevel::GetLevelPlayerForm())
	{
		if (FormUI != nullptr)
		{
			FormUI->Death();
		}
		
		FormUI = CreateUIRenderer("Normal_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// LifeCount
	if (0 == SubLevel::GetPlayerLife())
	{
		if (LifeCount != nullptr)
		{
			LifeCount->Death();
		}
		LifeCount = CreateUIRenderer("LifeCount_0.Bmp", RenderOrder::PlayUI);
		LifeCount->SetRenderPos(LIFECOUNTPOS);
		LifeCount->SetRenderScale(LIFECOUNTSCALE);
	}

	if (1 == SubLevel::GetPlayerLife())
	{
		if (LifeCount != nullptr)
		{
			LifeCount->Death();
		}
		LifeCount = CreateUIRenderer("LifeCount_1.Bmp", RenderOrder::PlayUI);
		LifeCount->SetRenderPos(LIFECOUNTPOS);
		LifeCount->SetRenderScale(LIFECOUNTSCALE);
	}

	if (2 == SubLevel::GetPlayerLife())
	{
		if (LifeCount != nullptr)
		{
			LifeCount->Death();
		}
		LifeCount = CreateUIRenderer("LifeCount_2.Bmp", RenderOrder::PlayUI);
		LifeCount->SetRenderPos(LIFECOUNTPOS);
		LifeCount->SetRenderScale(LIFECOUNTSCALE);
	}

	if (3 == SubLevel::GetPlayerLife())
	{
		if (LifeCount != nullptr)
		{
			LifeCount->Death();
		}
		LifeCount = CreateUIRenderer("LifeCount_3.Bmp", RenderOrder::PlayUI);
		LifeCount->SetRenderPos(LIFECOUNTPOS);
		LifeCount->SetRenderScale(LIFECOUNTSCALE);
	}


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
		Data.Pos = { 100.0f, 100.0f };
		Data.Scale = { 120, 100 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = { WinScale.Half().X, WinScale.Half().Y + WinScale.Half().Half().Y };
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void KirbyUI::LevelStart()
{
	/*FormUI = CreateUIRenderer("Normal_Icon.Bmp", RenderOrder::PlayUI);
	FormUI->SetRenderPos(FORMUIPOS);
	FormUI->SetRenderScale(FORMUISCALE);*/
}