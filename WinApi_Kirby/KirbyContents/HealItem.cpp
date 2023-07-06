#include "HealItem.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"
#include "ActorEnum.h"

#include <string>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

HealItem::HealItem()
{
}

HealItem::~HealItem()
{
}

void HealItem::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");

	FilePath.MoveChild("Resources\\Item\\");

	if (nullptr == ResourcesManager::GetInst().FindTexture("Heal_Item_1.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Heal_Item_1.Bmp"));
	}
	if (nullptr == ResourcesManager::GetInst().FindTexture("Heal_Item_2.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Heal_Item_2.Bmp"));
	}
	if (nullptr == ResourcesManager::GetInst().FindTexture("Heal_Item_3.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Heal_Item_3.Bmp"));
	}
	if (nullptr == ResourcesManager::GetInst().FindTexture("Heal_Item_4.Bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Heal_Item_4.Bmp"));
	}

	int ItemNum = GameEngineRandom::MainRandom.RandomInt(1, 4);
	
	switch (ItemNum)
	{
	case 1:
	{
		MainRenderer = CreateRenderer("Heal_Item_1.Bmp", RenderOrder::Item);
		HealValue = 10;
		break;
	}
	case 2:
	{
		MainRenderer = CreateRenderer("Heal_Item_2.Bmp", RenderOrder::Item);
		HealValue = 10;
		break;
	}
	case 3:
	{
		MainRenderer = CreateRenderer("Heal_Item_3.Bmp", RenderOrder::Item);
		HealValue = 20;
		break;
	}
	case 4:
	{
		MainRenderer = CreateRenderer("Heal_Item_4.Bmp", RenderOrder::Item);
		HealValue = 40;
		break;
	}
	default:
		break;
	}
	MainRenderer->SetRenderPos(HEALITEMPOS);
	MainRenderer->SetRenderScale(HEALITEMSCALE);

	BodyCollision = CreateCollision(CollisionOrder::ItemBody);
	BodyCollision->SetCollisionPos(HEALITEMCOLLISIONPOS);
	BodyCollision->SetCollisionScale(HEALITEMCOLLISIONSCALE);
}

void HealItem::Update(float _Delta)
{
	if (true == BodyCollision->Collision(CollisionOrder::Body, HealItemCol, CollisionType::Rect, CollisionType::Rect)
		|| static_cast<float>(fabs(GetPos().X - Kirby::GetMainKirby()->GetPos().X)) < 20.0f)
	{
		int PlayerHp = Kirby::GetMainKirby()->GetKirbyHp();
		int HealHp = PlayerHp + HealValue;
		if (HealHp > 120)
		{
			Kirby::GetMainKirby()->HpReset();
		}
		else
		{
			Kirby::GetMainKirby()->SetKirbyHp(HealHp);
		}
		GameEngineSound::SoundPlay("ItemGet.wav");
		Death();
		return;
	}
}