#include "HealItem.h"
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
	// std::string HealItemName = "Heal_Item_" + ItemNum + ".Bmp";

	MainRenderer = CreateRenderer("Heal_Item_1.Bmp", RenderOrder::Item);
	MainRenderer->SetRenderPos(HEALITEMPOS);
	MainRenderer->SetRenderScale(HEALITEMSCALE);

	BodyCollision = CreateCollision(CollisionOrder::ItemBody);
	BodyCollision->SetCollisionPos(HEALITEMCOLLISIONPOS);
	BodyCollision->SetCollisionScale(HEALITEMCOLLISIONSCALE);
}

void HealItem::Update(float _Delta)
{

}