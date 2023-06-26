#pragma once
#include "GameEngineActorSubObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <map>
#include <vector>

// Value 없는 맵.
// 데이터를 저장할 생각이 없다.
#include <set>

enum class CollisionType
{
	Point, // 점
	Rect, // 사각형
	CirCle, // 원
	Max, // 원
};

class CollisionData
{
public:
	float4 Pos;
	float4 Scale;

	float Left() const
	{
		return Pos.X - Scale.hX();
	}
	float Right() const
	{
		return Pos.X + Scale.hX();
	}
	float Top() const
	{
		return Pos.Y - Scale.hY();
	}
	float Bot() const
	{
		return Pos.Y + Scale.hY();
	}

	int iLeft() const
	{
		return static_cast<int>(Left());
	}
	int iRight() const
	{
		return static_cast<int>(Right());
	}
	int iTop() const
	{
		return static_cast<int>(Top());
	}
	int iBot() const
	{
		return static_cast<int>(Bot());
	}

};

// 설명 :
class GameEngineActor;
class CollisionInitClass;
class GameEngineCollision : public GameEngineActorSubObject
{
	// 함수 포인터
	static bool (*CollisionFunction[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(const CollisionData& _LeftData, const CollisionData& _RightData);

	friend CollisionInitClass;
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	static bool PointToPoint(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool PointToRect(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool PointToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool RectToPoint(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool RectToRect(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool RectToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool CirCleToPoint(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool CirCleToRect(const CollisionData& _LeftData, const CollisionData& _RightData);
	static bool CirCleToCirCle(const CollisionData& _LeftData, const CollisionData& _RightData);

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	void SetCollisionScale(const float4& _Value)
	{
		CollisionScale = _Value;
	}

	// 플레이어 위치기준.
	void SetCollisionPos(const float4& _Value)
	{
		CollisionPos = _Value;
	}

	// 몇가지 문제가 있는데. 
	// 1. 몬스터데 몬스터랑

	// 나는 사각형
	// int _Order => 나는 _Order 랑 충돌할거야
	// CollisionType _ThisType 나를 점으로 봐도 사각형으로 봐죠
	// CollisionType _OtherType 상대는 원으로 봐죠 사각형으로 봐줘
	// std::vector<GameEngineCollision*>& _Result 충돌한 애들 여기에 담아줘.

	template<typename EnumType>
	bool CollisionCallBack(
		EnumType _Order,
		CollisionType _ThisType = CollisionType::CirCle,
		CollisionType _OtherType = CollisionType::CirCle,
		void(*Enter)(GameEngineCollision* _this, GameEngineCollision* _Other) = nullptr,
		void(*Stay)(GameEngineCollision* _this, GameEngineCollision* _Other) = nullptr,
		void(*Exit)(GameEngineCollision* _this, GameEngineCollision* _Other) = nullptr
	)
	{
		return CollisionCallBack(static_cast<int>(_Order), _ThisType, _OtherType, Enter, Stay, Exit);
	}

	bool CollisionCallBack(
		int _Order,
		CollisionType _ThisType = CollisionType::CirCle,
		CollisionType _OtherType = CollisionType::CirCle,
		void(*Enter)(GameEngineCollision* _this, GameEngineCollision* _Other) = nullptr,
		void(*Stay)(GameEngineCollision* _this, GameEngineCollision* _Other) = nullptr,
		void(*Exit)(GameEngineCollision* _this, GameEngineCollision* _Other) = nullptr
	);

	template<typename EnumType>
	bool Collision(EnumType _Order, std::vector<GameEngineCollision*>& _Result
		, CollisionType _ThisType = CollisionType::CirCle
		, CollisionType _OtherType = CollisionType::CirCle)
	{
		return Collision(static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	}

	bool Collision(int _Order, std::vector<GameEngineCollision*>& _Result
		, CollisionType _ThisType = CollisionType::CirCle
		, CollisionType _OtherType = CollisionType::CirCle);

	template<typename EnumType>
	bool CollisionNext(const float4& _NextPos, EnumType _Order, std::vector<GameEngineCollision*>& _Result
		, CollisionType _ThisType = CollisionType::CirCle
		, CollisionType _OtherType = CollisionType::CirCle)
	{
		return CollisionNext(_NextPos, static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	}

	bool CollisionNext(const float4& _NextPos, int _Order, std::vector<GameEngineCollision*>& _Result
		, CollisionType _ThisType = CollisionType::CirCle
		, CollisionType _OtherType = CollisionType::CirCle);

	void SetOrder(int _Order) override;

	bool CollisonCheck(GameEngineCollision* _Other
		, CollisionType _ThisType
		, CollisionType _OtherType);

	bool CollisonCheckNext(const CollisionData& _Next, GameEngineCollision* _Other
		, CollisionType _ThisType
		, CollisionType _OtherType);

	float4 GetActorPivotPos();

	float4 GetActorScale()
	{
		return CollisionScale;
	}

	CollisionData GetCollisionData()
	{
		CollisionData Data;
		Data.Pos = GetActorPivotPos();
		Data.Scale = GetActorScale();
		return Data;
	}

	void SetCollisionType(CollisionType _ColType)
	{
		ColType = _ColType;
	}

	void On() override
	{
		GameEngineActorSubObject::On();
		CollisionRenderValue = true;
	}

	void Off() override
	{
		GameEngineActorSubObject::Off();
		CollisionRenderValue = false;
	}

	void IsUIOn()
	{
		IsUI = true;
	}

protected:

private:
	// 내가 어떤 애랑 처음충돌했다.
	// ??? 어떻게 체크할수 있을까?
	std::set<GameEngineCollision*> ColSet;

	bool IsUI = false;

	CollisionType ColType = CollisionType::Rect;

	bool CollisionRenderValue = true;

	float4 CollisionPos;
	float4 CollisionScale;

	void DebugRender();
};

