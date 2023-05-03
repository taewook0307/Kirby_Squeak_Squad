#include "GameEngineLevel.h"

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
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

void GameEngineLevel::ActorInit(GameEngineActor* _Actor)
{
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
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& ActorGroup = _Pair.second;

		for (GameEngineActor* _ActorPtr : ActorGroup)
		{
			_ActorPtr->Render();
		}
	}
}