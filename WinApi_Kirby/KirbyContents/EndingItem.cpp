#include "EndingItem.h"
#include "SubLevel.h"
#include "Kirby.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
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
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
		if (SoundPlayCount > 0)
		{
			GameEngineSound::SoundPlay("ItemDrop.wav");
			--SoundPlayCount;
		}
	}
	unsigned int UpColor = GetGroundColor(EMPTYCOLOR, float4::UP);

	while (EMPTYCOLOR != UpColor)
	{
		AddPos(float4::UP);
		UpColor = GetGroundColor(EMPTYCOLOR, float4::UP);
	}

	if (true == BodyCollision->Collision(CollisionOrder::Body, EndingItemCol, CollisionType::Rect, CollisionType::Rect)
		|| static_cast<float>(fabs((GetPos() - Kirby::GetMainKirby()->GetPos()).Size())) < 10.0f)
	{
		Death();
		SubLevel::GetBGM().Stop();
		GameEngineSound::SoundPlay("Move.wav");
		GameEngineCore::ChangeLevel("EndingLevel");
		return;
	}
}