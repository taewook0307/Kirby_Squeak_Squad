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
		MainRenderer = CreateRenderer(RenderOrder::Monster);

		MainRenderer->CreateAnimation("BossAttack_Idle", "Star.Bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("BossAttack_Death", "Star.Bmp", 8, 11, 0.1f, false);
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);

		MainRenderer->ChangeAnimation("BossAttack_Idle");
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

	if (true == Move)
	{
		AddPos(Dir * Speed * _Delta);
	}

	if (true == AttackCollision->Collision(CollisionOrder::Body, BossAttackCol, CollisionType::Rect, CollisionType::Rect)
		&& false == BodyCollision->Collision(CollisionOrder::Inhale, BossAttackCol, CollisionType::Rect, CollisionType::Rect))
	{
		Move = false;
		MainRenderer->ChangeAnimation("BossAttack_Death");
		AttackSuccess = true;
	}
	else if (3.0f < GetLiveTime() && false == BodyCollision->Collision(CollisionOrder::Inhale, BossAttackCol, CollisionType::Rect, CollisionType::Rect))
	{
		Death();
		return;
	}

	if (true == AttackSuccess && true == MainRenderer->IsAnimationEnd()
		|| true == TimeDone && true == MainRenderer->IsAnimationEnd())
	{
		Death();
		return;
	}
}