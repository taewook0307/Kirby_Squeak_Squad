#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

#include <GameEngineBase/GameEngineDebug.h>

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
			if (false == _ActorPtr->IsUpdate())
			{
				continue;
			}

			_ActorPtr->AddLiveTime(_Delta);
			_ActorPtr->Update(_Delta);
		}
	}
}

void GameEngineLevel::ActorRender(float _Delta)
{
	MainCamera->Render(_Delta);

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& ActorGroup = _Pair.second;

		for (GameEngineActor* _ActorPtr : ActorGroup)
		{
			if (false == _ActorPtr->IsUpdate())
			{
				continue;
			}

			_ActorPtr->Render();
		}
	}
}

void GameEngineLevel::ActorRelease()
{
	MainCamera->Release();

	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = AllActors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorGroup = GroupStartIter->second;

		std::list<GameEngineActor*>::iterator ActorStartIter = ActorGroup.begin();
		std::list<GameEngineActor*>::iterator ActorEndIter = ActorGroup.end();

		for (; ActorStartIter != ActorEndIter; )
		{
			GameEngineActor* ActorPtr = *ActorStartIter;
			if (false == ActorPtr->IsDeath())
			{
				ActorPtr->ActorRelease();
				++ActorStartIter;
				continue;
			}

			if (nullptr == ActorPtr)
			{
				MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}

			delete ActorPtr;
			ActorPtr = nullptr;

			ActorStartIter = ActorGroup.erase(ActorStartIter);
		}
	}
}