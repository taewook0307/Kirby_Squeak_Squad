#pragma once

#include "BaseActor.h"

class GameEngineRenderer;
class GameEngineCollision;
class EndingItem : public BaseActor
{
public:
	// constrcuter destructer
	EndingItem();
	~EndingItem();

	// delete Function
	EndingItem(const EndingItem& _Other) = delete;
	EndingItem(EndingItem&& _Other) noexcept = delete;
	EndingItem& operator=(const EndingItem& _Other) = delete;
	EndingItem& operator=(EndingItem&& _Other) noexcept = delete;

protected:

private:
};