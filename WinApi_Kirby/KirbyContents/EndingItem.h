#pragma once

#include "BaseActor.h"

#define ENDINGITEMPOS { 0.0f, 0.0f }
#define ENDINGITEMSCALE { 50.0f, 50.0f }
#define ENDINGITEMCOLLISIONPOS { 0.0f, 0.0f }
#define ENDINGITEMCOLLISIONSCALE { 50.0f, 50.0f }

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
	void Start();
	void Update(float _Delta);
};