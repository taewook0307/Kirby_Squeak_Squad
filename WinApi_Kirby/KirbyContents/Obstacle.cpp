#include "Obstacle.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindTexture("Obstacle.Bmp"))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Map\\Obstacle\\");

		ResourcesManager::GetInst().CreateSpriteSheet(Path.PlusFilePath("Obstacle.Bmp"), 5, 1);
	}

	MainRenderer = CreateRenderer(RenderOrder::Item);

	MainRenderer->CreateAnimation("Obstacle_Idle", "Obstacle.Bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Obstacle_Death", "Obstacle.Bmp", 1, 4, 0.1f, false);
	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(RatioValue);

	MainRenderer->ChangeAnimation("Obstacle_Idle");

	BodyCollision = CreateCollision(CollisionOrder::Obstacle);
	BodyCollision->SetCollisionPos(OBSTACLECOLLISIONPOS);
	BodyCollision->SetCollisionScale(OBSTACLECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Obstacle::Update(float _Delta)
{
	if (true == BodyCollision->Collision(CollisionOrder::Attack, ObsCol, CollisionType::Rect, CollisionType::Rect)
		|| true == BodyCollision->Collision(CollisionOrder::SpecialAttack, ObsCol, CollisionType::Rect, CollisionType::Rect))
	{
		AttackCheck = true;
	}

	if (true == AttackCheck)
	{
		BodyCollision->Off();
		MainRenderer->ChangeAnimation("Obstacle_Death");
		
		if (true == MainRenderer->IsAnimationEnd())
		{
			Death();
			return;
		}
	}
}

void Obstacle::SetRendererRatio(float _Value)
{
	ChangeRatioValue = true;
	RatioValue = 4.0f * _Value;
	MainRenderer->SetScaleRatio(RatioValue);

	BodyCollision->SetCollisionPos(float4 OBSTACLECOLLISIONPOS * _Value);
	BodyCollision->SetCollisionScale(float4 OBSTACLECOLLISIONSCALE * _Value);
}

void Obstacle::ChangeFloorObstacle()
{
	if (false == ChangeRatioValue)
	{
		BodyCollision->Death();
		BodyCollision = CreateCollision(CollisionOrder::FloorObstacle);
		BodyCollision->SetCollisionPos(OBSTACLECOLLISIONPOS);
		BodyCollision->SetCollisionScale(OBSTACLECOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}
}