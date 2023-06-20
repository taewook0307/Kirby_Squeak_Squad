#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineActor.h"

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
}

bool YSortFunction(GameEngineRenderer* _Left, GameEngineRenderer* _Right)
{
	return _Left->GetActorYPivot() < _Right->GetActorYPivot();
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

		// A C D F
		// 157 2011
		// C F A D 
		// 7 111520
		// 0 번 그룹 ysort 해야해?
		if (true == GetYSort(GroupStartIter->first))
		{
			// 포인터의 값으로 sort를 합니다
			// 내부에 있는 값을 비교합니다.
			// 그냥 하면 포인터의 크기로 합니다.
			// 포인터는 뭐다? => 8바이트 정수
			// List.sort();
			List.sort(YSortFunction);
		}

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