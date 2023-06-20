#include "BossUI.h"
#include "BossMonster.h"
#include "SubLevel.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

BossUI::BossUI()
{
}

BossUI::~BossUI()
{
}

void BossUI::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");

	FilePath.MoveChild("Resources\\UI\\MonsterLifeBar\\");

	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_0.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_0.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_10.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_10.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_20.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_20.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_30.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_30.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_40.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_40.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_50.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_50.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_60.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_60.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_70.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_70.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_80.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_80.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_90.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_90.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_100.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_100.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_110.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_110.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_120.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_120.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_130.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_130.Bmp"));
	}
	if (ResourcesManager::GetInst().FindTexture("MonsterLifeBar_140.Bmp") == nullptr)
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MonsterLifeBar_140.Bmp"));
	}
}

void BossUI::Update(float _Delta)
{
	if (140 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_140.Bmp");
	}

	if (130 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_130.Bmp");
	}

	if (120 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_120.Bmp");
	}

	if (110 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_110.Bmp");
	}

	if (100 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_100.Bmp");
	}

	if (90 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_90.Bmp");
	}

	if (80 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_80.Bmp");
	}

	if (70 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_70.Bmp");
	}

	if (60 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_60.Bmp");
	}

	if (50 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_50.Bmp");
	}

	if (40 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_40.Bmp");
	}

	if (30 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_30.Bmp");
	}

	if (20 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_20.Bmp");
	}

	if (10 == BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_10.Bmp");
	}

	if (0 >= BossMonster::GetMainBoss()->GetBossHp())
	{
		BossHpBarImageUpdate("MonsterLifeBar_0.Bmp");
	}
}

void BossUI::BossHpBarImageUpdate(const std::string& _ImageName)
{
	if (nullptr == ResourcesManager::GetInst().FindTexture(_ImageName))
	{
		MsgBoxAssert("몬스터 HPBar가 제대로 로드되지 않았습니다.");
		return;
	}

	if (nullptr != BossHpBar)
	{
		BossHpBar->Death();
	}

	BossHpBar = CreateUIRenderer(_ImageName, RenderOrder::PlayUI);
	BossHpBar->SetRenderPos(BOSSHPBARPOS);
	BossHpBar->SetRenderScale(BOSSHPBARSCALE);
}