#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCamera.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	for (GameEngineRenderer* Render : AllRenderer)
	{
		delete Render;
		Render = nullptr;
	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	GetLevel()->MainCamera->PushRenderer(NewRenderer, _Order);

	NewRenderer->Master = this;
	NewRenderer->SetTexture(_ImageName);
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

void GameEngineActor::PushMainCameraRenderer(GameEngineRenderer*)
{

}