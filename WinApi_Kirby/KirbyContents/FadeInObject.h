#pragma once

#include <GameEngineCore/GameEngineActor.h>

class FadeInObject : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeInObject();
	~FadeInObject();

	// delete Function
	FadeInObject(const FadeInObject& _Other) = delete;
	FadeInObject(FadeInObject&& _Other) noexcept = delete;
	FadeInObject& operator=(const FadeInObject& _Other) = delete;
	FadeInObject& operator=(FadeInObject&& _Other) noexcept = delete;

	inline void SetFadeSpeed(float _Value)
	{
		FadeSpeed = _Value;
	}

	inline void FadeSpeedReset()
	{
		FadeSpeed = 100.0f;
	}

protected:

private:
	GameEngineRenderer* MainRenderer = nullptr;

	float AlphaValue = 255.0f;
	float FadeSpeed = 100.0f;

	void Start() override;
	void Update(float _Delta) override;
};