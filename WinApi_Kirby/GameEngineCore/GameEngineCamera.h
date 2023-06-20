#pragma once
#include "GameEngineRenderer.h"
#include <map>
#include <list>

// Ό³Έν :
class GameEngineRenderer;
class GameEngineCamera
{
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _Value)
	{
		Pos = _Value;
	}

	void AddPos(const float4& _Value)
	{
		Pos += _Value;
	}

	template<typename EnumType>
	void SetYSort(EnumType _Order, bool _Sort)
	{
		SetYSort(static_cast<int>(_Order), _Sort);
	}

	void SetYSort(int _Order, bool _Sort)
	{
		YSort[_Order] = _Sort;
	}

	template<typename EnumType>
	bool GetYSort(EnumType _Order)
	{
		return GetYSort(static_cast<int>(_Order));
	}

	bool GetYSort(int _Order)
	{
		if (YSort.end() == YSort.find(_Order))
		{
			YSort[_Order] = false;
		}

		return YSort[_Order];
	}

protected:

private:
	float4 Pos = float4::ZERO;

	std::map<int, std::list<GameEngineRenderer*>> Renderers;

	std::map<int, bool> YSort;

	void PushRenderer(GameEngineRenderer* _Renderer, int _Order);

	void Release();

	void OverRelease();

	void Render(float _Delta);
};

