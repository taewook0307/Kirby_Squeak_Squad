#include "LifeCountPlusItem.h"
#include "KirbyGameEnum.h"
#include "SubLevel.h"
#include "ActorEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

LifeCountPlusItem::LifeCountPlusItem()
{
}

LifeCountPlusItem::~LifeCountPlusItem()
{
}

void LifeCountPlusItem::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindTexture("Life_Item.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Item\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Life_Item.Bmp"));
	}

	MainRenderer = CreateRenderer("Life_Item.Bmp", RenderOrder::Item);
	MainRenderer->SetRenderPos(LIFEITEMPOS);
	MainRenderer->SetRenderScale(LIFEITEMSCALE);

	BodyCollision = CreateCollision(CollisionOrder::ItemBody);
	BodyCollision->SetCollisionPos(LIFEITEMCOLLISIONPOS);
	BodyCollision->SetCollisionScale(LIFEITEMCOLLISIONSCALE);
}

void LifeCountPlusItem::Update(float _Delta)
{
	if (true == BodyCollision->Collision(CollisionOrder::Body, LifeItemCol, CollisionType::Rect, CollisionType::Rect))
	{
		SubLevel::PlusPlayerLife();
		Death();
		return;
	}
}