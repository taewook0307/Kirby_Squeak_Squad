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
	if (ResourcesManager::GetInst().FindTexture("LifeCount_4.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_4.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("LifeCount_5.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_5.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("LifeCount_6.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LifeCount_6.Bmp"));
	}

	FilePath.MoveParentToExistsChild("UI");
	FilePath.MoveChild("UI\\");

	if (ResourcesManager::GetInst().FindTexture("Life_Icon.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Life_Icon.Bmp"));
	}

	FilePath.MoveParentToExistsChild("UI");
	FilePath.MoveChild("UI\\HpBar\\");

	if (ResourcesManager::GetInst().FindTexture("HpBar_0.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_0.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_10.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_10.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_20.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_20.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_30.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_30.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_40.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_40.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_50.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_50.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_60.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_60.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_70.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_70.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_80.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_80.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_90.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_90.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_100.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_100.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_110.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_110.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_120.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_120.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_130.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_130.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("HpBar_140.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HpBar_140.Bmp"));
	}
}

void KirbyUI::Update(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// FormUI
	if (MonsterType::Fire == SubLevel::GetLevelPlayerForm())
	{
		if (FormUI != nullptr)
		{
			FormUI->Death();
		}
		FormUI = CreateUIRenderer("Fire_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Ice == SubLevel::GetLevelPlayerForm())
	{
		if (FormUI != nullptr)
		{
			FormUI->Death();
		}
		FormUI = CreateUIRenderer("Ice_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Tornado == SubLevel::GetLevelPlayerForm())
	{
		if (FormUI != nullptr)
		{
			FormUI->Death();
		}
		FormUI = CreateUIRenderer("Tornado_Icon.Bmp", RenderOrder::PlayUI);
		FormUI->SetRenderPos(FORMUIPOS);
		FormUI->SetRenderScale(FORMUISCALE);
	}
	if (MonsterType::Spark == SubLevel::GetLevelPlayerForm())
	{
		if (FormUI != nullptr)
		{
			FormUI->Death();
		}
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
	// HpBar
	if (140 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_140.Bmp");
	}

	if (130 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_130.Bmp");
	}

	if (120 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_120.Bmp");
	}

	if (110 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_110.Bmp");
	}

	if (100 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_100.Bmp");
	}

	if (90 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_90.Bmp");
	}

	if (80 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_80.Bmp");
	}

	if (70 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_70.Bmp");
	}

	if (60 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_60.Bmp");
	}

	if (50 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_50.Bmp");
	}

	if (40 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_40.Bmp");
	}

	if (30 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_30.Bmp");
	}

	if (20 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_20.Bmp");
	}

	if (10 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_10.Bmp");
	}

	if (0 == Kirby::GetMainKirby()->GetKirbyHp())
	{
		KirbyHpBarImageUpdate("HpBar_0.Bmp");
	}
	

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// LifeCount
	if (0 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_0.Bmp");
	}

	if (1 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_1.Bmp");
	}

	if (2 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_2.Bmp");
	}

	if (3 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_3.Bmp");
	}

	if (4 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_4.Bmp");
	}

	if (5 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_5.Bmp");
	}

	if (6 == SubLevel::GetPlayerLife())
	{
		KirbyLifeCountImageUpdate("LifeCount_6.Bmp");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		IsCheckPosPointChange();
	}
}

void KirbyUI::LevelStart()
{
	LifeIcon = CreateUIRenderer("Life_Icon.Bmp", RenderOrder::PlayUI);
	LifeIcon->SetRenderPos(LIFEICONPOS);
	LifeIcon->SetRenderScale(LIFEICONSCALE);
}

void KirbyUI::KirbyHpBarImageUpdate(const std::string& _ImageName)
{
	if (nullptr == ResourcesManager::GetInst().FindTexture(_ImageName))
	{
		MsgBoxAssert("커비 LifeCount 수를 나타내는 이미지가 없습니다.");
		return;
	}
	if (HpBar != nullptr)
	{
		HpBar->Death();
	}

	HpBar = CreateUIRenderer(_ImageName, RenderOrder::PlayUI);
	HpBar->SetRenderPos(HPBARPOS);
	HpBar->SetRenderScale(HPBARSCALE);
}

void KirbyUI::KirbyLifeCountImageUpdate(const std::string& _ImageName)
{
	if (nullptr == ResourcesManager::GetInst().FindTexture(_ImageName))
	{
		MsgBoxAssert("커비 LifeCount 수를 나타내는 이미지가 없습니다.");
		return;
	}
	if (nullptr != LifeCount)
	{
		LifeCount->Death();
	}
	LifeCount = CreateUIRenderer(_ImageName, RenderOrder::PlayUI);
	LifeCount->SetRenderPos(LIFECOUNTPOS);
	LifeCount->SetRenderScale(LIFECOUNTSCALE);
}