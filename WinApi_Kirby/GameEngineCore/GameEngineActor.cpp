#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"

#include <GameEngineBase/GameEngineDebug.h>

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

	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}

	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

void GameEngineActor::ActorRelease()
{
	std::list<GameEngineRenderer*>& Group = AllRenderer;

	std::list<GameEngineRenderer*>::iterator GroupStartIter = Group.begin();
	std::list<GameEngineRenderer*>::iterator GroupEndIter = Group.end();

	for (; GroupStartIter != GroupEndIter;)
	{
		GameEngineRenderer* Renderer = *GroupStartIter;

		if (false == Renderer->IsDeath())
		{
			++GroupStartIter;
			continue;
		}

		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr인 Renderer가 Actor의 list에 들어가 있었습니다.");
			continue;
		}

		delete Renderer;
		Renderer = nullptr;

		GroupStartIter = Group.erase(GroupStartIter);
	}
}

void GameEngineActor::PushMainCameraRenderer(GameEngineRenderer*)
{

}