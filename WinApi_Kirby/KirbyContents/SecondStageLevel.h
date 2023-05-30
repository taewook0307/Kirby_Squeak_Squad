#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class Ground;
class SecondStageLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SecondStageLevel();
	~SecondStageLevel();

	// delete Function
	SecondStageLevel(const SecondStageLevel& _Other) = delete;
	SecondStageLevel(SecondStageLevel&& _Other) noexcept = delete;
	SecondStageLevel& operator=(const SecondStageLevel& _Other) = delete;
	SecondStageLevel& operator=(SecondStageLevel&& _Other) noexcept = delete;

protected:

private:
	Ground* SecondStage = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};