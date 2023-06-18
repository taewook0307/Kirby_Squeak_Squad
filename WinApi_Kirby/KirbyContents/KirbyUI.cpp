#include "KirbyUI.h"
#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

KirbyUI::KirbyUI()
{
}

KirbyUI::~KirbyUI()
{
}

void KirbyUI::Start()
{
	if (ResourcesManager::GetInst().FindTexture("Normal_Icon.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\UI\\FormIcon\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Normal_Icon.Bmp"));
	}

	FormUI = CreateUIRenderer("Normal_Icon.Bmp", RenderOrder::PlayUI);
	FormUI->SetRenderPos(float4::ZERO);
}

void KirbyUI::Update(float _Delta)
{

}