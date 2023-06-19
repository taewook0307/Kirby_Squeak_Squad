#pragma once

#include "BaseActor.h"

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
};