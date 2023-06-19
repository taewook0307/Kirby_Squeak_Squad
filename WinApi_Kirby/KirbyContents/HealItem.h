#pragma once

#include "BaseActor.h"

class GameEngineRenderer;
class GameEngineCollision;
class HealItem : public BaseActor
{
public:
	// constrcuter destructer
	HealItem();
	~HealItem();

	// delete Function
	HealItem(const HealItem& _Other) = delete;
	HealItem(HealItem&& _Other) noexcept = delete;
	HealItem& operator=(const HealItem& _Other) = delete;
	HealItem& operator=(HealItem&& _Other) noexcept = delete;

protected:

private:
};