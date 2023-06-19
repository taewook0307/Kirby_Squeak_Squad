#pragma once

#include "BaseActor.h"

#define LIFEITEMPOS { 0.0f, 0.0f }
#define LIFEITEMSCALE { 50.0f, 50.0f }
#define LIFEITEMCOLLISIONPOS { 0.0f, 0.0f }
#define LIFEITEMCOLLISIONSCALE { 50.0f, 50.0f }

class GameEngineRenderer;
class GameEngineCollision;
class LifeCountPlusItem : public BaseActor
{
public:
	// constrcuter destructer
	LifeCountPlusItem();
	~LifeCountPlusItem();

	// delete Function
	LifeCountPlusItem(const LifeCountPlusItem& _Other) = delete;
	LifeCountPlusItem(LifeCountPlusItem&& _Other) noexcept = delete;
	LifeCountPlusItem& operator=(const LifeCountPlusItem& _Other) = delete;
	LifeCountPlusItem& operator=(LifeCountPlusItem&& _Other) noexcept = delete;

protected:

private:
	void Start();
	void Update(float _Delta);
};