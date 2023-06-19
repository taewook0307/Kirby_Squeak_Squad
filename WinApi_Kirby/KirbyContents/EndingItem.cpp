#include "EndingItem.h"
#include "KirbyGameEnum.h"
#include "ActorEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

EndingItem::EndingItem()
{
}

EndingItem::~EndingItem()
{
}

void EndingItem::Start()
{
	if (nullptr == ResourcesManager::GetInst().FindTexture("Ending_Box.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Item\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Ending_Box.Bmp"));
	}

	MainRenderer = CreateRenderer("Ending_Box.Bmp", RenderOrder::Item);
	MainRenderer->SetRenderPos(ENDINGITEMPOS);
	MainRenderer->SetRenderScale(ENDINGITEMSCALE);

	BodyCollision = CreateCollision(CollisionOrder::ItemBody);
	BodyCollision->SetCollisionPos(ENDINGITEMCOLLISIONPOS);
	BodyCollision->SetCollisionScale(ENDINGITEMCOLLISIONSCALE);
}

void EndingItem::Update(float _Delta)
{

}