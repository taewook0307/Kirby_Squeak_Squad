#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <string>
#include <map>

// 설명 : 화면혹은 장면을 표현합니다.
// 타이틀 장면
// 플레이 장면
// 엔딩 장면
class GameEngineCamera;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCollision;
	friend class GameEngineActor;
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


	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}


	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor, _Order);
		GroupList.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	GameEngineCamera* GetMainCamera()
	{
		return MainCamera;
	}

	GameEngineCamera* GetUICamera()
	{
		return UICamera;
	}

	static void CollisionDebugRenderSwitch() 
	{
		IsCollisionDebugRender = !IsCollisionDebugRender;
	}

	void OverCheck(GameEngineLevel* _PrevLevel);

protected:
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

private:
	static bool IsCollisionDebugRender;

	GameEngineCamera* MainCamera;
	GameEngineCamera* UICamera;



	std::map<int, std::list<GameEngineActor*>> AllActors;

	std::map<int, std::list<GameEngineCollision*>> AllCollision;

	void ActorInit(GameEngineActor* _Actor, int _Order);

	void ActorLevelEnd();
	void ActorLevelStart();

	void CollisionOverRelease();
	void CollisionRelease();

	void ActorUpdate(float _Delta);
	void ActorRender(float _Delta);
	void ActorRelease();
};

