#include "BackGround.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetWindowBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);
	// BackBuffer->BitCopy(FindTexture, GetPos());

	BackBuffer->BitCopy(FindTexture, GetPos());
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

		Scale.X *= 5.0f;
		Scale.Y *= 5.0f;

		SetScale(Scale);
	}

}