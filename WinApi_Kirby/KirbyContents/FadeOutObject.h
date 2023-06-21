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

protected:

private:
	GameEngineRenderer* MainRenderer = nullptr;

	float AlphaValue = 255.0f;
	float FadeSpeed = 100.0f;

	void Start() override;
	void Update(float _Delta) override;
};