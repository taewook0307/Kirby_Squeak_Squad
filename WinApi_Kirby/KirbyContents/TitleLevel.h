#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:

private:
	class GameEngineActor* TitleActor;
	class GameEngineRenderer* MainRenderer;

	void Start() override;
	void Update(float _Delta) override;
};