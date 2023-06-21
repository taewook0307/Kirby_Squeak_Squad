#pragma once

#include <GameEngineCore/GameEngineActor.h>

class FadeOutObject : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeOutObject();
	~FadeOutObject();

	// delete Function
	FadeOutObject(const FadeOutObject& _Other) = delete;
	FadeOutObject(FadeOutObject&& _Other) noexcept = delete;
	FadeOutObject& operator=(const FadeOutObject& _Other) = delete;
	FadeOutObject& operator=(FadeOutObject&& _Other) noexcept = delete;

	inline void SetFadeSpeed(float _Value)
	{
		FadeSpeed = _Value;
	}

	inline void FadeSpeedReset()
	{
		FadeSpeed = 100.0f;
	}

	inline bool GetFadeEffectEnd() const
	{
		return FadeEffectEnd;
	}

protected:

private:
	GameEngineRenderer* MainRenderer = nullptr;

	float AlphaValue = 0.0f;
	float FadeSpeed = 100.0f;

	bool FadeEffectEnd = false;

	void Start() override;
	void Update(float _Delta) override;
};