#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
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

	for (GameEngineCollision* Collision : AllCollision)
	{
		delete Collision;
		Collision = nullptr;
	}

}

void GameEngineActor::ActorRelease()
{
	std::list<GameEngineRenderer*>::iterator ObjectStartIter = AllRenderer.begin();
	std::list<GameEngineRenderer*>::iterator ObjectEndIter = AllRenderer.end();

	for (; ObjectStartIter != ObjectEndIter; )
	{
		GameEngineRenderer* Renderer = *ObjectStartIter;
		if (false == Renderer->IsDeath())
		{
			++ObjectStartIter;
			continue;
		}


		if (nullptr == Renderer)
		{
			MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
			continue;
		}

		delete Renderer;
		Renderer = nullptr;

		// [s] [a] [a]     [a] [e]
		ObjectStartIter = AllRenderer.erase(ObjectStartIter);

	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order) 
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->Master = this;
	NewRenderer->MainCameraSetting();
	NewRenderer->SetOrder(_Order);

	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}


GameEngineRenderer* GameEngineActor::CreateUIRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->Master = this;
	NewRenderer->UICameraSetting();
	NewRenderer->SetOrder(_Order);

	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}
	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

GameEngineCollision* GameEngineActor::CreateCollision(int _Order/* = 0*/)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();

	NewCollision->Master = this;
	NewCollision->Start();
	NewCollision->SetOrder(_Order);
	AllCollision.push_back(NewCollision);

	return NewCollision;
}