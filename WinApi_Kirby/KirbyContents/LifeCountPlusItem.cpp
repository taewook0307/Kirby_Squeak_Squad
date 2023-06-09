﻿#include "LifeCountPlusItem.h"
#include "Kirby.h"
#include "SubLevel.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineSound.h>
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
	if (true == BodyCollision->Collision(CollisionOrder::Body, LifeItemCol, CollisionType::Rect, CollisionType::Rect)
		|| static_cast<float>(fabs((GetPos() - Kirby::GetMainKirby()->GetPos()).Size())) < 10.0f)
	{
		SubLevel::PlusPlayerLife();
		GameEngineSound::SoundPlay("ItemGet.wav");
		Death();
		return;
	}
}