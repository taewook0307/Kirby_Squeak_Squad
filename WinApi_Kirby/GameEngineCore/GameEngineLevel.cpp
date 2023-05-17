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

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (nullptr != _Actor)
			{
				delete _Actor;
				_Actor = nullptr;
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
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->AddLiveTime(_Delta);
			_Actor->Update(_Delta);
		}
	}
}

void GameEngineLevel::ActorRender(float _Delta)
{
	MainCamera->Render(_Delta);

	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->Render();
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
		std::list<GameEngineActor*>& Group = GroupStartIter->second;

		std::list<GameEngineActor*>::iterator ObjectStartIter = Group.begin();
		std::list<GameEngineActor*>::iterator ObjectEndIter = Group.end();

		for (; ObjectStartIter != ObjectEndIter; )
		{
			GameEngineActor* Actor = *ObjectStartIter;
			if (false == Actor->IsDeath())
			{
				Actor->ActorRelease();
				++ObjectStartIter;
				continue;
			}

			if (nullptr == Actor)
			{
				MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}

			delete Actor;
			Actor = nullptr;

			ObjectStartIter = Group.erase(ObjectStartIter);
		}
	}
}