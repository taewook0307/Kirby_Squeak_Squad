#include "BossAttackObject.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

BossAttackObject::BossAttackObject()
{
}

BossAttackObject::~BossAttackObject()
{
}

void BossAttackObject::Start()
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
		MainRenderer->CreateAnimation("Star_Inhale", "Star.Bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Star_Death", "Star.Bmp", 8, 11, 0.1f, false);
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);

		MainRenderer->ChangeAnimation("Star_Idle");
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::BossAttackBody);
		BodyCollision->SetCollisionPos(BOSSATTACKCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BOSSATTACKCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);

		AttackCollision = CreateCollision(CollisionOrder::BossAttack);
		AttackCollision->SetCollisionPos(BOSSATTACKCOLLISIONPOS);
		AttackCollision->SetCollisionScale(BOSSATTACKCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}
}

void BossAttackObject::Update(float _Delta)
{
	float4 Dir = Kirby::GetMainKirby()->GetPos() - GetPos();

	Dir.Normalize();

	AddPos(Dir * Speed * _Delta);

	if (true == AttackCollision->Collision(CollisionOrder::Body, BossAttackCol, CollisionType::Rect, CollisionType::Rect))
	{
		MainRenderer->ChangeAnimation("Star_Death");

		if (true == MainRenderer->IsAnimationEnd())
		{
			Death();
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::Inhale, BossAttackCol, CollisionType::Rect, CollisionType::Rect))
	{
		AttackCollision->Off();
	}
}