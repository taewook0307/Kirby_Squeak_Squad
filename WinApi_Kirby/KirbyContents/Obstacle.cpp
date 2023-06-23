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
		Path.MoveChild("\\Resources\\Map\\Obstacle\\");

		ResourcesManager::GetInst().CreateSpriteSheet(Path.PlusFilePath("Obstacle.Bmp"), 5, 1);
	}

	MainRenderer = CreateRenderer(RenderOrder::Item);

	MainRenderer->CreateAnimation("Obstacle_Idle", "Obstacle.Bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Obstacle_Death", "Obstacle.Bmp", 1, 4, 0.1f, false);
	MainRenderer->SetRenderScaleToTexture();

	MainRenderer->ChangeAnimation("Obstacle_Idle");

	BodyCollision = CreateCollision(CollisionOrder::Obstacle);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Obstacle::Update(float _Delta)
{

}