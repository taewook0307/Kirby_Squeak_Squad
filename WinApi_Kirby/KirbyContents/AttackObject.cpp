#include "AttackObject.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

AttackObject::AttackObject()
{
}

AttackObject::~AttackObject()
{
}

void AttackObject::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Star.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\Normal\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Star.Bmp"), 5, 3);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Star_Idle", "Star.Bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Star_Death", "Star.Bmp", 8, 11, 0.1f, false);
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);

		MainRenderer->ChangeAnimation("Star_Idle");
	}

	{
		AttackCollision = CreateCollision(CollisionOrder::SpecialAttack);
		AttackCollision->SetCollisionPos(STARCOLLISIONPOS);
		AttackCollision->SetCollisionScale(STARCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}
}

void AttackObject::Update(float _Delta)
{
	if (Dir == ActorDir::Left)
	{
		AddPos(float4::LEFT * _Delta * Speed);
	}
	else
	{
		AddPos(float4::RIGHT * _Delta * Speed);
	}

	if (1.0f < GetLiveTime())
	{
		if (nullptr != MainRenderer)
		{
			MainRenderer->Death();
			MainRenderer = nullptr;
		}
		if (nullptr != AttackCollision)
		{
			AttackCollision->Death();
			AttackCollision = nullptr;
		}
	}
}