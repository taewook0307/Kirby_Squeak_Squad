#include "GameEngineCamera.h"

#include <GameEngineBase/GameEngineDebug.h>

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{

}

void GameEngineCamera::Render()
{
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

			Render->Render(this);
		}
	}
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer, int _Order)
{
	if (nullptr == _Renderer)
	{
		MsgBoxAssert("nullptr인 랜더러를 그룹에 속하게 하려고 했습니다.");
	}

	Renderers[_Order].push_back(_Renderer);
}

void GameEngineCamera::Release()
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& RendererGroup = GroupStartIter->second;

		std::list<GameEngineRenderer*>::iterator RendererStartIter = RendererGroup.begin();
		std::list<GameEngineRenderer*>::iterator RendererEndIter = RendererGroup.end();

		for (; RendererStartIter != RendererEndIter; )
		{
			GameEngineRenderer* Renderer = *RendererStartIter;
			if (false == Renderer->IsDeath())
			{
				++RendererStartIter;
				continue;
			}

			if (nullptr == Renderer)
			{
				MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}
			RendererStartIter = RendererGroup.erase(RendererStartIter);
		}
	}
}