#include "BossMonster.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

BossMonster::BossMonster()
{
}

BossMonster::~BossMonster()
{
}

void BossMonster::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_Boss.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_Boss.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Boss.Bmp"), 5, 7);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Boss.Bmp"), 5, 7);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Boss);

		MainRenderer->CreateAnimation("Right_Boss_Idle", "Right_Boss.Bmp", 0, 3, 0.1f, true);
		
		MainRenderer->CreateAnimation("Left_Boss_Idle", "Left_Boss.Bmp", 0, 3, 0.1f, true);
	
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}
}