#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"

#include <list>
#include <string>
#include <map>

// 설명 : 화면혹은 장면을 표현 ex) 타이틀 장면, 플레이 장면, 엔딩 장면 등
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		GroupList.push_back(NewActor);
	}

protected:

private:
	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorInit(GameEngineActor* _Actor);

	void ActorUpdate(float _Delta);
	void ActorRender();
};