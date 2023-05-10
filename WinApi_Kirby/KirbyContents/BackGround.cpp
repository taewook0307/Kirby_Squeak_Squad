#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	SetPos({ 640, 360 });
}


void BackGround::Update(float _Delta) {
}
void BackGround::Render()
{
	
}
void BackGround::Release() {
}


void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Stage\\FirstStage\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		float4 Scale = Text->GetScale();

		Scale.X *= 3.0f;
		Scale.Y *= 3.0f;

		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
		Render->SetRenderScale(Scale);
	}
}