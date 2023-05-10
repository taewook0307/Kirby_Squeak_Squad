#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = new GameEngineCamera();
	UICamera = new GameEngineCamera();
}

GameEngineLevel::~GameEngineLevel()
{
	if (nullptr != MainCamera)
	{
		delete MainCamera;
		MainCamera = nullptr;
	}

	if (nullptr != UICamera)
	{
		delete UICamera;
		UICamera = nullptr;
	}

	for (std::pair<int, std::list<GameEngineActor*>> _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& ActorGroup = _Pair.second;

		for (GameEngineActor* _ActorPtr : ActorGroup)
		{
			if (nullptr != _ActorPtr)
			{
				delete _ActorPtr;
				_ActorPtr = nullptr;
			}
		}
	}
}

void GameEngineLevel::ActorInit(GameEngineActor* _Actor, int _Order)
{
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

void GameEngineLevel::ActorUpdate(float _Delta)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& ActorGroup = _Pair.second;

		for (GameEngineActor* _ActorPtr : ActorGroup)
		{
			_ActorPtr->Update(_Delta);
		}
	}
}

void GameEngineLevel::ActorRender()
{
	MainCamera->Render();

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& ActorGroup = _Pair.second;

		for (GameEngineActor* _ActorPtr : ActorGroup)
		{
			_ActorPtr->Render();
		}
	}
}