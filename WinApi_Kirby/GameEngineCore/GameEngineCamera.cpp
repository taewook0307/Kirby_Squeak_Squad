#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineActor.h"

GameEngineCamera::GameEngineCamera() 
{
}

GameEngineCamera::~GameEngineCamera() 
{
}

void GameEngineCamera::Render(float _Delta)
{
	//for (const std::pair<int, std::list<GameEngineRenderer*>>& Pair : Renderers)
	//{
	//}

	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& List = GroupStartIter->second;

		std::list<GameEngineRenderer*>::iterator RenderStartIter = List.begin();
		std::list<GameEngineRenderer*>::iterator RenderEndIter = List.end();


		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			GameEngineRenderer* Render = *RenderStartIter;

			if (false == Render->IsUpdate())
			{
				continue;
			}

			Render->Render(_Delta);
		}
	}
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer, int _Order)
{
	if (nullptr == _Renderer)
	{
		MsgBoxAssert("nullptr인 랜더러를 그룹에 속하게 하려고 했습니다.");
	}

	_Renderer->Camera = this;
	Renderers[_Order].push_back(_Renderer);
}

void GameEngineCamera::Release()
{

	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	// 눈꼽 만큼이라도 연산을 줄이려는 거죠.

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& Group = GroupStartIter->second;

		std::list<GameEngineRenderer*>::iterator ActorStartIter = Group.begin();
		std::list<GameEngineRenderer*>::iterator ActorEndIter = Group.end();

		for (; ActorStartIter != ActorEndIter; )
		{
			GameEngineRenderer* Object = *ActorStartIter;
			if (false == Object->IsDeath())
			{
				++ActorStartIter;
				continue;
			}

			if (nullptr == Object)
			{
				MsgBoxAssert("nullptr인 랜더러가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}
			// [s] [a] [a]     [a] [e]
			ActorStartIter = Group.erase(ActorStartIter);

		}
	}
}

void GameEngineCamera::OverRelease()
{

	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	// 눈꼽 만큼이라도 연산을 줄이려는 거죠.

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& Group = GroupStartIter->second;

		std::list<GameEngineRenderer*>::iterator ActorStartIter = Group.begin();
		std::list<GameEngineRenderer*>::iterator ActorEndIter = Group.end();

		for (; ActorStartIter != ActorEndIter; )
		{
			GameEngineRenderer* Object = *ActorStartIter;
			if (false == Object->GetActor()->IsLevelOver())
			{
				++ActorStartIter;
				continue;
			}

			if (nullptr == Object)
			{
				MsgBoxAssert("nullptr인 랜더러가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}
			// [s] [a] [a]     [a] [e]
			ActorStartIter = Group.erase(ActorStartIter);

		}
	}
}